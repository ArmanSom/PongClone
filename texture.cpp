//Arman Farhangi
//May 12, 2015
//Pong Game
//Standard C++ and SDL Libraries

#include "texture.h"
#include "globals.h"

/******* TEXTURE CLASS DEFS *******/

//constructor
Texture::Texture()
{
    texture = NULL;
    width = 0;
    height = 0;
}

//load text texture
void Texture::load_text(TTF_Font* font, SDL_Color color, std::string text)
{
    //load text into a surface
    SDL_Surface* surface = TTF_RenderText_Solid( font, text.c_str(), color );
    
    //error check
    if (surface == NULL)
        printf( "Couldn't load text surface. Error : %s\n", TTF_GetError() );
    
    else
    {
        //grab dimensions from surface (can't do so from texture) before freeing
        width = surface->w;
        height = surface->h;
        
        //create texture out of surface
        texture = SDL_CreateTextureFromSurface( renderer, surface );
        
        //error check
        if( texture == NULL )
            printf( "Couldn't create texture out of surface. Error: %s\n", SDL_GetError() );
    }
    
    //free unneeded surface
    SDL_FreeSurface( surface );
}

//render texture relative to window's 0,0 (top left)
void Texture::render(int x, int y)
{
    //create rectangle that texture will be fitted into
    SDL_Rect rectangle = { x - width/2, y - height/2, width, height };
    
    //render to screen
    SDL_RenderCopy( renderer, texture, NULL, &rectangle);
}

//destructor (frees texture)
Texture::~Texture()
{
    SDL_DestroyTexture(texture);
}
