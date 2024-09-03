#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include "map.h"

typedef struct {
    int x, y; // Position
    int w, h;
    float angle;
} Player;

void init_player(Player *p);
void move_player(Player *player, int distance);
void render_player(SDL_Renderer *renderer, Player *p);
void render_lights(SDL_Renderer *renderer, Player *player, int map[MAP_HEIGHT][MAP_WIDTH]);

#endif // PLAYER_H
