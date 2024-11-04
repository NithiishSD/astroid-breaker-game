#pragma once
#include <SDL2/SDL.h>

struct Paddle
{
    int x, y; // Paddle position
    int paddlewidth,paddleheight ; // Paddle dimensions
    int velocity; // Movement speed
};
extern struct Paddle paddle;

void initPaddle(SDL_Renderer* renderer,SDL_Texture*t1);
void movePaddle(SDL_Event* event);
void render_image_Paddle(SDL_Renderer* renderer,SDL_Texture* paddle_image_texture);
