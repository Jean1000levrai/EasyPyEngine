#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/engine.h"

static void sdl_die(const char *msg) {
    fprintf(stderr, "SDL ERROR: %s: %s\n", msg, SDL_GetError());
    SDL_Quit();
    exit(1);
}


void engine_init(EngineObject *self, char *title, int width, int height){
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        sdl_die("init failed");
    }

    // Create window
    self->window = SDL_CreateWindow(title, 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        width, height, 0);

    if (!self->window ) {
        sdl_die("window creation failed");
    }

    // Create renderer
    self->renderer = SDL_CreateRenderer(self->window, 
        -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        
    if (!self->renderer) {
        SDL_DestroyWindow(self->window);
        sdl_die("renderer creation failed");
    }

    self->keyboard_state = SDL_GetKeyboardState(NULL);

    self->running = 1;
}

void engine_clear(EngineObject *self, int r, int g, int b){
    // clear screen
    SDL_SetRenderDrawColor(self->renderer, r, g, b, 255);
    SDL_RenderClear(self->renderer);
}

void engine_run(EngineObject *self){
    // main loop
    SDL_Event event;
    while (self->running) {
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                self->running = 0;
            }
        engine_clear(self, 0, 0, 0);
        SDL_RenderPresent(self->renderer);
        }
    }
}

void engine_quit(EngineObject *self){
    // quits the engine
    SDL_DestroyRenderer(self->renderer);
    SDL_DestroyWindow(self->window);
    SDL_Quit();
}

int main(){
    EngineObject engine;

    engine_init(&engine, "test", 1000, 500);
    engine_run(&engine);  
    engine_quit(&engine);

    return 0;
}