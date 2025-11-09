cmake_minimum_required(VERSION 3.16)
project(easyPyEngine C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Python
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

# SDL2
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)

file(GLOB SRC_FILES src/*.c)
add_library(easyPyEngine MODULE ${SRC_FILES} python/easyPyEngine.c)

# so name 
set_target_properties(easyPyEngine PROPERTIES
    PREFIX ""
    SUFFIX ".so"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/python/easyPyEngine"
    LINK_FLAGS "-undefined dynamic_lookup"
)

# Includes
target_include_directories(easyPyEngine PRIVATE
    ${Python3_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    include
)

# libraries
if (APPLE)
    # Explicit paths (mac)
    set(SDL2_LIB /opt/homebrew/lib/libSDL2.dylib)
    set(SDL2_IMAGE_LIB /opt/homebrew/lib/libSDL2_image.dylib)
    target_link_libraries(easyPyEngine PRIVATE
        ${Python3_LIBRARIES}
        ${SDL2_LIB}
        ${SDL2_IMAGE_LIB}
    )

    set_target_properties(easyPyEngine PROPERTIES
        INSTALL_RPATH "@loader_path"
        BUILD_WITH_INSTALL_RPATH ON
    )
endif()

if (LINUX)
    # Explicit paths (linux)
    set(SDL2_LIB_PATH /usr/lib/x86_64-linux-gnu/libSDL2.so)
    set(SDL2_IMAGE_LIB_PATH /usr/lib/x86_64-linux-gnu/libSDL2_image.so)
endif()

if (WIN32)
    # N E E D S   A D J U S T E M E N T S
    set(SDL2_LIB_PATH "C:/SDL2/lib/x64/SDL2.lib")
    set(SDL2_IMAGE_LIB_PATH "C:/SDL2_image/lib/x64/SDL2_image.lib")
endif()

# target_link_libraries(easyPyEngine PRIVATE
#     ${Python3_LIBRARIES}
#     ${SDL2_LIB_PATH}
#     ${SDL2_IMAGE_LIB_PATH}
# )
