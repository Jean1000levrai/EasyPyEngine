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

Right now CMakeLists.txt is only optimized for my machine running macos but is planned to be updated to work on most machines (windows, mac, linux)

### compile for dev

#### Compile to C

Use compile.sh to make an executable for testing when developing in C. 
```bash
compile.sh
```
This script will create an executable in `build/` and launch it.   
   
#### To wrap it to python
1. Compile it
```bash
cd build
make
```
2. Then add the function or object in `python/easyPyEngineModule.c` using the `Python.h` library.   
3. Then create the shared library for python
```bash
python3 example/setup.py build
```
4. Test the library in python! Make sure to include the path to the .so by adding the path at the top of your script.
```python
import sys
sys.path.append("/Users/<username>/<path/to/project>/build/lib.macosx-15.0-arm64-cpython-314")
# the library is here on my device for example

import easyPyEngine
```




# Usage

### 1. Install Dependencies

On Ubuntu / Debian. 
```bash
sudo apt install libsdl2-dev libsdl2-image-dev
```
On 
```bash
brew install sdl2 sdl2_image
```

### 2. Install the files

Go to `https://github.com/Jean1000levrai/EasyPyEngine/`.   
Install the appropriate version.   
If on Windows or Linux, it is not released yet.  

### 3. In Python

```python
import sys
sys.path.append("path/to/so")
import easyPyEngine
```
**Note:** The specified path should be the folder to `easyPyEngine.so`, Not the .so file directly.

### 4. Start programming
[Usage](usage.md). 



