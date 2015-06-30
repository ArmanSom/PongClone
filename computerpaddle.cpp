//Arman Farhangi
//May 12, 2015
//Pong Game
//Standard C++ and SDL Libraries

#include "computerpaddle.h"
#include "globals.h"
#include "ball.h"

/******* COMPUTER PADDLE CLASS DEFS *******/

//constructor
ComputerPaddle::ComputerPaddle() : Paddle(LEFT), ball(NULL), opponent(NULL){}

//set pointer to opponent to use for movement
void ComputerPaddle::set_opponent(Paddle* opponent)
{
    ComputerPaddle::opponent = opponent;
}

//set pointer to ball to use for movement
void ComputerPaddle::set_ball(Ball* ball)
{
    ComputerPaddle::ball = ball;
}

//move computer paddle based off opponent or ball
void ComputerPaddle::move()
{   //if ball is still
    if (ball->get_x_velocity() == 0 && ball->get_y_velocity() == 0)
    {
        //if top of paddle is under opponent's top of paddle (give or take 4 pixels), move up
        if ( hitbox.y - opponent->get_y() > 4 )
            hitbox.y -= COMPUTER_PADDLE_SPEED;
        
        //if top of paddle is above opponent's top of paddle (give or take 4 pixels), move down
        else if ( opponent->get_y() - hitbox.y > 6 )
            hitbox.y += COMPUTER_PADDLE_SPEED;
    }
    
    //if ball is moving
    else
    {
        //if low-center of paddle is below center of ball
        if ( hitbox.y + PADDLE_HEIGHT/3 > ball->get_y() + Ball::BALL_HEIGHT/2 )
        {
            //move paddle up
            hitbox.y -= COMPUTER_PADDLE_SPEED;
            //if out of bounds, revert movement
            if (hitbox.y < 10)
                hitbox.y += COMPUTER_PADDLE_SPEED;
        }
        //if high-center of padle is above center of ball
        if ( hitbox.y + (PADDLE_HEIGHT/2 + PADDLE_HEIGHT/3) < ball->get_y() + Ball::BALL_HEIGHT/2 )
        {
            //move paddle down
            hitbox.y += COMPUTER_PADDLE_SPEED;
            //if out of bounds, revert movement
            if ( hitbox.y > WINDOW_HEIGHT - PADDLE_HEIGHT - 10 )
                hitbox.y -= COMPUTER_PADDLE_SPEED;
            
        }
    }
}
