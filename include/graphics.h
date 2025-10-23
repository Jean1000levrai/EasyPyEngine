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

void draw_line(EngineObject *engine, int x1, int y1, int x2, int y2,
               int r, int g, int b);



#ifdef __cplusplus
}
#endif

#endif