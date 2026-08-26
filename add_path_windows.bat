@echo off
setlocal

if "%~1"=="" (
 exit /b 1
)

set "DIR=%~1"

powershell -NoProfile -ExecutionPolicy Bypass -Command "$Dir='%DIR%'; $p=[Environment]::GetEnvironmentVariable('Path','Machine'); $paths=$p -split ';' | Where-Object { $_ }; if ($paths -notcontains $Dir) { [Environment]::SetEnvironmentVariable('Path',\"$p;$Dir\",'Machine') }"

endlocal
