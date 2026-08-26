@echo off
echo -------------------------
echo  Detecting C compiler
echo -------------------------

set "DETECTED_CC="
set "DEFAULT_CFLAGS=-Wall -Wextra -O2"
set "DEFAULT_LDFLAGS=-lkernel32"

if not defined CC goto check
where "%CC%" >nul 2>&1
if %errorlevel% equ 0 (
 set "DETECTED_CC=%CC%"
 goto write_config
)

:check
where gcc >nul 2>&1
if %errorlevel% equ 0 (
 set "DETECTED_CC=gcc"
 goto write_config
)

where clang >nul 2>&1
if %errorlevel% equ 0 (
 set "DETECTED_CC=clang"
 goto write_config
)

where cl >nul 2>&1
if %errorlevel% equ 0 (
 set "DETECTED_CC=cl"
 set "DEFAULT_CFLAGS=/W4 /O2"
 goto write_config
)

where cc >nul 2>&1
if %errorlevel% equ 0 (
 set "DETECTED_CC=cc"
 goto write_config
)

echo -------------------------
echo  [Error] No C compiler found on your system
echo -------------------------
exit /b 1

:write_config
if not defined PREFIX set "PREFIX=C:\Program Files\${TARGET}"

(
echo CC="%DETECTED_CC%"
echo CFLAGS="%DEFAULT_CFLAGS%"
echo LDFLAGS="%DEFAULT_LDFLAGS"
echo BIN_EXT=".exe"
echo PREFIX="%PREFIX%"
echo INSTALL_MSG="Trying to install ${TARGET}${BIN_EXT} to ${PREFIX}\"
echo UNINSTALL_MSG="Trying to remove ${TARGET}${BIN_EXT} from ${PREFIX}\"
echo INSTALL_CMD=if not exist "${PREFIX}" mkdir "${PREFIX}" ^& copy /Y ${TARGET}${BIN_EXT} "${PREFIX}\" ^>nul ^& powershell -ExecutionPolicy Bypass -File "%~dp0add_path_windows.bat" "${PREFIX}" ^>nul 2^>^&1
echo UNINSTALL_CMD=del /Q /F "${PREFIX}\${TARGET}${BIN_EXT}" 2^>nul ^& rmdir "${PREFIX}" 2^>nul
) > config.txt

echo =========================
echo  Found: %DETECTED_CC%
echo =========================
echo -------------------------
echo  Configuration complete
echo -------------------------
