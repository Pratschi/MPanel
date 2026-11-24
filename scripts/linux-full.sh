#!/usr/bin/env bash
set -euo pipefail
trap 'echo -e "\nAn error occurred. For compilation help, please read docs/Compiling.md" >&2' ERR
ROOT="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"

echo -e "[INFO] Configuring..."
"$ROOT"/scripts/linux-configure.sh
echo -e "[INFO] Building..."
"$ROOT"/scripts/linux-build.sh

clear

echo -e "[INFO] Cleaning..."
mv "$ROOT/build/MPanel" "$ROOT/"
rm -rf "$ROOT/build/"

echo -e "===== PROGRAM RUNNING ====="
"$ROOT"/MPanel