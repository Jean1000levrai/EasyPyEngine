from setuptools import setup, Extension
from Cython.Build import cythonize
import sysconfig

engine_extension = Extension(
    "EasyPyEngine",
    sources=["python/engine_wrapper.pyx"],
    include_dirs=[
        "include",  # your own headers
        "/opt/homebrew/include",  # this allows #include <SDL2/SDL.h>
        sysconfig.get_path("include")
    ],
    library_dirs=["/opt/homebrew/lib"],
    libraries=["SDL2", "SDL2_image"],
    language="c"
)

setup(
    name="EasyPyEngine",
    version="0.0.1",
    ext_modules=cythonize(engine_extension, compiler_directives={"language_level": "3"})
)
