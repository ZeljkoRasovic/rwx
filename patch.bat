@echo off
setlocal enabledelayedexpansion

set "PROG=%~nx0"
set "CLEANUP_FILES="

if "%~1"=="" call :usage 1 >&2 & exit /b 1
set "CMD=%~1"
shift

if /i "%CMD%"=="-h" call :usage 0 & exit /b 0
if /i "%CMD%"=="--help" call :usage 0 & exit /b 0
if /i "%CMD%"=="help" call :usage 0 & exit /b 0

if /i "%CMD%"=="gen" (
 if "%~3"=="" call :usage 1 >&2 & exit /b 1
 if not "%~4"=="" call :usage 1 >&2 & exit /b 1
 call :gen_diff "%~1" "%~2" "%~3"
 set "ERROR=!errorlevel!"
 call :cleanup
 exit /b !ERROR!
)

if /i "%CMD%"=="apply" (
 if "%~2"=="" call :usage 1 >&2 & exit /b 1
 if not "%~3"=="" call :usage 1 >&2 & exit /b 1
 call :apply_patch "%~1" "%~2"
 set "ERROR=!errorlevel!"
 call :cleanup
 exit /b !ERROR!
)

call :usage 1 >&2 & exit /b 1

:die
(
 echo -------------------------
 echo  %PROG%: %~1
 echo -------------------------
) >&2
call :cleanup
exit /b 1

:cleanup
if defined CLEANUP_FILES (
 for %%F in (%CLEANUP_FILES%) do (
  if exist "%%~F" del /f /q "%%~F" >nul 2>nul
 )
)
exit /b 0

:have
where "%~1" >nul 2>nul
exit /b %errorlevel%

:create_temp_file
set "PREFIX=%~1"
set "TMP_FILE="
set "i=0"
:retry_temp
set /a "i+=1"
if !i! gtr 100 call :die "[Error] Cannot safely create temp file" & exit /b 1
set "TMP_FILE=%TEMP%\%PREFIX%.!RANDOM!.!i!"
if exist "%TMP_FILE%" goto retry_temp
(type nul > "%TMP_FILE%") 2>nul || goto retry_temp
for %%F in ("%TMP_FILE%") do set "TMP_FILE=%%~fF"
if defined CLEANUP_FILES (
 set "CLEANUP_FILES=!CLEANUP_FILES! "!TMP_FILE!""
) else (
 set "CLEANUP_FILES="!TMP_FILE!""
)
exit /b 0

:file_has_cr
where powershell >nul 2>nul || exit /b 1
set "CHK_FILE=%~1"
powershell -NoProfile -ExecutionPolicy Bypass -Command ^
 "if ((Get-Content -LiteralPath $env:CHK_FILE -Raw) -match '\r') { exit 0 } else { exit 1 }" >nul 2>&1
exit /b %errorlevel%

:strip_cr
where powershell >nul 2>nul || exit /b 1
set "STRIP_IN=%~1"
set "STRIP_OUT=%~2"
powershell -NoProfile -ExecutionPolicy Bypass -Command ^
 "$bytes=[System.IO.File]::ReadAllBytes($env:STRIP_IN);" ^
 " $new=@($bytes | Where-Object { $_ -ne 0x0D });" ^
 " [System.IO.File]::WriteAllBytes($env:STRIP_OUT,[byte[]]$new)"
exit /b %errorlevel%

:fix_diff_headers
where powershell >nul 2>nul || exit /b 1
set "FIX_ORIG=%~1"
set "FIX_MOD=%~2"
set "FIX_IN=%~3"
set "FIX_OUT=%~4"
powershell -NoProfile -ExecutionPolicy Bypass -Command ^
 "$o=$env:FIX_ORIG; $m=$env:FIX_MOD; $done=$false;" ^
 "$lines=Get-Content -LiteralPath $env:FIX_IN;" ^
 "$new=foreach($l in $lines) {" ^
 " if (-not $done) {" ^
 "  if ($l -match '^--- '){ '--- ' + $o }" ^
 "  elseif ($l -match '^\+\+\+ '){ $done=$true; '+++ ' + $m }" ^
 "  else { $l }" ^
 " } else { $l }" ^
 "};" ^
 "[System.IO.File]::WriteAllLines($env:FIX_OUT,$new)"
exit /b %errorlevel%

:prepare_patch
where powershell >nul 2>nul || exit /b 1
set "PREP_TARGET=%~2"
set "PREP_IN=%~1"
set "PREP_OUT=%~3"
powershell -NoProfile -ExecutionPolicy Bypass -Command ^
 "$t=$env:PREP_TARGET; $s=$false;" ^
 "$lines=Get-Content -LiteralPath $env:PREP_IN;" ^
 "$out=foreach($l in $lines) {" ^
 " $l=$l -replace '\r$','';" ^
 "  if ($l -match '^(diff --git |index |(old|new|deleted) mode|new file mode|similarity index|rename )') { continue };" ^
 "  if (-not $s) {" ^
 "   if ($l -match '^--- ' -and $l -notmatch '^--- /dev/null') { $l = '--- ' + $t }" ^
 "   elseif ($l -match '^\+\+\+ ' -and $l -notmatch '^\+\+\+ /dev/null') { $l='+++ ' + $t; $s=$true }" ^
 "  };" ^
 "  $l" ^
 "};" ^
 "[System.IO.File]::WriteAllLines($env:PREP_OUT, $out)"
exit /b %errorlevel%

:gen_diff
set "ORIG=%~1"
set "MOD=%~2"
set "OUT=%~3"

if not exist "%ORIG%" (call :die "[Error] Original file not found: %ORIG%" & exit /b 1)
if not exist "%MOD%" (call :die "[Error] Modified file not found: %MOD%" & exit /b 1)

call :have diff
set "HAVE_DIFF=!errorlevel!"
call :have git
set "HAVE_GIT=!errorlevel!"

if !HAVE_DIFF! neq 0 if !HAVE_GIT! neq 0 (
 call :die "[Error] Required tools not found: please install 'diff' or 'git'" & exit /b 1
)

set "HAS_CR=0"
call :file_has_cr "%ORIG%" && set "HAS_CR=1"
if !HAS_CR! equ 0 ( call :file_has_cr "%MOD%" && set "HAS_CR=1" )

set "DIFF_DONE=0"

if !HAVE_DIFF! equ 0 (
 if !HAS_CR! equ 0 (
  set "D_STATUS=0"
  diff -u -- "%ORIG%" "%MOD%" > "%OUT%" 2>nul
  set "D_STATUS=!errorlevel!"
  if !D_STATUS! equ 0 set "DIFF_DONE=1"
  if !D_STATUS! equ 1 set "DIFF_DONE=1"
 )
 if !DIFF_DONE! equ 0 if !HAS_CR! equ 1 (
  call :create_temp_file "orig"
  set "TMP_ORIG=!TMP_FILE!"
  call :create_temp_file "mod"
  set "TMP_MOD=!TMP_FILE!"
  call :strip_cr "%ORIG%" "!TMP_ORIG!" || (call :die "[Error] Processing %ORIG%" & exit /b 1)
  call :strip_cr "%MOD%" "!TMP_MOD!"  || (call :die "[Error] Processing %MOD%" & exit /b 1)
  set "D_STATUS=0"
  diff -u -- "!TMP_ORIG!" "!TMP_MOD!" > "%OUT%" 2>nul
  set "D_STATUS=!errorlevel!"
  if !D_STATUS! equ 0 set "DIFF_DONE=1"
  if !D_STATUS! equ 1 set "DIFF_DONE=1"
  if !DIFF_DONE! equ 1 (
   call :create_temp_file "out_clean"
   set "TMP_OUT=!TMP_FILE!"
   call :fix_diff_headers "%ORIG%" "%MOD%" "%OUT%" "!TMP_OUT!" || (call :die "[Error] Failed to fix diff headers" & exit /b 1)
   move /y "!TMP_OUT!" "%OUT%" >nul 2>nul || (call :die "[Error] Finalizing diff file" & exit /b 1)
  )
 )
)

if !DIFF_DONE! equ 0 if !HAVE_GIT! equ 0 (
 if !HAS_CR! equ 0 (
  set "GIT_STATUS=0"
  git diff --no-index --no-prefix --ignore-space-at-eol --no-color -- "%ORIG%" "%MOD%" > "%OUT%" 2>nul
  set "GIT_STATUS=!errorlevel!"
  if !GIT_STATUS! equ 0 set "DIFF_DONE=1"
  if !GIT_STATUS! equ 1 set "DIFF_DONE=1"
 )
 if !DIFF_DONE! equ 0 if !HAS_CR! equ 1 (
  call :create_temp_file "orig_git"
  set "GIT_ORIG=!TMP_FILE!"
  call :create_temp_file "mod_git"
  set "GIT_MOD=!TMP_FILE!"
  call :strip_cr "%ORIG%" "!GIT_ORIG!" || (call :die "[Error] Processing %ORIG%" & exit /b 1)
  call :strip_cr "%MOD%" "!GIT_MOD!"   || (call :die "[Error] Processing %MOD%" & exit /b 1)
  set "GIT_STATUS=0"
  git diff --no-index --no-prefix --ignore-space-at-eol --no-color -- "!GIT_ORIG!" "!GIT_MOD!" > "%OUT%" 2>nul
  set "GIT_STATUS=!errorlevel!"
  if !GIT_STATUS! equ 0 set "DIFF_DONE=1"
  if !GIT_STATUS! equ 1 set "DIFF_DONE=1"
  if !DIFF_DONE! equ 1 (
   call :create_temp_file "out_clean_git"
   set "TMP_OUT=!TMP_FILE!"
   call :fix_diff_headers "%ORIG%" "%MOD%" "%OUT%" "!TMP_OUT!" || (call :die "[Error] Failed to fix git diff headers" & exit /b 1)
   move /y "!TMP_OUT!" "%OUT%" >nul 2>nul || (call :die "[Error] Finalizing git diff file" & exit /b 1)
  )
 )
)

if !DIFF_DONE! equ 0 (call :die "[Error] Failed to generate diff" & exit /b 1)

for %%F in ("%OUT%") do set "OUT_SIZE=%%~zF"
if !OUT_SIZE! equ 0 (
 (
  echo -------------------------
  echo  [Warning] %PROG%: %OUT% is empty (no differences found)
  echo -------------------------
 ) >&2
) else (
 echo -------------------------
 echo  %PROG%: Wrote %OUT%
 echo -------------------------
)
exit /b 0

:apply_patch
set "PATCH_FILE=%~1"
set "TARGET=%~2"

if not exist "%PATCH_FILE%" (call :die "[Error] Patch file not found: %PATCH_FILE%" & exit /b 1)
if not exist "%TARGET%" (call :die "[Error] Target file not found: %TARGET%" & exit /b 1)

for %%D in ("%TARGET%") do set "TARGET_DIR=%%~dpD"
for %%B in ("%TARGET%") do set "TARGET_BASE=%%~nxB"
for %%P in ("%PATCH_FILE%") do set "PATCH_FULL=%%~fP"

if not exist "%TARGET_DIR%\" (call :die "[Error] Target directory not found: %TARGET_DIR%" & exit /b 1)

call :have patch
set "HAVE_PATCH=!errorlevel!"
call :have git
set "HAVE_GIT=!errorlevel!"

if !HAVE_PATCH! neq 0 if !HAVE_GIT! neq 0 (
 call :die "[Error] Required tools not found: please install 'patch' or 'git'" & exit /b 1
)

call :create_temp_file "patch"
set "TMP_PATCH=!TMP_FILE!"
call :create_temp_file "patch_out"
set "PATCH_OUT=!TMP_FILE!"
call :create_temp_file "backup"
set "BACKUP_FILE=!TMP_FILE!"

copy /y "%TARGET%" "!BACKUP_FILE!" >nul || (call :die "[Error] Failed to backup target file" & exit /b 1)

call :prepare_patch "!PATCH_FULL!" "!TARGET_BASE!" "!TMP_PATCH!" || (call :die "[Error] Failed to prepare patch file" & exit /b 1)

pushd "%TARGET_DIR%" || (call :die "[Error] Cannot access target directory" & exit /b 1)

set "PATCH_APPLIED=0"
set "P_STATUS="

if !HAVE_PATCH! equ 0 (
 patch -p0 < "!TMP_PATCH!" >"!PATCH_OUT!" 2>&1
 if !errorlevel! equ 0 (
  set "PATCH_APPLIED=1"
 ) else (
  set "P_STATUS=!errorlevel!"
 )
)

if !PATCH_APPLIED! equ 0 if !HAVE_GIT! equ 0 (
 if exist "!BACKUP_FILE!" copy /y "!BACKUP_FILE!" "%TARGET%" >nul
 git apply -p0 --no-index --whitespace=nowarn --ignore-space-change -- "!TMP_PATCH!" >"!PATCH_OUT!" 2>&1
 if !errorlevel! equ 0 (
  set "PATCH_APPLIED=1"
 ) else (
  set "P_STATUS=!errorlevel!"
 )
)

popd

if !PATCH_APPLIED! equ 0 (
 if exist "!BACKUP_FILE!" copy /y "!BACKUP_FILE!" "%TARGET%" >nul
 if defined P_STATUS type "!PATCH_OUT!" >&2
 call :die "[Error] Patch application failed. See output above." & exit /b 1
)

echo -------------------------
echo  %PROG%: applied %PATCH_FILE% to %TARGET%
echo -------------------------
call :cleanup
exit /b 0

:usage
set "EXIT_CODE=%~1"
if "%EXIT_CODE%"=="" set "EXIT_CODE=1"
(
 echo -------------------------
 echo Usage:
 echo  .\%PROG% gen   ^<original_file^> ^<modified_file^> ^<output.diff^>
 echo  .\%PROG% apply ^<patch_file^> ^<target_file^>
 echo.
 echo Commands:
 echo  gen    Generate a unified diff between two individual files.
 echo  apply  Apply a previously generated patch file to a single target file.
 echo.
 echo Note:
 echo  For patch name use this format:
 echo  patch word (patch),
 echo  what patch does (cpp_support),
 echo  version number on which this patch works
 echo  Example: patch_cpp_support_1_0_0.diff
 echo.
 echo Examples:
 echo  .\%PROG% gen rwx.c rwx_with_cpp.c patch_cpp_support_1_0_0.diff
 echo  .\%PROG% apply patch_cpp_support_1_0_0.diff rwx.c
 echo -------------------------
)
if %EXIT_CODE% equ 1 (
 call :cleanup
 exit /b 1
) else (
 exit /b 0
)
