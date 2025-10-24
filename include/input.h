#ifndef INPUT_H
#define INPUT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <SDL2/SDL.h>
#include "engine.h"


int is_key_pressed(EngineObject *engine, const char *keyName);


#ifdef __cplusplus
}
#endif

#endif