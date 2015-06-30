//Arman Farhangi
//May 7, 2015
//Pong Game
//Standard C++ and SDL Libraries

#ifndef pong_playerpaddle_h
#define pong_playerpaddle_h

#include "paddle.h"


/******* PLAYER PADDLE CLASS DECLARES *******/

//player paddle
class PlayerPaddle : public Paddle
{
public:
    //constant
    const static int PLAYER_PADDLE_SPEED = 7;
    
    //constructor (different spawn depending if player battle)
    PlayerPaddle(int second_player = 0);
    
    //event handler (changes velocity)
    void handle(SDL_Event& event);
    
    //implement velocity into change of coordinates
    void move();
    
private:
    //change of y-pixels per frame
    int y_velocity;
};



#endif
