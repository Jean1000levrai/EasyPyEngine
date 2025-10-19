#!/bin/bash

# Stop on first error
set -e  

# Build folder
mkdir -p build

# Source files
SRC_FILES=$(find src/ -name '*.c')

# SDL flags
CFLAGS="$(pkg-config --cflags sdl2)"
LDFLAGS="$(pkg-config --libs sdl2)"

# Python flags
CFLAGS+=" $(python3-config --cflags)"
LDFLAGS+=" $(python3-config --ldflags)"

# Compile
gcc -g $CFLAGS -Iinclude $SRC_FILES -o build/application $LDFLAGS

# Run
./build/application