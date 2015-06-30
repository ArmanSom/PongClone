//Arman Farhangi
//May 12, 2015
//Pong Game
//Standard C++ and SDL Libraries

#include "globals.h"

//initialize external global objects
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* big_font = NULL;
TTF_Font* medium_font = NULL;
TTF_Font* small_font = NULL;
TTF_Font* smallest_font = NULL;

/******* SETUP AND SHUTDOWN FUNCTION DEFS *******/

//setup SDL, window, and renderer
bool setup()
{
    //error tracker
    bool succeeded = true;
    
    //initialize SDL
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize.  Error: %s\n", SDL_GetError() );
        succeeded = false;
    }
    
    else
    {
        //create window titled PONG
        window = SDL_CreateWindow( "PONG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        
        //error check
        if (window == NULL)
        {
            printf( "Could not create window.  Error: %s\n", SDL_GetError() );
            succeeded = false;
        }
        
        else
        {
            //create hardware accelerated renderer
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            
            //error check
            if (renderer == NULL)
            {
                printf( "Could not create renderer.  Error: %s\n", SDL_GetError() );
                succeeded = false;
            }
            
            else
            {
                //set render color to black
                SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
                
                //initialize SDL Font
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_TTF could not initialize. Error: %s\n", TTF_GetError() );
                    succeeded = false;
                }
                
                else
                {
                    //setup fonts
                    big_font = TTF_OpenFont( "PressStart2P.ttf", 60 );
                    medium_font = TTF_OpenFont( "PressStart2P.ttf", 28 );
                    small_font = TTF_OpenFont( "PressStart2P.ttf", 18 );
                    smallest_font = TTF_OpenFont( "PressStart2P.ttf", 12);
                    
                    //error check
                    if (big_font == NULL)
                    {
                        printf( "Could not open title font.  Error: %s\n", TTF_GetError() );
                        succeeded = false;
                    }
                    
                    //error check
                    if (medium_font == NULL)
                    {
                        printf( "Could not open button font.  Error: %s\n", TTF_GetError() );
                        succeeded = false;
                    }
                    
                    //error check
                    if (small_font == NULL)
                    {
                        printf( "Could not open button font.  Error: %s\n", TTF_GetError() );
                        succeeded = false;
                    }
                    
                    //error check
                    if (smallest_font == NULL)
                    {
                        printf( "Could not open button font.  Error: %s\n", TTF_GetError() );
                        succeeded = false;
                    }
                }
            }
        }
    }
    
    //return error tracker
    return succeeded;
}


//destroy window, renderer, and quit SDL
void shutdown()
{
    //free window and renderer
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;
    
    //Free big font
    TTF_CloseFont( big_font );
    big_font = NULL;
    //free medium font
    TTF_CloseFont( medium_font );
    medium_font = NULL;
    //free small font
    TTF_CloseFont( small_font );
    small_font = NULL;
    //free smallest font
    TTF_CloseFont( smallest_font );
    smallest_font = NULL;
    
    //quit SDL systems
    TTF_Quit();
    SDL_Quit();
}
