#ifndef EVENT_H
#define EVENT_H

#include <SDL2/SDL.h>
#include "player.h"

// Function to handle events
void handle_events(SDL_Event *event, Player *player);

#endif // EVENT_H
