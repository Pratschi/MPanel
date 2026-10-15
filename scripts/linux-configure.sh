#!/usr/bin/env bash
set -euo pipefail
trap 'echo -e "\nAn error occurred. For help, please read docs/Compiling.md" >&2' ERR
ROOT="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"

cmake -S "$ROOT" -B "$ROOT/build" -G Ninja \
    -DCMAKE_BUILD_TYPE="${BUILD_TYPE:-Release}"