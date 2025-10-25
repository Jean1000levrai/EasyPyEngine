# engine_wrapper.pyx
from libc.stdlib cimport malloc, free, NULL

# ---- SDL ----
cdef extern from "SDL2/SDL.h":
    cdef struct SDL_Renderer:
        pass

# ---- Engine core ----
cdef extern from "engine.h":
    cdef struct EngineObject:
        SDL_Renderer *renderer

    void engine_init(EngineObject *self, const char *title, int width, int height)
    void engine_run(EngineObject *self, void (*update_callback)(EngineObject *self, float dt))
    void engine_clear(EngineObject *self, unsigned char r, unsigned char g, unsigned char b)
    void engine_quit(EngineObject *self)

# ---- Graphics functions ----
cdef extern from "graphics.h":
    void draw_rect(EngineObject *engine, int x, int y, int width, int height,
                   int r, int g, int b, int filled)
    void draw_line(EngineObject *engine, int x1, int y1, int x2, int y2,
                   int r, int g, int b)

# ---- Sprite management ----
cdef extern from "sprite.h":
    cdef struct SpriteObject:
        pass

    SpriteObject* load_sprite(SDL_Renderer *renderer, int width, int height, const char *path)
    void draw_sprite(EngineObject *engine, SpriteObject *sprite, int x, int y)
    void free_sprite(SpriteObject *sprite)

# ---- Input handling ----
cdef extern from "input.h":
    int is_key_pressed(EngineObject *engine, const char *keyName)


# --------
# Callback bridge (C -> Python)
# --------
cdef object py_callback = None

cdef void _update_callback(EngineObject *self, float dt) except *:
    with gil:
        if py_callback is not None:
            py_callback(dt)

# --------
# Python-exposed Engine class
# --------
cdef class Engine:
    cdef EngineObject *_engine

    def __cinit__(self, str title, int width, int height):
        self._engine = <EngineObject *> malloc(sizeof(EngineObject))
        if not self._engine:
            raise MemoryError("Failed to allocate EngineObject")
        engine_init(self._engine, title.encode("utf-8"), width, height)

    def run(self, callback):
        global py_callback
        py_callback = callback
        engine_run(self._engine, _update_callback)

    def clear(self, tuple color=(0, 0, 0)):
        r, g, b = color
        engine_clear(self._engine, r, g, b)

    def quit(self):
        if self._engine != NULL:
            engine_quit(self._engine)
            free(self._engine)
            self._engine = NULL

    def is_key_pressed(self, str keyName):
        return bool(is_key_pressed(self._engine, keyName.encode("utf-8")))

    def draw_rect(self, int x, int y, int width, int height,
                  tuple color=(255, 255, 255), int filled=1):
        r, g, b = color
        draw_rect(self._engine, x, y, width, height, r, g, b, filled)

    def draw_line(self, int x1, int y1, int x2, int y2, tuple color=(255, 255, 255)):
        r, g, b = color
        draw_line(self._engine, x1, y1, x2, y2, r, g, b)

    def draw_sprite(self, Sprite sprite, int x, int y):
        draw_sprite(self._engine, sprite._sprite, x, y)


# --------
# Sprite class
# --------
cdef class Sprite:
    cdef SpriteObject *_sprite

    def __cinit__(self, Engine engine, int width, int height, str path):
        self._sprite = load_sprite(engine._engine.renderer, width, height, path.encode("utf-8"))
        if not self._sprite:
            raise MemoryError("Failed to load sprite")

    def draw(self, Engine engine, int x, int y):
        draw_sprite(engine._engine, self._sprite, x, y)

    def free(self):
        if self._sprite != NULL:
            free_sprite(self._sprite)
            self._sprite = NULL