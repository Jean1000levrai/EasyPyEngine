#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "engine.h"
#include "graphics.h"
// #include "input.h"
#include "sprite.h"

// U S E F U L  F U N C T I O N S

static void sdl_die(const char *msg) {
    fprintf(stderr, "SDL ERROR: %s: %s\n", msg, SDL_GetError());
    IMG_Quit();
    SDL_Quit();
    exit(1);
}


// E N G I N E  F U N C T I O N S

void update_callback(EngineObject *self, float dt){
    // update callback

    draw_rect(self, 100, 100, 100, 100, 255, 0, 0, 1);
    draw_rect(self, 500, 100, 100, 100, 0, 0, 255, 0);
    draw_line(self, 100, 300, 600, 500, 0, 255, 0);
    SpriteObject *sprite = load_sprite(self->renderer, 100, 100, "../assets/profilePicV1.2.png");
    draw_sprite(self, sprite, 400, 200);
    draw_sprite(self, sprite, 500, 200);
    free_sprite(sprite);

    // printf("%d\n", is_key_pressed(self, "w"));
}

void engine_init(EngineObject *self, char *title, int width, int height){
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        sdl_die("init failed");
    }

    // Initialize SDL_image
    int img_flags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(img_flags) & img_flags)) {
        sdl_die("ERROR: IMG_Init failed");
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

void engine_run(EngineObject *self, void (*update_callback)(EngineObject *self, float dt)){
    // main loop
    Uint64 last_time = SDL_GetPerformanceCounter();
    SDL_Event event;

    while (self->running) {
        // --- Input & events ---
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                self->running = 0;
            }
        }

        // --- update keyboard state ---
        self->keyboard_state = SDL_GetKeyboardState(NULL);
        
        // --- delta time ---
        Uint64 now = SDL_GetPerformanceCounter();
        float dt = (float)(now - last_time) / SDL_GetPerformanceFrequency();
        last_time = now;

        // --- Rendering & callback ---
        engine_clear(self, 0, 0, 0);
        update_callback(self, dt);
        SDL_RenderPresent(self->renderer);

        // Delay to limit cpu usage, optimisation
        // small compromise between performance and cpu usage
        SDL_Delay(1);

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
    engine_run(&engine, update_callback);  
    engine_quit(&engine);


    return 0;
}