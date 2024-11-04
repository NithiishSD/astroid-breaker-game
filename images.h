#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
SDL_Texture* images_init(SDL_Renderer* renderer,char* location);
SDL_Rect* image_present_location(int x,int y,int width,int height);
void render_image(SDL_Renderer* renderer,SDL_Texture* image_texture,SDL_Rect* texture_destination);
