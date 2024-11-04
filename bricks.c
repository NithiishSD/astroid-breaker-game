#include <stdbool.h>
#include <SDL2/SDL.h>
#include "randomgenerate.h"
#include "ball.h"
#include "images.h"
#include "bricks.h"
#include "audio.h"

void initGame(struct Brick bricks[][brick_columns],SDL_Renderer* renderer,SDL_Texture* t1,SDL_Texture* t2,SDL_Texture* t3)
{
    int k=0;


    for (int i = 0; i < brick_rows; i++) {
        for (int j = 0; j < brick_columns; j++) {
            bricks[i][j].rect.x = i* (brick_width+50)+10;    // Calculate the x position for each brick
            bricks[i][j].rect.y =  (j+1)*(brick_height+30)+10;   // Calculate the y position for each brick
            bricks[i][j].rect.w = brick_width;
            bricks[i][j].rect.h = brick_height;
            bricks[i][j].visible = 1;
           if (k<10)
            render_image(renderer,t2,&bricks[i][j].rect);
           else if(k>=10&&k<20)
                   render_image(renderer,t2,&bricks[i][j].rect);
           else
               render_image(renderer,t1,&bricks[i][j].rect);

            k++;


                             // All bricks start as visible
            }

    }
}
void renderBricks(SDL_Renderer* renderer, struct Brick bricks[ brick_rows][ brick_columns],int *cnt,SDL_Texture* t1,SDL_Texture* t2,SDL_Texture* t3){
    int k=0;
    for (int i = 0; i < brick_rows; i++) {
        for (int j = 0; j < brick_columns; j++) {
            if (bricks[i][j].visible)
            {
                SDL_SetRenderDrawColor(renderer,255,255,0,255);
                SDL_RenderDrawRect(renderer,&bricks[i][j].rect);
                 if (k<8)
                render_image(renderer,t3,&bricks[i][j].rect);
                else if(k>=8&&k<20)
                   render_image(renderer,t2,&bricks[i][j].rect);
                else
               render_image(renderer,t1,&bricks[i][j].rect);
                k++;

            }
            else{
                ball.velX+=ball.velX/16;
                ball.velY+=ball.velY/16;

                *cnt+=1;
                k++;
            }
        }
    }
}
bool checkcollision(SDL_Rect ball,SDL_Rect brick)
{

    return SDL_HasIntersection(&ball,&brick);
}

void brickdestroy(SDL_Renderer* renderer,struct Brick bricks[brick_rows][brick_columns])
{
    SDL_Rect ballRect ={ ball.x, ball.y, ball.width, ball.height};

    for(int i = 0; i < brick_rows; i++)
    {
        for (int j = 0; j < brick_columns; j++)
        {
                if (bricks[i][j].visible &&(checkcollision(ballRect, bricks[i][j].rect)))
                {
                    Mix_Chunk* brickcollision =init_WAV("bricksound.wav");
                    Mix_PlayChannel(-1,brickcollision,0);
                    bricks[i][j].visible=0;// Disable the brick
                    if(ballRect.y+ballRect.h<=bricks[i][j].rect.y+bricks[i][j].rect.w||ballRect.x+ballRect.w>=bricks[i][j].rect.y){

                        ball.velY =-ball.velY;
                    }
                    else if(ballRect.y+ball.height>=bricks[i][j].rect.y&&ballRect.y+ball.height<=bricks[i][j].rect.y)
                        ball.velY=-ball.velY;
                    else{
                        ball.velY=-ball.velY;
                         ball.velX=-ball.velX;
                    }



                }
            }
        }
}
