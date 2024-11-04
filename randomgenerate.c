#include <stdio.h>
#include <time.h>

#include <stdlib.h>
#include "randomgenerate.h"

int randomNumbers(int minNum,int maxNum)
{
    return rand()%maxNum-minNum+minNum;
}
int randomColour()
{

    return randomNumbers(0,255);
}
SDL_Texture* randombrick(SDL_Texture *t1,SDL_Texture *t2,SDL_Texture *t3)
{
    int i;
    i=randomNumbers(1,3);
    switch(i)
    {
        case 1:
            return t1;
        case 2:
            return t2;
        case 3:
            return t3;
    }
}

