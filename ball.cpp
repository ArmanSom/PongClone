//Arman Farhangi
//May 12, 2015
//Pong Game
//Standard C++ and SDL Libraries

#include "ball.h"
#include "globals.h"

/******* BALL CLASS DEFS *******/

//constructor
Ball::Ball()
{
    //places ball in middle of window
    hitbox.x = WINDOW_WIDTH/2 - BALL_WIDTH/2;
    hitbox.y = WINDOW_HEIGHT/2 - BALL_HEIGHT/2;
    hitbox.w = BALL_WIDTH;
    hitbox.h = BALL_HEIGHT;
    
    //starts off still
    x_velocity = 0;
    y_velocity = 0;
}

//handles space bar event (which launches still ball)
void Ball::handle(SDL_Event& event)
{
    //if the ball has no velocity
    if (x_velocity == 0 && y_velocity == 0)
        //if event is a non-repeat key press
        if ( event.type == SDL_KEYDOWN && event.key.repeat == 0 )
            //if event is space key
            if ( event.key.keysym.sym == SDLK_SPACE )
            {
                //randomly launch in a direction
                if (rand() % 2 == 0)
                    x_velocity += SPEED;
                else
                    x_velocity -= SPEED;
                if (rand() % 2 == 0)
                    y_velocity += SPEED;
                else
                    y_velocity -= SPEED;
            }
    
}

//moves ball based on velocity
void Ball::move(const std::vector<Collider*>& paddles, int& player1_score, int& player2_score)
{
    //change x and y coordinates
    hitbox.x += x_velocity;
    hitbox.y += y_velocity;
    
    //if ball hits the top or bottom of window
    if (hitbox.y <= 0 || hitbox.y >= WINDOW_HEIGHT - BALL_HEIGHT)
        //change y-direction
        y_velocity = -y_velocity;
    
    //if there's a collision with either paddle and it's been three seconds since collision timer started
    if ( ( collided(paddles[0]) || collided(paddles[1]) ) && collision_timer.check() > 500 )
    {
        //change x-direction
        x_velocity = -x_velocity;
        
        //if the collision was at the top or bottom of paddle
        if ( top_or_bottom_collision(paddles[0]) || top_or_bottom_collision(paddles[1]) )
            //also change y velocity direction
            y_velocity = -y_velocity;
        
        //reset ball collision timer
        collision_timer.start();
    }
    
    //if ball is out of left or right screen
    if (hitbox.x > WINDOW_WIDTH || hitbox.x < 0 - BALL_WIDTH)
    {
        //if ball out right, player1 scores
        if( hitbox.x > WINDOW_WIDTH )
            ++player1_score;
        //if ball out left, player2 scores
        else if ( hitbox.x < 0 - BALL_WIDTH )
            ++player2_score;
        
        //place ball back in center
        hitbox.x = WINDOW_WIDTH/2 - BALL_WIDTH/2;
        hitbox.y = WINDOW_HEIGHT/2 - BALL_HEIGHT/2;
        //stop moving
        x_velocity = 0;
        y_velocity = 0;
    }
}

//renders ball (can just use hitbox since it's a little rectangle)
void Ball::render()
{
    SDL_RenderFillRect(renderer, &hitbox);
}

//get x-velocity
int Ball::get_x_velocity()
{
    return x_velocity;
}

//get y-velocity
int Ball::get_y_velocity()
{
    return y_velocity;
}
