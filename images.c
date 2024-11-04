#include "images.h"

SDL_Texture* images_init(SDL_Renderer* renderer,char* location)
{
      SDL_Surface* image=IMG_Load(location);
        SDL_Texture* image_texture=SDL_CreateTextureFromSurface(renderer,image);
        SDL_FreeSurface(image);
        return image_texture;


     //to import the image into the program
    //to free the image on in the main
}
SDL_Rect* image_present_location(int x,int y,int width,int height)
{
    SDL_Rect texture_destination;
    texture_destination.x=x;
    texture_destination.y=y;
    texture_destination.w=width;
    texture_destination.h=height;
    return &texture_destination;
}
 void render_image(SDL_Renderer* renderer,SDL_Texture* image_texture,SDL_Rect* texture_destination)
{


    SDL_RenderCopy(renderer,image_texture,NULL,texture_destination);
}
