@echo off
cmake --build build --config Release
if errorlevel 1 exit /b 1

if not exist "build\MPanel.exe" (
    echo Error: executable not found at build\MPanel.exe 1>&2
    exit /b 1
)