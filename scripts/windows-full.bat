@echo off
echo [INFO] Configuring...
call scripts\windows-configure.bat
if errorlevel 1 exit /b 1

echo [INFO] Building...
call scripts\windows-build.bat
if errorlevel 1 exit /b 1

echo [INFO] Compilation Complete.
build\MPanel.exe --version