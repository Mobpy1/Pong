#define SDL_MAIN_HANDLED // Tell SDL to use our main function

#include <SDL2/SDL.h>
#include <stdio.h>


#define WHITE 0xffffffff // Color White
#define BLACK 0x00000000 // Color Black

static int MOVEMENT_SPEED = 20;


void move_playerUP(SDL_Surface* surface , SDL_Rect* rect, int movement) 
{
    if( rect->y >= 20){
        SDL_FillRect(surface, rect, BLACK);
        rect->y -= movement;
        SDL_FillRect(surface, rect, WHITE);
        printf("Y =  %d\n", rect->y);
    }
}

void move_playerDOWN(SDL_Surface *surface, SDL_Rect *rect, int movement)
{
    if (rect->y <= 440)
    {
        SDL_FillRect(surface, rect, BLACK);
        rect->y += movement;
        SDL_FillRect(surface, rect, WHITE);
        printf("Y = %d\n",rect->y);
    }
}


int main()
{
    SDL_InitSubSystem(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("I Love Julija", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 640, 0);
    
    if (window == NULL)
    {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Surface *surface = SDL_GetWindowSurface(window);


    SDL_Rect player_1 = (SDL_Rect){40,40,40,200};
    SDL_Rect player_2 = (SDL_Rect){550,40,40,200}; 
    
    SDL_FillRect(surface, &player_1, WHITE);
    SDL_FillRect(surface, &player_2 ,WHITE);

    

    SDL_Event event;
    int quit = 0;

    while (!quit)
    {
        SDL_UpdateWindowSurface(window);

        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) // If the window close button is clicked
        {
            quit = 1;
        }
        if (event.key.keysym.sym == SDLK_w )
        {
            move_playerUP(surface ,&player_1,MOVEMENT_SPEED);
        }
        if (event.key.keysym.sym == SDLK_s)
        {
            move_playerDOWN(surface, &player_1, MOVEMENT_SPEED);
        }
        if (event.key.keysym.sym == SDLK_UP)
        {
            move_playerUP(surface, &player_2, MOVEMENT_SPEED);
        }
        if (event.key.keysym.sym == SDLK_DOWN)
        {
            move_playerDOWN(surface, &player_2, MOVEMENT_SPEED);
        }    
    }
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
