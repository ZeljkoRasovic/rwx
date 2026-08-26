@echo off
setlocal enabledelayedexpansion

if "%~1"=="" (
 echo -------------------------
 echo  Usage: %~nx0 [compiler] [flags] ^<file.c^> ^| %~nx0 clean ^<file^>
 echo -------------------------
 exit /b 1
)

if /i "%~1"=="clean" (
 if "%~2"=="" (
  echo -------------------------
  echo  [Error] Please specify what to clean
  echo -------------------------
  exit /b 1
 )
 echo -------------------------
 echo  Cleaning up %~2
 echo -------------------------
 del /f /q "%~2" 2>nul
 exit /b 0
)

set "CLI_CC="
set "CLI_CFLAGS="
set "CLI_LDFLAGS="
set "SOURCE_FILE="

:parse_args
if "%~1"=="" goto args_done
set "ARG=%~1"
set "PREFIX_ONE=!ARG:~0,1!"
set "PREFIX_TWO=!ARG:~0,2!"

if "!ARG:~-2!"==".c" (
 set "SOURCE_FILE=!ARG!"
 shift
 goto parse_args
)

if "!ARG!"=="-I" goto handle_space_flag
if "!ARG!"=="/I" goto handle_space_flag
if "!ARG!"=="-L" goto handle_space_flag
if "!ARG!"=="/L" goto handle_space_flag
if "!ARG!"=="-l" goto handle_space_flag
if "!ARG!"=="/l" goto handle_space_flag
if "!ARG!"=="-D" goto handle_space_flag
if "!ARG!"=="/D" goto handle_space_flag
if "!ARG!"=="-U" goto handle_space_flag
if "!ARG!"=="/U" goto handle_space_flag

if "!PREFIX_TWO!"=="-l" (
 if defined CLI_LDFLAGS (set "CLI_LDFLAGS=!CLI_LDFLAGS! !ARG!") else (set "CLI_LDFLAGS=!ARG!")
)else if "!PREFIX_TWO!"=="-L" (
 if defined CLI_LDFLAGS (set "CLI_LDFLAGS=!CLI_LDFLAGS! !ARG!") else (set "CLI_LDFLAGS=!ARG!")
)else if "!PREFIX_TWO!"=="/l" (
 if defined CLI_LDFLAGS (set "CLI_LDFLAGS=!CLI_LDFLAGS! !ARG!") else (set "CLI_LDFLAGS=!ARG!")
)else if "!PREFIX_TWO!"=="/L" (
 if defined CLI_LDFLAGS (set "CLI_LDFLAGS=!CLI_LDFLAGS! !ARG!") else (set "CLI_LDFLAGS=!ARG!")
)else if "!PREFIX_ONE!"=="-" (
 if defined CLI_CFLAGS (set "CLI_CFLAGS=!CLI_CFLAGS! !ARG!") else (set "CLI_CFLAGS=!ARG!")
)else if "!PREFIX_ONE!"=="/" (
 if defined CLI_CFLAGS (set "CLI_CFLAGS=!CLI_CFLAGS! !ARG!") else (set "CLI_CFLAGS=!ARG!")
)else (
 if "!CLI_CC!"=="" (
  set "CLI_CC=!ARG!"
 )
)

shift
goto parse_args

:handle_space_flag
set "NEXT_ARG=%~2"
if "!NEXT_ARG!"=="" (
 echo -------------------------
 echo  [Error] !ARG! requires an argument
 echo -------------------------
 exit /b 1
)
if "!ARG!"=="-L" (
 if defined CLI_LDFLAGS (set "CLI_LDFLAGS=!CLI_LDFLAGS! !ARG! !NEXT_ARG!") else (set "CLI_LDFLAGS=!ARG! !NEXT_ARG!")
)else if "!ARG!"=="-l" (
 if defined CLI_LDFLAGS (set "CLI_LDFLAGS=!CLI_LDFLAGS! !ARG! !NEXT_ARG!") else (set "CLI_LDFLAGS=!ARG! !NEXT_ARG!")
)else if "!ARG!"=="/L" (
 if defined CLI_LDFLAGS (set "CLI_LDFLAGS=!CLI_LDFLAGS! !ARG! !NEXT_ARG!") else (set "CLI_LDFLAGS=!ARG! !NEXT_ARG!")
)else if "!ARG!"=="/l" (
 if defined CLI_LDFLAGS (set "CLI_LDFLAGS=!CLI_LDFLAGS! !ARG! !NEXT_ARG!") else (set "CLI_LDFLAGS=!ARG! !NEXT_ARG!")
)else (
 if defined CLI_CFLAGS (set "CLI_CFLAGS=!CLI_CFLAGS! !ARG! !NEXT_ARG!") else (set "CLI_CFLAGS=!ARG! !NEXT_ARG!")
)
shift
shift
goto parse_args

:args_done

if "!SOURCE_FILE!"=="" (
 echo -------------------------
 echo  [Error] No source file ^(.c^) specified
 echo -------------------------
 echo  Usage: %~nx0 [compiler] [flags] ^<file.c^>
 echo -------------------------
 exit /b 1
)

set "ENV_CC=!CC!"
set "ENV_CFLAGS=!CFLAGS!"
set "ENV_LDFLAGS=!LDFLAGS!"
set "CFLAGS="
set "LDFLAGS="

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

if not "!CLI_CC!"=="" (
 set "COMPILER=!CLI_CC!"
)else if not "!ENV_CC!"=="" (
 set "COMPILER=!ENV_CC!"
)else if not "!CC!"=="" (
 set "COMPILER=!CC!"
)else (
 set "COMPILER=cc"
)

where "!COMPILER!" >nul 2>&1
if !errorlevel! neq 0 (
 if not exist "!COMPILER!" (
  echo -------------------------
  echo  [Error] Compiler '!COMPILER!' not found on your system
  echo -------------------------
  exit /b 1
 )
)

if not "!CLI_CFLAGS!"=="" (
 set "CFLAGS=!CLI_CFLAGS!"
)else if not "!ENV_CFLAGS!"=="" (
 set "CFLAGS=!ENV_CFLAGS!"
)else if "!CFLAGS!"=="" (
 if /i "!COMPILER!"=="cl" (
  set "CFLAGS=/W4 /O2"
 )else (
  set "CFLAGS=-Wall -Wextra -O2"
 )
)

if not "!CLI_LDFLAGS!"=="" (
 set "LDFLAGS=!CLI_LDFLAGS!"
)else if not "!ENV_LDFLAGS!"=="" (
 set "LDFLAGS=!ENV_LDFLAGS!"
)else (
 set "LDFLAGS=-lkernel32"
)

for %%F in ("!SOURCE_FILE!") do set "FILE_NAME=%%~nF"
if not defined BIN_EXT set "BIN_EXT=.exe"
set "OUT_FILE=!FILE_NAME!!BIN_EXT!"

echo =========================
echo  Compiler: !COMPILER!
echo  CFLAGS:   !CFLAGS!
echo  LDFLAGS:  !LDFLAGS!
echo =========================

if /i "!COMPILER!"=="cl" (
 echo "!COMPILER!" !CFLAGS! /utf-8 "!SOURCE_FILE!" /Fe:"!OUT_FILE!" !LDFLAGS!
 "!COMPILER!" !CFLAGS! "!SOURCE_FILE!" /Fe:"!OUT_FILE!" !LDFLAGS!
)else (
 echo "!COMPILER!" !CFLAGS! "!SOURCE_FILE!" -o "!OUT_FILE!" !LDFLAGS!
 "!COMPILER!" !CFLAGS! "!SOURCE_FILE!" -o "!OUT_FILE!" !LDFLAGS!
)

if !errorlevel! equ 0 (
 echo -------------------------
 echo  Success!
 echo -------------------------
 if not "!QUIET!"=="1" (
  echo -------------------------
  echo  Run program with .\!OUT_FILE!
  echo -------------------------
 )
)else (
 echo -------------------------
 echo  [Error] Compilation failed
 echo -------------------------
 exit /b 1
)

endlocal
