#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

SDL_Texture* text_init(SDL_Renderer* renderer,TTF_Font* font,char* string,SDL_Color* color);
void render_text(SDL_Renderer* renderer,SDL_Texture* text_texture,SDL_Rect* texture_destination);
