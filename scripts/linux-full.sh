#!/usr/bin/env bash

echo "[INFO] Configuring..."
./scripts/linux-configure.sh
echo "[INFO] Building..."
./scripts/linux-build.sh
echo "[INFO] Compilation Complete."
./build/MPanel --version