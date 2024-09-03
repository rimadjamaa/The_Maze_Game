#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>

SDL_Renderer* init_renderer(SDL_Window* window);
void render_clear(SDL_Renderer* renderer);
void render_draw(SDL_Renderer* renderer);
void cleanup_renderer(SDL_Renderer* renderer);

#endif 


