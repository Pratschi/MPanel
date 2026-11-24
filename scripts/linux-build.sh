#!/usr/bin/env bash
set -euo pipefail
trap 'echo -e "\nAn error occurred. For help, please read docs/Compiling.md" >&2' ERR

ROOT="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"

CLEAN=false
RUN=false

for arg in "$@"; do
    case "$arg" in
        --clean) CLEAN=true ;;
        --run)   RUN=true ;;
        *)
            echo "Usage: $0 [--clean] [--run]" >&2
            exit 1
            ;;
    esac
done

if [[ ! -d "$ROOT/build" ]]; then
    cmake -S "$ROOT" -B "$ROOT/build"
fi

cmake --build "$ROOT/build"

EXECUTABLE="$ROOT/build/MPanel"

if [[ ! -f "$EXECUTABLE" ]]; then
    echo "Error: executable not found at $EXECUTABLE" >&2
    exit 1
fi

if [[ "$CLEAN" == true ]]; then
    mv "$EXECUTABLE" "$ROOT/MPanel"
    rm -rf "$ROOT/build"
    EXECUTABLE="$ROOT/MPanel"
fi

if [[ "$RUN" == true ]]; then
    clear
    "$EXECUTABLE"
fi
