#include "renderer.h"
#include <stdio.h>

SDL_Renderer* init_renderer(SDL_Window* window)
{
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return NULL;
    }
    return renderer;
}

void render_clear(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
    SDL_RenderClear(renderer);
}

void render_draw(SDL_Renderer* renderer)
{
    /*Draw a white rectangle*/ 
    SDL_Rect rect = {100, 100, 200, 150};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
    SDL_RenderFillRect(renderer, &rect);
}

void cleanup_renderer(SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
}
