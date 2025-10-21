#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <Python.h>
#include "engine.h"

#ifdef __cplusplus
extern "C" {
#endif

// F U N C T I O N S

void draw_rect(EngineObject *engine, int x, int y, int width, int height,
               int r, int g, int b, int filled);

// S T R U C T U R E S
typedef struct{
    PyObject_HEAD
    SDL_Renderer *renderer;
    int x;
    int y;
    int width;
    int height;
} SpriteObject;

// C O N S T A N T S


#ifdef __cplusplus
}
#endif

#endif