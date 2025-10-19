#include <SDL2/SDL.h>
#include <Python.h>
#include <stdio.h>
#include "../include/engine.h"

// clang main.c -o main $(sdl2-config --cflags --libs)



void engine_init(EngineObject *self, char *title, int width, int height){
    self->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    self->renderer = SDL_CreateRenderer(self->window, -1, 0);
    self->running = 1;
}