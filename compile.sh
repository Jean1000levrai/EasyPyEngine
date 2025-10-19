#!/bin/bash

# Pour lancer, utiliser sh compile.sh ou bash compile.sh ou ./compile.sh (nécessite autorisation (chmod))

# stoppe le script en cas d'erreur
set -e  

# dossier build
mkdir -p build

# les fichiers sources
SRC_FILES=$(find src/ -name '*.c')

# les flags
CFLAGS=$(pkg-config --cflags sdl3)
LDFLAGS=$(pkg-config --libs sdl3)

# compilation
gcc $SRC_FILES -o build/application $CFLAGS $LDFLAGS -Iinclude
./build/application

