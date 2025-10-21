#include <SDL2/SDL.h>
#include <Python.h>

typedef struct{
    PyObject_HEAD
    SDL_Window *window;
    SDL_Renderer *renderer;
    int running;
    Uint64 last_time;
    const Uint8 *keyboard_state;

} EngineObject ;

