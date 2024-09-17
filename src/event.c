// event.c
#include "../headers/event.h"

void handle_events(SDL_Event *event, Player *player) {
    // Check if an event is a key press
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_UP:
                move_player(player, 5); // Move forward in the direction of the angle
                break;
            case SDLK_DOWN:
                move_player(player, -5); // Move backward in the opposite direction
                break;
            case SDLK_LEFT:
                player->angle -= 5;  // Rotate left (decrease angle)
                break;
            case SDLK_RIGHT:
                player->angle += 5;  // Rotate right (increase angle)
                break;
            default:
                break;
        }
    }
}


