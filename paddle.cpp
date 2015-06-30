//Arman Farhangi
//May 12, 2015
//Pong Game
//Standard C++ and SDL Libraries

#include "paddle.h"
#include "globals.h"


/******* PADDLE CLASS DEFS *******/

//constructor that sets coordinates depending on side
Paddle::Paddle(int side)
{
    //set size and side
    hitbox.w = PADDLE_WIDTH;
    hitbox.h = PADDLE_HEIGHT;
    Paddle::side = side;
    
    //if right paddle, set right side position
    if (side == RIGHT)
    {
        hitbox.x = (WINDOW_WIDTH - WINDOW_WIDTH/20) - PADDLE_WIDTH;
        hitbox.y = WINDOW_HEIGHT/2 - PADDLE_HEIGHT/2;
    }
    //if left paddle, set left side position
    else if (side == LEFT)
    {
        hitbox.x = WINDOW_WIDTH/20;
        hitbox.y = WINDOW_HEIGHT/2 - PADDLE_HEIGHT/2;
    }
    //error check
    else if (side != RIGHT || side != LEFT)
        printf( "Error: invalid side choice.  Pick either LEFT or RIGHT.\n");
}

//renders paddle
void Paddle::render()
{
    SDL_RenderFillRect(renderer, &hitbox);
}
