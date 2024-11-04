#pragma once
#include <SDL2/SDL_image.h>
#include <time.h>

int randomNumbers(int minNum,int maxNum);


int randomColour();

SDL_Texture* randombrick(SDL_Texture *t1,SDL_Texture *t2,SDL_Texture *t3);
