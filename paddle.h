//Arman Farhangi
//May 7, 2015
//Pong Game
//Standard C++ and SDL Libraries

#ifndef pong_paddle_h
#define pong_paddle_h

#include "collider.h"

/******* PADDLE CLASS DECLARES *******/

//base class for paddles
class Paddle : public Collider
{
public:
    //constants
    const static int PADDLE_WIDTH = 20;
    const static int PADDLE_HEIGHT = 90;
    
    //constructor
    Paddle(int side);
    
    //render paddle
    void render();
    
protected:
    //determines whether on right or left side
    int side;
};


#endif
