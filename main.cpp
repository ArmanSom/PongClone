//Arman Farhangi
//May 7, 2015
//Pong Game
//Standard C++ and SDL Libraries

#include <ctime>
#include <stdio.h>

#include "functions.h"
#include "game.h"

/******* MAIN *******/
int main( int arg, char* args[] )
{
    //allow for random number generation
    srand(static_cast<unsigned int>(time(NULL)));
    
    //setup SDL, window, and renderer
    if (setup() == false)
        printf("FAILURE: CANNOT SETUP!\n");
    
    else
    {
        //create game and start level control loop
        Game game;
        game.level_control();
    }
    
    //cleanup and close SDL
    shutdown();
    
    return 0;
}