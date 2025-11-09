from setuptools import setup, Extension
import sys
import os


sdl2_include = "/opt/homebrew/include"
sdl2_lib = "/opt/homebrew/lib"

engine_module = Extension(
    "easyPyEngine",  # Python module name
    sources=[
        "src/engine.c",
        "src/graphics.c",
        "src/input.c",
        "src/sprite.c",
        "python/easyPyEngineModule.c",  # wrapper functions
    ],
    include_dirs=[
        sdl2_include,
        "include",
    ],
    library_dirs=[sdl2_lib],
    libraries=["SDL2", "SDL2_image"],  # SDL2 libraries
    extra_compile_args=["-std=c17"],
)

setup(
    name="easyPyEngine",
    version="0.1",
    description="Minimal 2D game engine in C with SDL2",
    ext_modules=[engine_module],
)
