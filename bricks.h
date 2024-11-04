#pragma once
#include <stdio.h>
#include <SDL2/SDL.h>
#include "randomgenerate.h"
#include <stdbool.h>
#define brick_width 50
#define brick_height 25
#define brick_rows 15
#define brick_columns 4

struct Brick
{
    SDL_Rect rect;
    int strength;
    int visible;
};
extern struct Brick Brick;

void initGame(struct Brick bricks[][brick_columns],SDL_Renderer* renderer,SDL_Texture* t1,SDL_Texture* t2,SDL_Texture* t3);
bool  checkcollision(SDL_Rect ball,SDL_Rect brick);
void renderBricks(SDL_Renderer* renderer, struct Brick bricks[ brick_rows][ brick_columns],int *cnt,SDL_Texture* t1,SDL_Texture* t2,SDL_Texture* t3);
void brickdestroy(SDL_Renderer* renderer,struct Brick bricks[brick_rows][brick_columns]);
void initGame2(struct Brick bricks[][brick_columns],SDL_Renderer* renderer,SDL_Texture* t1,SDL_Texture* t2,SDL_Texture* t3);
bool  checkcollision2(SDL_Rect ball,SDL_Rect brick);
void renderBricks2(SDL_Renderer* renderer, struct Brick bricks[ brick_rows][ brick_columns],int *cnt,SDL_Texture* t1,SDL_Texture* t2,SDL_Texture* t3,SDL_Texture* t4);
void brickdestroy2(SDL_Renderer* renderer,struct Brick bricks[brick_rows][brick_columns]);
