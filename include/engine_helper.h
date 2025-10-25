#include "engine.h"
#include "sprite.h"

// Create and initialize an EngineObject
EngineObject* engine_create(const char* title, int width, int height);

// Destroy EngineObject
void engine_destroy(EngineObject* engine);

// Load a sprite using an EngineObject
SpriteObject* sprite_load(EngineObject* engine, int width, int height, const char* path);
