#pragma once
#include "bricks.h"

struct Ball
{
    int x, y, width, height, velX, velY;


};
extern struct Ball ball;

void checkBallCollision(int screen_width, int screen_height);
void initBall(int x, int y);
void moveBall();

void renderball_image(SDL_Renderer* renderer,SDL_Texture* ball_image_texture);


