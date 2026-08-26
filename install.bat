@echo off
setlocal enabledelayedexpansion

set "TARGET=rwx"
if defined PREFIX set "ENV_PREFIX=!PREFIX!"

set "HAS_CLEAN=0"
for %%A in (%*) do if "%%A"=="clean" set "HAS_CLEAN=1"
if !HAS_CLEAN! equ 1 (
 echo -------------------------
 echo  [Error] 'clean' argument not allowed with install
 echo -------------------------
 exit /b 1
)

if not exist "%TARGET%.c" (
 echo -------------------------
 echo  [Error] %TARGET%.c not found in current directory
 echo -------------------------
 exit /b 1
)

if exist "compile.bat" (
 set "QUIET=1"
 call compile.bat %* "%TARGET%.c"
 if !errorlevel! neq 0 exit /b 1
)else (
 echo -------------------------
 echo  [Error] compile.bat not found
 echo -------------------------
 exit /b 1
)

if not exist "config.txt" (
 if exist "configure.bat" (
  echo -------------------------
  echo  [Warning] config.txt is missing, running configure.bat
  echo -------------------------
  call configure.bat
 )else (
  echo -------------------------
  echo  [Warning] config.txt and configure.bat are missing
  echo -------------------------
 )
)

if exist "config.txt" (
 for /f "usebackq tokens=1,* delims==" %%A in ("config.txt") do set "%%A=%%~B"
)

if defined ENV_PREFIX set "PREFIX=!ENV_PREFIX!"
if not defined PREFIX set "PREFIX=C:\Program Files\${TARGET}"
if not defined BIN_EXT set "BIN_EXT=.exe"
set "PREFIX=!PREFIX:${TARGET}=%TARGET%!"

if not defined INSTALL_MSG set "INSTALL_MSG="Trying to install ${TARGET}${BIN_EXT} to ${PREFIX}\""
set "INSTALL_MSG=!INSTALL_MSG:"=!"
set "INSTALL_MSG=!INSTALL_MSG:${TARGET}=%TARGET%!"
set "INSTALL_MSG=!INSTALL_MSG:${BIN_EXT}=%BIN_EXT%!"
set "INSTALL_MSG=!INSTALL_MSG:${PREFIX}=%PREFIX%!"

echo -------------------------
echo !INSTALL_MSG!
echo -------------------------

if not defined INSTALL_CMD set "INSTALL_CMD=if not exist "${PREFIX}" mkdir "${PREFIX}" & copy /Y ${TARGET}${BIN_EXT} "${PREFIX}\" >nul & powershell -ExecutionPolicy Bypass -File "%~dp0add_path_windows.bat" "${PREFIX}" >nul 2>&1"
set "INSTALL_CMD=!INSTALL_CMD:${TARGET}=%TARGET%!"
set "INSTALL_CMD=!INSTALL_CMD:${BIN_EXT}=%BIN_EXT%!"
set "INSTALL_CMD=!INSTALL_CMD:${PREFIX}=%PREFIX%!"

cmd /c "!INSTALL_CMD!"

if !errorlevel! neq 0 (
 echo -------------------------
 echo  [Error] Failed to install %TARGET%
 echo -------------------------
 echo  Run as Administrator
 echo -------------------------
 exit /b 1
)

echo -------------------------
echo  Installation completed successfully
echo -------------------------
endlocal
