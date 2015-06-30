//Arman Farhangi
//May 7, 2015
//Pong Game
//Standard C++ and SDL Libraries

#ifndef pong_globals_h
#define pong_globals_h

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

/******* GLOBAL CONSTANTS, OBJECTS, ENUMERATIONS *******/

//window dimensions
const int WINDOW_WIDTH = 700;
const int WINDOW_HEIGHT = 400;

//window and renderer
extern SDL_Window* window;
extern SDL_Renderer* renderer;

//fonts
extern TTF_Font* big_font;
extern TTF_Font* medium_font;
extern TTF_Font* small_font;
extern TTF_Font* smallest_font;

//for Paddle constructor
enum PaddleSide { RIGHT, LEFT };

//for level control
enum Level { TITLE, COMPUTER_BATTLE, PLAYER_BATTLE, INSTRUCTIONS, END };


#endif
