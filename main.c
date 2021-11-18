#include <SDL2/SDL.h>
// include <SDL2_ttf-devel>
#include <stdio.h>
#include <stdlib.h>
#include "components.h"

const int SCREEN_HEIGHT = 320;
const int SCREEN_WIDTH = 240;

// Prototypes
bool loadbitmap(SDL_Surface *surface, char *path);
bool ControlInput(SDL_Event event, SDL_Rect *sprite_position);
bool DetectCollision(SDL_Rect *a, SDL_Rect *b);
int aimovement(SDL_Rect *sprite_position);
void controlconversation();
void cleanup(void);


int main(int argc, char* argv[])
{
    // Game window
    SDL_Window *game_window;
    
    // Canvas level
    SDL_Surface *screen_surface;
    
    // Background image
    SDL_Surface *map_surface;
    
    sprite cap_sprite;
    cap_sprite.entity_id = 1;
    cap_sprite.sprite_surface = SDL_LoadBMP("resources/capred.bmp");

    position cap_sprite_position;
    cap_sprite_position.entity_id = 1;
    cap_sprite_position.sprite_position.x = 200;
    cap_sprite_position.sprite_position.y = 68;

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
    //loadbitmap(sprite_surface, "resources/capred.bmp");
    sprite_position.x = 200;
    sprite_position.y = 68;
    SDL_SetColorKey(sprite_surface, SDL_TRUE, SDL_MapRGB(sprite_surface->format, 255, 255, 255));


    bool quit = false;

    SDL_Event event;
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            // Event Controls
            ControlInput(event, &sprite_position);
            quit = ControlInput(event, &sprite_position);
            
            // Scene Control
            // stagemanager();

            // Collision Detection
            DetectCollision(&sprite_position, &green_alien_pos.sprite_position);

            // Rendering
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


bool ControlInput(SDL_Event event, SDL_Rect *sprite_position)
{
    bool quit = false;
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    if(event.type == SDL_QUIT || keystate[SDL_SCANCODE_Q])
    {
        quit = true;
        printf("SDL: Quit Event\n");
        return quit;
    }
    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        printf("SDL: Mouse Button Down");
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

    int mouse_x;
    int mouse_y;

    Uint32 SDL_GetMouseState(int *mouse_x, int *mouse_y);
    Uint32 buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

    // SDL_Log("Mouse cursor is at %d, %d", mouse_x, mouse_y);

    if ((buttons & SDL_BUTTON_LMASK) != 0) 
    {
        SDL_Log("Mouse Button 1 (left) is pressed.\nMouse cursor is at %d, %d", mouse_x, mouse_y);
    }

    return quit;
}


bool loadbitmap(SDL_Surface *surface, char *path)
{
    surface = SDL_LoadBMP(path);
    if (surface == NULL)
    {
        printf("Failed to load %s\n", path);
        return false;
    }
    return true;
}

bool DetectCollision(SDL_Rect *a, SDL_Rect *b)
{
    if (a->x == b->x && a->y == b->y)
    {
        printf("Collision Detected!\n");
        return true;
    }
    return false;
}

int aimovement(SDL_Rect *sprite_position)
{

}

void cleanup(void)
{
    //Free Surfaces and Destroy Windows
    ;
}