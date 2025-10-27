# Getting Started!

This guide will help you get started for both using the API or helping developping it. 

# Contents
- [Prerequisites](#prerequisites)
- [Setup for Developpement](#developpement)
- [Setup for Usage](#usage)

## Consider checking this part of the documentation

- [ReadMe](../README.md)
- [Usage](usage.md)


---

## Prerequisites

- **CMake >= 3.16**
- **C >= 17**
- **Python >= 3.10**
- **SDL2 & SLD2_image**


On macOS (Homebrew):
```bash
brew install cmake sdl2 sdl2_image
```

On Ubuntu or other Debian based distros (apt):
```bash
sudo apt install cmake python3-dev libsdl2-dev libsdl2-image-dev
```

On arch (pacman):
```bash
sudo pacman -S --needed base-devel cmake python python-pip sdl2 sdl2_image
```

On windows >= 10: install from the internet

---

# Developpement

## Setup

### Clone

```bash
cd path/to/your/project
```
```bash
git clone git@github.com:Jean1000levrai/EasyPyEngine.git
```

### create a build folder
```bash
mkdir -p build
```

## Notes

### Virtual Environment for Python

It is highly recommended to create a virtual environment for python, this will make things easier for you as all python packages (e.g. setuptools) will remain in the project's folder and won't bloat our whole system. 

```bash 
python3 -m venv .venv
```

### CMake

Use cmake to build for the python extension. 
```bash
cd build/
cmake ..
make
```
#### Additional notes

right now CMakeLists.txt is only optimized for my machine running macos but is planned to be updated to work on most machines (windows, mac, linux)

### compile for dev

Use compile.sh to make an executable for testing when developing in C. 
```bash
compile.sh
```
This script will create an executable in `build/` in launch it.



# Usage

## ------ TODO ------

