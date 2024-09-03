#ifndef MAP_H
#define MAP_H
#include <SDL2/SDL.h>

#define MAP_WIDTH 16
#define MAP_HEIGHT 12
#define TILE_SIZE 50

extern int map[MAP_HEIGHT][MAP_WIDTH];

/*Function declarations*/ 
void draw_map(SDL_Renderer *renderer);
int get_map_tile(int x, int y);

#endif /* MAP_H */
