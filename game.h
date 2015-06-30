//Arman Farhangi
//May 9, 2015
//Pong Game
//Standard C++ and SDL Libraries

#ifndef pong_game_h
#define pong_game_h

#include <SDL2/SDL.h>

/******* GAME CLASS DECLARES *******/

//pong game
class Game
{
public:
    //constructor
    Game();
    
    //the main game loop
    void level_control();
    
private:
    //determines what part of game will be running
    int level;
    
    //title screen loop
    void title_screen( SDL_Rect window_outline );
    
    //computer_battle loop
    void computer_battle( SDL_Rect window_outline );
    
    //player_battle loop
    void player_battle( SDL_Rect window_outline );
    
    //instructions loop
    void instructions( SDL_Rect window_outline );
};




#endif
