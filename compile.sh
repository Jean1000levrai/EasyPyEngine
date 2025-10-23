#!/bin/bash

# Stop on first error
set -e  

# Build folder
mkdir -p build

# Source files
SRC_FILES=$(find src/ -name '*.c')

# SDL flags
CFLAGS="$(pkg-config --cflags sdl2 SDL2_image) $(python3-config --cflags) -I./include"
LDFLAGS="$(pkg-config --libs sdl2 SDL2_image) $(python3-config --ldflags)"

# Compile
gcc -g $CFLAGS $SRC_FILES -o build/application $LDFLAGS

# Run
./build/application