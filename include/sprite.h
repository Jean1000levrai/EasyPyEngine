#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Python.h>
#include "engine.h"

#ifdef __cplusplus
extern "C" {
#endif

// F U N C T I O N S




// S T R U C T U R E S

typedef struct{
    PyObject_HEAD
    SDL_Renderer *renderer;
    int x;
    int y;
    int width;
    int height;
} SpriteObject;


#ifdef __cplusplus
}
#endif

#endif