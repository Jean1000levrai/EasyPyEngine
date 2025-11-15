#include <SDL2/SDL.h>
#include <stdio.h>

#include "graphics.h"


void draw_rect(EngineObject *engine, int x, int y, int width, int height,
               int r, int g, int b, int filled) {
    SDL_Rect rect = {x, y, width, height};
    SDL_SetRenderDrawColor(engine->renderer, r, g, b, 255);

    if (filled)
        SDL_RenderFillRect(engine->renderer, &rect);
    else
        SDL_RenderDrawRect(engine->renderer, &rect);
}

void draw_line(EngineObject *engine, int x1, int y1, int x2, int y2,
               int r, int g, int b){
    SDL_SetRenderDrawColor(engine->renderer, r, g, b, 255);
    SDL_RenderDrawLine(engine->renderer, x1, y1, x2, y2);
}
