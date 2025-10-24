#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <Python.h>
#include "engine.h"

#ifdef __cplusplus
extern "C" {
#endif

// S T R U C T U R E S

typedef struct{
    PyObject_HEAD
    SDL_Texture *texture;
    int x;
    int y;
    int width;
    int height;
} SpriteObject;


// F U N C T I O N S

SpriteObject* load_sprite(SDL_Renderer *renderer, int width, int height, const char *path);
void draw_sprite(EngineObject *engine, SpriteObject *sprite, int x, int y);
void free_sprite(SpriteObject *sprite);




#ifdef __cplusplus
}
#endif

#endif