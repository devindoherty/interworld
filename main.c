#include <SDL2/SDL.h>
#include <stdio.h>
#include "components.h"

const int SCREEN_HEIGHT = 640;
const int SCREEN_WIDTH = 480;

// Prototypes
bool loadbitmap(SDL_Surface *surface, char *path);
bool controlkeys(SDL_Event event, SDL_Rect *sprite_position);
void cleanup(void);

int main(int argc, char* argv[])
{
    // Game window
    SDL_Window *game_window;
    
    // Canvas level
    SDL_Surface *screen_surface;
    
    // Background image
    SDL_Surface *map_surface;
    
    // Test sprite surface and rect
    SDL_Surface *sprite_surface;
    SDL_Rect sprite_position;
    
    // ECS approach
    sprite green_alien_onscreen;
    green_alien_onscreen.entity_id = 2;
    green_alien_onscreen.sprite_surface = SDL_LoadBMP("resources/greenalien.bmp");

    position green_alien_pos;
    green_alien_pos.entity_id = 2;
    green_alien_pos.sprite_position.x = 264;
    green_alien_pos.sprite_position.y = 198;


    game_window = SDL_CreateWindow("Interworld ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                SCREEN_HEIGHT, SCREEN_WIDTH, 0);

    screen_surface = SDL_GetWindowSurface(game_window);
    
    map_surface = SDL_LoadBMP("resources/brokenworld.bmp");
    
    // loadbitmap(map_surface, "resources/brokenworld.bmp");

    sprite_surface = SDL_LoadBMP("resources/capred.bmp");
    sprite_position.x = 200;
    sprite_position.y = 68;


    bool quit = false;

    SDL_Event event;
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    Uint32 SDL_GetMouseState(int *mouse_x, int *mouse_y);

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            controlkeys(event, &sprite_position);
            quit = controlkeys(event, &sprite_position);
            SDL_BlitSurface(map_surface, NULL, screen_surface, NULL);
            SDL_BlitSurface(sprite_surface, NULL, screen_surface, &sprite_position);
            SDL_BlitSurface(green_alien_onscreen.sprite_surface, NULL, screen_surface, &green_alien_pos.sprite_position);
            SDL_UpdateWindowSurface(game_window);
        }
    }

    SDL_FreeSurface(map_surface);
    SDL_FreeSurface(sprite_surface);
    SDL_FreeSurface(green_alien_onscreen.sprite_surface);
    SDL_DestroyWindow(game_window);
    SDL_Quit();
    return 0;
}


bool controlkeys(SDL_Event event, SDL_Rect *sprite_position)
{
    bool quit = false;
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    if(event.type == SDL_QUIT || keystate[SDL_SCANCODE_Q])
    {
        quit = true;
        printf("SDL: Quit Event\n");
        return quit;
    }
    if (keystate[SDL_SCANCODE_UP])
    {
        sprite_position->y -= 2;
        printf("SDL: Up Key\n");
        printf("Player X: %i\nPlayer Y: %i\n", sprite_position->x, sprite_position->y);
    }
    if (keystate[SDL_SCANCODE_DOWN])
    {
        sprite_position->y += 2;
        printf("SDL: Down Key\n");
        printf("Player X: %i\nPlayer Y: %i\n", sprite_position->x, sprite_position->y);
    }
    if (keystate[SDL_SCANCODE_LEFT])
    {
        sprite_position->x -= 2;
        printf("SDL: Left Key\n");
        printf("Player X: %i\nPlayer Y: %i\n", sprite_position->x, sprite_position->y);
    }
    if (keystate[SDL_SCANCODE_RIGHT])
    {
        sprite_position->x += 2;
        printf("SDL: Right Key\n");
        printf("Player X: %i\nPlayer Y: %i\n", sprite_position->x, sprite_position->y);
    }

    return quit;
}


bool loadbitmap(SDL_Surface *surface, char *path)
{
    surface = SDL_LoadBMP(path);
    if (surface == NULL)
    {
        return false;
    }
    return true;
}

