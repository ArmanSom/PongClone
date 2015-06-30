//Arman Farhangi
//May 7, 2015
//Pong Game
//Standard C++ and SDL Libraries

#ifndef pong_computerpaddle_h
#define pong_computerpaddle_h

#include "paddle.h"
#include "ball.h"


/******* COMPUTER PADDLE CLASS DECLARES *******/

//AI paddle
class ComputerPaddle : public Paddle
{
public:
    //constants
    const static int COMPUTER_PADDLE_SPEED = 6;
    
    //constructor
    ComputerPaddle();
    
    //move function that follows opponent
    void move();
    
    //sets pointer to opponent
    void set_opponent(Paddle* opponent);
    
    //sets pointer to ball
    void set_ball(Ball* ball);
    
private:
    //pointer to opponent for its y-coordinate
    Paddle* opponent;
    
    //pointer to ball for its y-coordinate
    Ball* ball;
};





#endif
