@echo off
setlocal enabledelayedexpansion

set "TARGET=rwx"
if defined PREFIX set "ENV_PREFIX=!PREFIX!"

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

if not defined UNINSTALL_MSG set "UNINSTALL_MSG="Trying to remove ${TARGET}${BIN_EXT} from ${PREFIX}\""
set "UNINSTALL_MSG=!UNINSTALL_MSG:"=!"
set "UNINSTALL_MSG=!UNINSTALL_MSG:${TARGET}=%TARGET%!"
set "UNINSTALL_MSG=!UNINSTALL_MSG:${BIN_EXT}=%BIN_EXT%!"
set "UNINSTALL_MSG=!UNINSTALL_MSG:${PREFIX}=%PREFIX%!"

echo -------------------------
echo !UNINSTALL_MSG!
echo -------------------------

if not defined UNINSTALL_CMD set "UNINSTALL_CMD=del /Q /F "${PREFIX}\${TARGET}${BIN_EXT}" 2>nul & rmdir "${PREFIX}" 2>nul"
set "UNINSTALL_CMD=!UNINSTALL_CMD:${TARGET}=%TARGET%!"
set "UNINSTALL_CMD=!UNINSTALL_CMD:${BIN_EXT}=%BIN_EXT%!"
set "UNINSTALL_CMD=!UNINSTALL_CMD:${PREFIX}=%PREFIX%!"

cmd /c "!UNINSTALL_CMD!"

if !errorlevel! neq 0 (
 echo -------------------------
 echo  [Error] Failed to remove %TARGET%
 echo -------------------------
 echo  Run as Administrator
 echo -------------------------
 exit /b 1
)

echo -------------------------
echo  Uninstall completed successfully
echo -------------------------
endlocal
