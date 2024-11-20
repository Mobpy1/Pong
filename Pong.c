#define SDL_MAIN_HANDLED // Tell SDL to use main function

#include <SDL2/SDL.h>
#include <stdio.h>

#define WHITE 0xffffffff   // Color White
#define BLACK 0x00000000   // Color Black
#define PINK 0xfc028b      // Color Pink
#define GREEN 0x1fe04c     // Color Green
#define TURQUOISE 0x05ffff // Color Turquoise

static int PLAYER_SPEED = 20;
int Gameover = 0;

struct BallSpeed
{
    int x;
    int y;
} BallSpeed = {2, 2};


// Initialize Ball
SDL_Rect ball = (SDL_Rect){150, 230, 10, 10}; 

//Initialize Players
SDL_Rect player_1 = (SDL_Rect){40, 40, 40, 200};
SDL_Rect player_2 = (SDL_Rect){550, 40, 40, 200};

void spawn_ball(SDL_Surface *surface)
{
    SDL_FillRect(surface, &ball, PINK); // Draw Ball
}

void move_ball_AND_collisions(SDL_Surface *surface, SDL_Rect *ball, SDL_Rect *player_1, SDL_Rect *player_2, struct BallSpeed *speed)
{
    SDL_FillRect(surface, ball, BLACK); // Clear previous ball position

    ball->x += speed->x;
    ball->y += speed->y;

    // END OF THE GAME
    if (ball->x <= 0 || ball->x + ball->w >= surface->w) // Left or Right Edge
    {
        Gameover = 1;
    }

    // Normal Collision Check With Wall
    if (ball->y <= 0 || ball->y + ball->h >= surface->h) // Top or Bottom Edge
    {
        speed->y = -speed->y; // Reverse Vertical Direction
    }

    // Collision Check With Players
    if (SDL_HasIntersection(ball, player_1) || SDL_HasIntersection(ball, player_2))
    {
        speed->x = -speed->x;
    }

    SDL_FillRect(surface, ball, PINK); // Redraw ball
}

void move_player(SDL_Surface *surface, SDL_Rect *player, int movement, char direction)
{
    SDL_FillRect(surface, player, BLACK); // Clear previous player position

    
    if (direction == '-' && player->y >= 20)
    {
        player->y -= movement; // Move up
    }
    else if (direction == '+' && player->y + player->h <= surface->h - 20)
    {
        player->y += movement; // Move down
    }
    
    
    if (player == &player_1)
    {
        SDL_FillRect(surface, player, GREEN); // Green for player 1
    }
    else if (player == &player_2)
    {
        SDL_FillRect(surface, player, TURQUOISE); // Turquoise for player 2
    }

    printf("(Y) =  %d\n", player->y); // Debugging output for player Y position
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

    
    
    // Spawning Players (Initial drawing)
    SDL_FillRect(surface, &player_1, GREEN);     // Green for player 1
    SDL_FillRect(surface, &player_2, TURQUOISE); // Turquoise for player 2

    SDL_Event event;

    int ball_spawned = 0;

    while (!Gameover)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                Gameover = 1;
            }
            // KEYDOWN to prevent double inputs
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                // SPACE SPAWNS BALL
                case SDLK_SPACE:
                    if (!ball_spawned)
                    {
                        spawn_ball(surface);
                        ball_spawned = 1;
                    }
                    break;

                // MOVEMENT KEYS
                case SDLK_w:
                    move_player(surface, &player_1, PLAYER_SPEED, '-');
                    break;
                case SDLK_s:
                    move_player(surface, &player_1, PLAYER_SPEED, '+');
                    break;
                case SDLK_UP:
                    move_player(surface, &player_2, PLAYER_SPEED, '-');
                    break;
                case SDLK_DOWN:
                    move_player(surface, &player_2, PLAYER_SPEED, '+');
                    break;
                case SDLK_x:
                    Gameover = 1;
                    break;

                default:
                    break;
                }
            }
        }

        // Move the ball if spawned
        if (ball_spawned)
        {
            move_ball_AND_collisions(surface, &ball, &player_1, &player_2, &BallSpeed);
        }
        
        SDL_FillRect(surface,&player_1,GREEN);
        SDL_FillRect(surface,&player_2,TURQUOISE);

        SDL_UpdateWindowSurface(window); // Update the window
        SDL_Delay(10);                   // Control frame rate
    }

    printf("Game Over. Well Done!");
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
