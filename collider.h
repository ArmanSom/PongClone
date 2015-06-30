//Arman Farhangi
//May 7, 2015
//Pong Game
//Standard C++ and SDL Libraries

#ifndef pong_collider_h
#define pong_collider_h

#include <SDL2/SDL.h>

/******* COLLIDER CLASS DECLARES *******/

//collision determiner
class Collider
{
public:
    //coordinate accessors
    int get_x();
    int get_y();
    
    //dimension accessors
    int get_width();
    int get_height();
    
    //checks for collisions
    bool collided(Collider* object2);
    
    //checks for top or bottom collision
    bool top_or_bottom_collision(Collider* object2);
    
protected:
    //to check for collisions (and possibly render)
    SDL_Rect hitbox;
};





#endif
