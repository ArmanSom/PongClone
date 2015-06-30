//Arman Farhangi
//May 7, 2015
//Pong Game
//Standard C++ and SDL Libraries

#ifndef pong_ball_h
#define pong_ball_h

#include <vector>

#include "collider.h"
#include "timer.h"


/******** BALL CLASS DECLARES *******/

//ball
class Ball : public Collider
{
public:
    //constants
    const static int BALL_WIDTH = 15;
    const static int BALL_HEIGHT = 15;
    const static int SPEED = 7;
    
    //constructor
    Ball();
    
    //event handler for velocity changes
    void handle(SDL_Event& event);
    
    //coordinate mover (based on velocity)
    void move(const std::vector<Collider*>& paddles, int& player1_score, int& player2_score);
    
    //renders ball
    void render();
    
    //gets x-velocity
    int get_x_velocity();
    
    //gets y-velocity
    int get_y_velocity();
  
private:
    //change of x coordinates (x pixels for each frame)
    int x_velocity;
    
    //change of y coordinates (y pixels for each frame)
    int y_velocity;
    
    //creates hit cooldown to prevent collision glitches
    Timer collision_timer;
};

#endif
