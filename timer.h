//Arman Farhangi
//May 8, 2015
//Pong Game
//Standard C++ and SDL Libraries

#ifndef pong_timer_h
#define pong_timer_h

#include <SDL2/SDL.h>

/******* TIMER CLASS DECLARES *******/

//stopwatch timer
class Timer
{
public:
    //constructor
    Timer();
    
    //create arbitrary starting point
    void start();
    
    //check time passed since starting point
    int check();
    
private:
    //stores starting time
    Uint32 start_time;
};




#endif
