#include "input.h"

int is_key_pressed(EngineObject *engine, const char *keyName){
    SDL_Scancode code = SDL_GetScancodeFromName(keyName);
    if (code == SDL_SCANCODE_UNKNOWN) {
        return 0;
    }
    return engine->keyboard_state[code];
}

