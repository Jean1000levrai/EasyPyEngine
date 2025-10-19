#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/engine.h"


void engine_init(EngineObject *self, char *title, int width, int height){
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("ERROR: init failed, %s\n", SDL_GetError());
        exit(1);
    }

    self->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (!self->window ) {
        printf("ERROR: window creation failed, %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
    self->renderer = SDL_CreateRenderer(self->window, -1, 0);
    if (!self->renderer) {
        printf("ERROR: renderer creation failed, %s\n", SDL_GetError());
        SDL_DestroyWindow(self->window);
        SDL_Quit();
        exit(1);
    }
    self->running = 1;
}

void engine_run(EngineObject *self){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT){
            self->running = 0;
        }
    }
}

void engine_clear(EngineObject *self, int r, int g, int b){
    SDL_SetRenderDrawColor(self->renderer, r, g, b, 255);
    SDL_RenderClear(self->renderer);
}

void engine_quit(EngineObject *self){
    SDL_DestroyRenderer(self->renderer);
    SDL_DestroyWindow(self->window);
    SDL_Quit();
}

int main(){
    EngineObject engine;
    engine_init(&engine, "test", 1000, 500);
    
    while (engine.running){
        engine_run(&engine);
        engine_clear(&engine, 0, 0, 0);  // clear screen each frame
        SDL_RenderPresent(engine.renderer);  // show contents
    }
    
    engine_quit(&engine);
    return 0;
}