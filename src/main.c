#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>
#include "../headers/all_headers.h"

const int WIDTH = 800, HEIGHT = 600;


void render(SDL_Renderer *renderer, Player *player, int map[MAP_HEIGHT][MAP_WIDTH]) {
    // Render the map and other game elements...

    // Render lights based on the player's angle
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow light
    render_lights(renderer, player, map);

    SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
    /* Declare variables at the start */
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *surface = NULL;
    SDL_Surface *text_surface = NULL;
    SDL_Event windowEvent;
    int running = 1;
    
    
    (void)argc;
    (void)argv;

    /* Initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    /* Create an SDL window */
    window = SDL_CreateWindow("WELCOM TO MY MAZE GAME",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              WIDTH, HEIGHT,
                              SDL_WINDOW_ALLOW_HIGHDPI);

    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    /* Create a renderer */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    /* Load a font and create a text surface (assuming you have SDL_ttf) */
    surface = SDL_GetWindowSurface(window);
    if (!surface) {
        fprintf(stderr, "SDL_GetWindowSurface Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    /* Set the window color to white */
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255));
    
    /* Draw text on the window surface */
    text_surface = SDL_CreateRGBSurfaceWithFormat(0, WIDTH, HEIGHT, 32, SDL_PIXELFORMAT_RGBA32);
    SDL_FillRect(text_surface, NULL, SDL_MapRGB(text_surface->format, 0, 0, 0)); // Black text background
    SDL_BlitSurface(text_surface, NULL, surface, NULL);
    
    SDL_UpdateWindowSurface(window);

     // Initialize the player
    Player player;
    
    init_player(&player);

    /* Main loop */
    while (running)
    {
        /* Poll events */
        while (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT) {
                running = 0;
            }
            else {
                // Handle events
                handle_events(&windowEvent, &player);
            }
        }

        /* Render the window surface */
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Clear screen with black
        SDL_RenderClear(renderer);
        
        draw_map(renderer);    // Draw the map
        //render_3d_view(renderer,&player,map);
        render_player(renderer, &player);// Draw the player

        render(renderer, &player, map);
        SDL_RenderPresent(renderer); // Present the renderer
        SDL_Delay(16); // Approx 60 FPS
    }

    /* Clean up */
    SDL_FreeSurface(text_surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


