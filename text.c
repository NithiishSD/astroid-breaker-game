#include "text.h"
SDL_Texture* text_init(SDL_Renderer* renderer,TTF_Font* font,char* string,SDL_Color* color)
{
      SDL_Surface* text=TTF_RenderText_Solid(font,string,*color);
        SDL_Texture* text_texture=SDL_CreateTextureFromSurface(renderer,text);
        SDL_FreeSurface(text);
        return text_texture;


     //to import the image into the program
    //to free the image on in the main
}






void render_text(SDL_Renderer* renderer,SDL_Texture* text_texture,SDL_Rect* texture_destination)
{


    SDL_RenderCopy(renderer,text_texture,NULL,texture_destination);
}
