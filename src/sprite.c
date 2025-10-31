#include "sprite.h"
#include "SDL2/SDL_image.h"


SpriteObject* load_sprite(SDL_Renderer *renderer, int width, int height, const char *path) {
    SDL_Surface *surface = IMG_Load(path);
    if (!surface) {
        printf("ERROR: failed to load image %s: %s\n", path, IMG_GetError());
        return NULL;
    }

    SDL_Texture* texture;
    if (strcmp(path, "") == 0){
        texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET,
            width,
            height
        );
    } else {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!texture) {
            printf("ERROR: failed to create texture from %s: %s\n", path, SDL_GetError());
            SDL_FreeSurface(surface);
            return NULL;
        }
    }


    SpriteObject *sprite = malloc(sizeof(SpriteObject));
    if (!sprite) {
        printf("ERROR: failed to allocate memory for sprite\n");
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
        return NULL;
    }

    sprite->texture = texture;

    int tex_w, tex_h;
    SDL_QueryTexture(texture, NULL, NULL, &tex_w, &tex_h);
    sprite->width  = (width  > 0) ? width  : tex_w;
    sprite->height = (height > 0) ? height : tex_h;

    SDL_FreeSurface(surface);
    return sprite;
}

void draw_sprite(EngineObject *engine, SpriteObject *sprite, float x, float y){
    // draw sprite
    SDL_Rect rect = {x, y, sprite->width, sprite->height};
    sprite->x = x;
    sprite->y = y;
    SDL_RenderCopy(engine->renderer, sprite->texture, NULL, &rect);

}

void free_sprite(SpriteObject *sprite){
    // free sprite
    SDL_DestroyTexture(sprite->texture);
    free(sprite);
}