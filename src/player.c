#include "../headers/player.h"


// Initialize the player
Player player ; // Example initial position

// Define functions to manipulate the player
void init_player(Player *p) {
    p->x = 50;
    p->y = 50;
    p->w = 20;  // Width of the player
    p->h = 20;  // Height of the player
    p->angle = 0;
}

// Check if the new position is valid (not colliding with a wall)
int is_valid_position(int x, int y) {
    if (x < 0 || x + 20 > MAP_WIDTH * TILE_SIZE || y < 0 || y + 20 > MAP_HEIGHT * TILE_SIZE) {
        return 0; // Out of bounds
    }

    int mapX1 = x / TILE_SIZE;
    int mapY1 = y / TILE_SIZE;

    int mapX2 = (x + 19) / TILE_SIZE; // x + width - 1
    int mapY2 = (y + 19) / TILE_SIZE; // y + height - 1

    // Check all four corners of the player's bounding box
    return get_map_tile(mapX1, mapY1) == 0 &&
           get_map_tile(mapX2, mapY1) == 0 &&
           get_map_tile(mapX1, mapY2) == 0 &&
           get_map_tile(mapX2, mapY2) == 0;
}


void move_player(Player *player, int distance) {
    // Calculate the change in position based on the player's angle
    int dx = cos(player->angle * M_PI / 180.0) * distance;
    int dy = sin(player->angle * M_PI / 180.0) * distance;

    // Calculate new position
    int new_x = player->x + dx;
    int new_y = player->y + dy;

    // Check if the new position is valid
    if (is_valid_position(new_x, new_y)) {
        player->x = new_x;
        player->y = new_y;
    }
}

// Function to render the lights based on the player's angle
void render_lights(SDL_Renderer *renderer, Player *player, int map[MAP_HEIGHT][MAP_WIDTH]) {
    int FOV = 60; // Field of View in degrees
    int num_rays = 100; // Number of rays to cast
    double ray_angle_step = FOV / (double)num_rays; // Angle step between each ray

    // Calculate the center of the player rectangle
    int center_x = player->x + player->w / 2;
    int center_y = player->y + player->h / 2;

    int i;
    for (i = 0; i < num_rays; i++) {
        // Calculate the angle of the current ray
        double ray_angle = (player->angle - FOV / 2.0) + i * ray_angle_step;
        double ray_angle_rad = ray_angle * M_PI / 180.0;

        double ray_x = center_x;
        double ray_y = center_y;
        double light_length = 300; // Maximum length of the light ray
        double step_size = 1; // Step size for raycasting

        // Cast the ray
        while (1) {
            ray_x += cos(ray_angle_rad) * step_size;
            ray_y += sin(ray_angle_rad) * step_size;

            // Check if the ray hits a wall
            int map_x = (int)(ray_x / TILE_SIZE);
            int map_y = (int)(ray_y / TILE_SIZE);

            if (map[map_y][map_x] != 0) {
                break;
            }

            // Draw the light ray
            if (sqrt(pow(ray_x - center_x, 2) + pow(ray_y - center_y, 2)) < light_length) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow light
                SDL_RenderDrawLine(renderer, center_x, center_y, (int)ray_x, (int)ray_y);
            }
        }
    }
}

void render_player(SDL_Renderer *renderer, Player *p) {
    SDL_Rect rect = {p->x, p->y, p->h, p->w}; // Example player size
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Red color
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderDrawLine(renderer, player.x, player.y, 
                   player.x + cos(player.angle * M_PI / 180.0) * 20, 
                   player.y + sin(player.angle * M_PI / 180.0) * 20);
}




void render_3d_view(SDL_Renderer *renderer, Player *player, int map[MAP_HEIGHT][MAP_WIDTH]) {
    int screen_width = 800; // Adjust to your screen width
    int screen_height = 600; // Adjust to your screen height
    int FOV = 60; // Field of View in degrees
    int num_rays = screen_width; // Number of rays equals screen width for a 1:1 pixel ratio
    double ray_angle_step = (double)FOV / (double)num_rays; // Angle step between each ray

    double player_angle_rad = player->angle * M_PI / 180.0; // Convert player angle to radians

    // Define colors for ground and ceiling
    SDL_Color ground_color = {0, 255, 0, 255}; // Green
    SDL_Color ceiling_color = {0, 0, 255, 255}; // Blue

    int i;
    for (i = 0; i < num_rays; i++) {
        double ray_angle = (player->angle - FOV / 2.0) + i * ray_angle_step;
        double ray_angle_rad = ray_angle * M_PI / 180.0;

        double ray_x = player->x;
        double ray_y = player->y;
        double distance_to_wall = 0;

        while (1) {
            ray_x += cos(ray_angle_rad);
            ray_y += sin(ray_angle_rad);
            distance_to_wall += 1;

            int map_x = (int)(ray_x / TILE_SIZE);
            int map_y = (int)(ray_y / TILE_SIZE);

            // Check if ray hit a wall
            if (map[map_y][map_x] != 0) {
                break;
            }
        }

        // Correct fish-eye effect
        double perpendicular_distance = distance_to_wall * cos(ray_angle_rad - player_angle_rad);

        // Calculate height of the wall slice to draw
        int wall_height = (int)(screen_height / perpendicular_distance);

        // Determine start and end of the wall slice on the screen
        int wall_start = (screen_height / 2) - (wall_height / 2);
        int wall_end = wall_start + wall_height;

        // Draw ceiling
        SDL_SetRenderDrawColor(renderer, ceiling_color.r, ceiling_color.g, ceiling_color.b, ceiling_color.a);
        SDL_RenderDrawLine(renderer, i, 0, i, wall_start);

        // Draw wall slice
        SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255); // Gray wall color
        SDL_RenderDrawLine(renderer, i, wall_start, i, wall_end);

        // Draw ground
        SDL_SetRenderDrawColor(renderer, ground_color.r, ground_color.g, ground_color.b, ground_color.a);
        SDL_RenderDrawLine(renderer, i, wall_end, i, screen_height);
    }
}
