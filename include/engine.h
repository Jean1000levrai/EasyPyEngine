#include <SDL2/SDL.h>
#include <Python.h>

#ifndef ENGINE_H
#define ENGINE_H

#ifdef __cplusplus
extern "C" {
#endif


// S T R U C T U R E S

typedef struct{
    PyObject_HEAD
    SDL_Window *window;
    SDL_Renderer *renderer;
    int running;
    Uint64 last_time;
    const Uint8 *keyboard_state;

} EngineObject ;


// F U N C T I O N S

void engine_init(EngineObject *self, char *title, int width, int height);
void engine_clear(EngineObject *self, int r, int g, int b);
void engine_run(EngineObject *self, void (*update_callback)(EngineObject *self, float dt));
void engine_quit(EngineObject *self);



#ifdef __cplusplus
}
#endif

#endif
