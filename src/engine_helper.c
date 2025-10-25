#include <stdlib.h>
#include "engine_helper.h"

EngineObject* engine_create(const char* title, int width, int height) {
    EngineObject* e = (EngineObject*)malloc(sizeof(EngineObject));
    if (!e) return NULL;
    engine_init(e, title, width, height);
    return e;
}

void engine_destroy(EngineObject* engine) {
    if (engine) {
        engine_quit(engine);
        free(engine);
    }
}

SpriteObject* sprite_load(EngineObject* engine, int width, int height, const char* path) {
    return load_sprite(engine->renderer, width, height, path);
}
