#include <SDL2/SDL.h>

// clang main.c -o main $(sdl2-config --cflags --libs)

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Quit();
    return 0;
}