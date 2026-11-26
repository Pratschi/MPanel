#!/usr/bin/env bash

cmake -S "." -B "./build" -G Ninja \
    -DCMAKE_BUILD_TYPE="${BUILD_TYPE:-Release}"