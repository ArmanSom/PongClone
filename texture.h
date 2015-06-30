//Arman Farhangi
//May 9, 2015
//Pong Game
//Standard C++ and SDL Libraries

#ifndef pong_texture_h
#define pong_texture_h

#include <SDL2_ttf/SDL_ttf.h>
#include <string>
#include <SDL2/SDL.h>

/******* TEXTURE CLASS DECLARES *******/

//graphic holders
class Texture
{
public:
    //constructor
    Texture();
    
    //load text into texture
    void load_text(TTF_Font* font, SDL_Color color, std::string text);
    
    //render to screen
    void render(int x, int y);
    
    //destructor (to free texture)
    ~Texture();
    
    //accessors
    int get_width() { return width; };
    int get_height() { return height; };
    
private:
    //loaded texture
    SDL_Texture* texture;
    
    //width and height of loaded texture
    int width;
    int height;
};



#endif
