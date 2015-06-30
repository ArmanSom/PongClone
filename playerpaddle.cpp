//Arman Farhangi
//May 12, 2015
//Pong Game
//Standard C++ and SDL Libraries

#include "playerpaddle.h"
#include "globals.h"


/******* PLAYER PADDLE CLASS DEFS *******/

//constructor (spawns paddle on right side by default)
PlayerPaddle::PlayerPaddle(int player2) : Paddle(RIGHT), y_velocity(0)
{
    //if it's a player battle and it's player 2, then spawn left
    if (player2 != 0)
    {
        hitbox.x = WINDOW_WIDTH/20;
        hitbox.y = WINDOW_HEIGHT/2 - PADDLE_HEIGHT/2;
    }
}


//check events for velocity change
void PlayerPaddle::handle(SDL_Event& event)
{
    //if paddle is on the right side
    if (hitbox.x > WINDOW_WIDTH/2)
    {
        //if event is a non-repeat key press
        if ( event.type == SDL_KEYDOWN && event.key.repeat == 0 )
        {
            //if event is up key
            if ( event.key.keysym.sym == SDLK_UP )
                //gear paddle up
                y_velocity -= PLAYER_PADDLE_SPEED;
            
            //if event is down key
            else if ( event.key.keysym.sym == SDLK_DOWN )
                //gear paddle down
                y_velocity += PLAYER_PADDLE_SPEED;
        }
        
        //if event is a non-repeat key release
        else if( event.type == SDL_KEYUP && event.key.repeat == 0 )
        {
            //if event is up key
            if ( event.key.keysym.sym == SDLK_UP )
                //back to zero
                y_velocity += PLAYER_PADDLE_SPEED;
            
            //if event is down key
            else if ( event.key.keysym.sym == SDLK_DOWN )
                //back to zero
                y_velocity -= PLAYER_PADDLE_SPEED;
        }
    }
    
    //if paddle is on the left side
    else if (hitbox.x < WINDOW_WIDTH/2)
    {
        //if event is a non-repeat key press
        if ( event.type == SDL_KEYDOWN && event.key.repeat == 0 )
        {
            //if event is w key
            if ( event.key.keysym.sym == SDLK_w )
                //gear paddle up
                y_velocity -= PLAYER_PADDLE_SPEED;
            
            //if event is d key
            else if ( event.key.keysym.sym == SDLK_d )
                //gear paddle down
                y_velocity += PLAYER_PADDLE_SPEED;
        }
        
        //if event is a non-repeat key release
        else if( event.type == SDL_KEYUP && event.key.repeat == 0 )
        {
            //if event is w key
            if ( event.key.keysym.sym == SDLK_w )
                //back to zero
                y_velocity += PLAYER_PADDLE_SPEED;
            
            //if event is d key
            else if ( event.key.keysym.sym == SDLK_d )
                //back to zero
                y_velocity -= PLAYER_PADDLE_SPEED;
        }
    }
    
}



//change coordinates based on velocity
void PlayerPaddle::move()
{
    //change position by current velocity
    hitbox.y += y_velocity;
    
    //if out of bounds, revert the coordinate change
    if (hitbox.y < 5 || hitbox.y > WINDOW_HEIGHT - PADDLE_HEIGHT - 5)
        hitbox.y -= y_velocity;
}

