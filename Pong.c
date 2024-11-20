#define SDL_MAIN_HANDLED // Tell SDL to use main function

#include <SDL2/SDL.h>
#include <stdio.h>


#define WHITE 0xffffffff // Color White
#define BLACK 0x00000000 // Color Black



static int PlayerSpeed = 20;

struct BallSpeed
{
    int x;
    int y;    
} BallSpeed;

SDL_Rect ball = (SDL_Rect){150, 230, 10, 10}; // Initialize Ball 

void spawn_ball(SDL_Surface* surface)
{
    SDL_FillRect(surface, &ball, WHITE);  //Draw Ball
    BallSpeed = (struct BallSpeed){1,1}; //Initialize Ball Speed
}

void move_ball(SDL_Surface* surface , SDL_Rect* ball , struct BallSpeed)
{
    SDL_FillRect(surface,ball,BLACK);
    ball->x += BallSpeed.x ;
    SDL_FillRect(surface,ball,WHITE);
}


void move_player_1(SDL_Surface* surface , SDL_Rect* rect, int movement, char direction) 
{   
    SDL_FillRect(surface, rect, BLACK);
    if(direction == '-' && rect->y >=20)
    {
        rect->y -= movement;
    }
    else if (direction == '+' && rect->y + rect->h <= surface->h - 20)
    {
       rect->y += movement;  
    }
    
    SDL_FillRect(surface, rect, WHITE);
    printf("PLAYER 1(Y) =  %d\n", rect->y);
        
}   

void move_player_2(SDL_Surface *surface, SDL_Rect *rect, int movement, char direction)
{
    if (direction == '-')
    {
        if (rect->y >= 20)
        {
            SDL_FillRect(surface, rect, BLACK);
            rect->y -= movement;
            SDL_FillRect(surface, rect, WHITE);
            printf("PLAYER 1(Y) =  %d\n", rect->y);
        }
    }
    else if (direction == '+')
    {
        if (rect->y <= 260)
        {
            SDL_FillRect(surface, rect, BLACK);
            rect->y += movement;
            SDL_FillRect(surface, rect, WHITE);

            printf("PLAYER 2(Y) = %d\n", rect->y);
        }
    }
}



int main()
{
    SDL_InitSubSystem(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("I Love Julija", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    
    if (window == NULL)
    {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Surface *surface = SDL_GetWindowSurface(window);

    //Creating Players
    SDL_Rect player_1 = (SDL_Rect){40,40,40,200};
    SDL_Rect player_2 = (SDL_Rect){550,40,40,200}; 
    

    // Spawning Players
    SDL_FillRect(surface, &player_1, WHITE);
    SDL_FillRect(surface, &player_2 ,WHITE);


    SDL_Event event;
    
    int quit = 0;
    int ballspawned = 0;


    while (!quit)
    {
        
        SDL_PollEvent(&event);

        if(!ballspawned) //Spawn Ball By Pressing Space
        {
            if (event.key.keysym.sym == SDLK_SPACE){
                spawn_ball(surface);
                ballspawned = 1;
            }
        }

        if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_x) // Window Close Button OR x is Clicked
        {
            printf("Quitting: Key Pressed");
            quit = 1;
        }
        
        switch (event.key.keysym.sym)
        {
        case SDLK_w:
            move_player_1(surface, &player_1, PlayerSpeed,'-');
            break;
        case SDLK_s:
            move_player_1(surface, &player_1, PlayerSpeed,'+');
            break;
        case SDLK_UP:
            move_player_2(surface, &player_2, PlayerSpeed,'-');
            break;
        case SDLK_DOWN:
            move_player_2(surface, &player_2, PlayerSpeed,'+');
            break;

        default:
            break;
        }

        move_ball(surface, &ball, BallSpeed);
        //Move Ball


        SDL_Delay(10);
        SDL_UpdateWindowSurface(window);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
