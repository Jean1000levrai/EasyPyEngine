# EasyPyEngine

<div align="center">
  <a href="https://moonshot.hackclub.com" target="_blank">
    <img src="https://hc-cdn.hel1.your-objectstorage.com/s/v3/35ad2be8c916670f3e1ac63c1df04d76a4b337d1_moonshot.png" 
         alt="This project is part of Moonshot, a 4-day hackathon in Florida visiting Kennedy Space Center and Universal Studios!" 
         style="width: 100%;">
  </a>
</div>

## About

A very easy to use game engine for python. It is developped in C with the SDL2 library. 


## Installation

### Requirements

- python
- C17+
- SDL2
- SDL2_image

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

### CMake

use cmake to build for the python extension
```bash
cd build/
cmake ..
make
```

### compile for dev

use compile.sh to make an executable for testing when developing in C
```bash
compile.sh
```


### Additional notes

right now CMakeLists.txt is only optimized for my machine running macos but is planned to be updated to work on most machines (windows, mac, linux)

## Contributors

[![Contributors](https://contrib.rocks/image?repo=USERNAME/REPO)](https://github.com/Jean1000levrai/EasyPyEngine/graphs/contributors)


## License

This project is under thge MIT License, check the LICENSE. 




