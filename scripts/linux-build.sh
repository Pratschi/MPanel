#!/usr/bin/env bash

if [[ ! -d "./build" ]]; then
    cmake -S "." -B "./build" 
fi

cmake --build "./build"

if [[ ! -f "./build/MPanel" ]]; then
    echo "Error: executable not found at ./build/MPanel" >&2
    exit 1
fi