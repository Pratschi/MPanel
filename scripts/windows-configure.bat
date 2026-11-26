@echo off
rmdir /s /q build 2>nul
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXE_LINKER_FLAGS="-static -static-libgcc -static-libstdc++"
if errorlevel 1 exit /b 1