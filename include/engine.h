#include <SDL2/SDL.h>
#include <Python.h>

#ifndef ENGINE_H
#define ENGINE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
    PyObject_HEAD
    SDL_Window *window;
    SDL_Renderer *renderer;
    int running;
    Uint64 last_time;
    const Uint8 *keyboard_state;

} EngineObject ;


#ifdef __cplusplus
}
#endif

#endif
