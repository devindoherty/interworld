#include <SDL2/SDL.h>
#include <stdio.h>
// #include <structures.h>

const int SCREEN_HEIGHT = 320;
const int SCREEN_WIDTH = 240;

int main(int argc, char* argv[])
{

    SDL_Window *game_window;
    SDL_Surface *screen_surface;
    SDL_Surface *map_surface;
    SDL_Surface *sprite_surface;
    SDL_Rect sprite_position;

    game_window = SDL_CreateWindow("Interworld ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                SCREEN_HEIGHT, SCREEN_WIDTH, 0);

    screen_surface = SDL_GetWindowSurface(game_window);
    
    map_surface = SDL_LoadBMP("resources/brokenworld.bmp");
    
    sprite_surface = SDL_LoadBMP("resources/capred.bmp");
    sprite_position.x = 20;
    sprite_position.y = 20;


    bool quit = false;

    SDL_Event event;
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    Uint32 SDL_GetMouseState(int *mouse_x, int *mouse_y);

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT || keystate[SDL_SCANCODE_Q])
            {
                quit = true;
                printf("SDL: Quit Event\n");
            }
            if (keystate[SDL_SCANCODE_DOWN])
            {
                sprite_position.y += 2;
            }
            if (keystate[SDL_SCANCODE_UP])
            {
                sprite_position.y -= 2;
            }
            if (keystate[SDL_SCANCODE_RIGHT])
            {
                sprite_position.x += 2;
            }
            if (keystate[SDL_SCANCODE_LEFT])
            {
                sprite_position.x -= 2;
            }
            if (SDL_BUTTON_LEFT == 0)
            {
                // printf("Left Mouse Button Clicked!");
            }

            SDL_BlitSurface(map_surface, NULL, screen_surface, NULL);
            SDL_BlitSurface(sprite_surface, NULL, screen_surface, &sprite_position);
            SDL_UpdateWindowSurface(game_window);
        
        }
    }

    SDL_FreeSurface(map_surface);
    SDL_DestroyWindow(game_window);
    SDL_Quit();
    return 0;
}