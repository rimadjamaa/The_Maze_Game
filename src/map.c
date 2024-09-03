#include "../headers/map.h"
#include <SDL2/SDL.h>

/*Define the map layout*/ 
int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1},
    {1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

/*Function to return the value of a tile in the map*/ 
int get_map_tile(int x, int y) {
    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
        return map[y][x]; 
    } else {
        return -1; 
    }
}

/*Function to draw the map as a grid of rectangles*/ 
void draw_map(SDL_Renderer *renderer) {
    int tileSize = 50; /*Size of each tile on the screen*/ 
    int x, y;
    for (y = 0; y < MAP_HEIGHT; y++) {
        for ( x = 0 ; x < MAP_WIDTH; x++) {
            SDL_Rect rect;
            rect.x = x * tileSize;
            rect.y = y * tileSize;
            rect.w = tileSize;
            rect.h = tileSize;

            /*Draw walls in a different color*/ 
            if (map[y][x] == 0) {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); 
            } else {
                SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255); 
            }
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

