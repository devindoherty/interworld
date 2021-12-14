// gcc -std=c17 main.c -IC:\Users\devin\dev\SDL2\include\SDL2 -LC:\Users\devin\Dev\SDL2\lib -Wall -lmingw32 -lSDL2main -lSDL2 -lsdl2_mixer -o main

#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "components.h"

const int SCREEN_HEIGHT = 360;
const int SCREEN_WIDTH = 360;

// Prototypes
bool loadbitmap(SDL_Surface *surface, char *path);
bool ControlInput(SDL_Event event, SDL_Rect *sprite_position, bool *title);
bool DetectCollision(SDL_Rect *a, SDL_Rect *b);
int DialogueMenu(struct dialogue);
int CharacterCreation(struct statistic);
void cleanup(void);


int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    // Game window
    SDL_Window *game_window;
    
    // Canvas surface to which all other surfaces are rendered
    SDL_Surface *screen_surface;
    
    // Background images
    SDL_Surface *map_surface;
    SDL_Surface *title_surface;
    
    // Player sprite surface, rect, and other information
    SDL_Surface *sprite_surface;
    SDL_Rect sprite_position;
    statistic player_stats;
    
    // ECS approach for nonplayer character
    sprite green_alien_onscreen;
    green_alien_onscreen.entity_id = 2;
    green_alien_onscreen.sprite_surface = SDL_LoadBMP("resources/greenalien.bmp");

    position green_alien_pos;
    green_alien_pos.entity_id = 2;
    green_alien_pos.sprite_position.x = 264;
    green_alien_pos.sprite_position.y = 198;

    // ECS approach for player
    // sprite cap_sprite;
    // cap_sprite.entity_id = 1;
    // cap_sprite.sprite_surface = SDL_LoadBMP("resources/capred.bmp");

    // position cap_sprite_position;
    // cap_sprite_position.entity_id = 1;
    // cap_sprite_position.sprite_position.x = 200;
    // cap_sprite_position.sprite_position.y = 68;

    // Music, possibly broken
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL Mixer could not init! SDL Error: %s\n", Mix_GetError());
    }
    Mix_Music *main_theme = NULL;
    main_theme = Mix_LoadMUS("resources/theme16.wav");
    if (main_theme == NULL)
    {
        printf("Theme not loaded SDL error: %s\n", Mix_GetError());
    }

    // Init the game window
    game_window = SDL_CreateWindow("Interworld ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                SCREEN_HEIGHT, SCREEN_WIDTH, 0);

    // Set canvas surface to be the window
    screen_surface = SDL_GetWindowSurface(game_window);
    
    // Set background surfaces to bitmaps
    map_surface = SDL_LoadBMP("resources/ship.bmp");
    title_surface = SDL_LoadBMP("resources/interworldtitlescreen.bmp");
    
    // Attempting clicking functionality for title screen start button
    SDL_Rect start_button;
    start_button.x = 113;
    start_button.y = 220;
    start_button.w = 80;
    start_button.h = 30;
    
    // loadbitmap(map_surface, "resources/brokenworld.bmp");

    sprite_surface = SDL_LoadBMP("resources/caprednew.bmp");
    //loadbitmap(sprite_surface, "resources/capred.bmp");
    sprite_position.x = 200;
    sprite_position.y = 68;
    
    // Makes white pixels for loaded sprite surfaces transparent
    SDL_SetColorKey(sprite_surface, SDL_TRUE, SDL_MapRGB(sprite_surface->format, 255, 255, 255));
    SDL_SetColorKey(green_alien_onscreen.sprite_surface, SDL_TRUE, SDL_MapRGB(green_alien_onscreen.sprite_surface->format, 255, 255, 255));

    bool quit = false;
    bool title = true;
    SDL_Event event;
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            // Event Controls
            // ControlInput(event, &sprite_position, &title);
            quit = ControlInput(event, &sprite_position, &title);
            
            // Scene Control
            // StageManager();

            // Collision Detection
            // DetectCollision(&sprite_position, &green_alien_pos.sprite_position);
            SDL_bool sprite_collision = SDL_HasIntersection(&sprite_position, &green_alien_pos.sprite_position);
            if (sprite_collision == true)
            {
                printf("Collision Detected!");
            }

            // Rendering and Music
            if (title == true)
            {
                SDL_BlitSurface(title_surface, NULL, screen_surface, NULL);
                SDL_UpdateWindowSurface(game_window);
                if (Mix_PlayingMusic() == 0)
                {
                    Mix_PlayMusic(main_theme, -1);
                }
                
            }
            else
            {
                Mix_PauseMusic();
                SDL_BlitSurface(map_surface, NULL, screen_surface, NULL);
                SDL_BlitSurface(sprite_surface, NULL, screen_surface, &sprite_position);
                SDL_BlitSurface(green_alien_onscreen.sprite_surface, NULL, screen_surface, &green_alien_pos.sprite_position);
                SDL_UpdateWindowSurface(game_window);
            }
        }
    }

    SDL_FreeSurface(map_surface);
    SDL_FreeSurface(title_surface);
    SDL_FreeSurface(sprite_surface);
    SDL_FreeSurface(green_alien_onscreen.sprite_surface);
    Mix_FreeMusic(main_theme);
    SDL_DestroyWindow(game_window);
    Mix_Quit();
    SDL_Quit();
    return 0;
}


bool ControlInput(SDL_Event event, SDL_Rect *sprite_position, bool *title)
{
    // Quit condition
    bool quit = false;
    
    // From SDL documentation, pointer to SDL array containing state of keys
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    if (*title == true)
    {
        if(keystate[SDL_SCANCODE_SPACE])
        {
            printf("End Title Screen\n");
            *title = false;
        }
        if (event.type == SDL_QUIT || keystate[SDL_SCANCODE_Q] || keystate[SDL_SCANCODE_ESCAPE])
        {
            quit = true;
            printf("SDL: Quit Event\n");
            return quit;
        }
    }   
    if(event.type == SDL_QUIT || keystate[SDL_SCANCODE_Q] || keystate[SDL_SCANCODE_ESCAPE])
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
    if(keystate[SDL_SCANCODE_C])
    {
        printf("SDL: C\n");
    }

    // Init mouse x,y position
    int mouse_x;
    int mouse_y;

    // SDL function to find mouse location
    Uint32 SDL_GetMouseState(int *mouse_x, int *mouse_y);
    Uint32 buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

    // SDL_Log("Mouse cursor is at %d, %d", mouse_x, mouse_y);

    if ((buttons & SDL_BUTTON_LMASK) != 0) 
    {
        SDL_Log("Mouse Button 1 (left) is pressed.\nMouse cursor is at %d, %d", mouse_x, mouse_y);
    }

    return quit;
}

// Function to load bitmaps
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

// Framework for a basic terminal multiple choice dialogue system
int DialogueMenu(dialogue talk)
{

}

// Framework for a basic character stat system
int CharacterCreation(statistic player_stats)
{
    player_stats;
    int stat_points = 10;
    for (int i = 0; stat_points != 0; i++)
    {
        printf("Choose an attribute to increase:\na. Command\nb. Tactical\n c. Operations\nStat Points: %i", stat_points);
        char selection = scanf("%c", selection);
        if (selection == 'a')
        {
            player_stats.command++;
            stat_points--;
        }
        if (selection == 'b')
        {
            player_stats.tactical++;
            stat_points--;
        }
        if (selection == 'c')
        {
            player_stats.operations++;
            stat_points--;
        }
    }
}

// Detects Collisions, depreciated in favor of SDL_HasIntersection
// bool DetectCollision(SDL_Rect *a, SDL_Rect *b)
// {
//     if (a->x == b->x && a->y == b->y)
//     {
//         printf("Collision Detected!\n");
//         return true;
//     }
//     return false;
// }
