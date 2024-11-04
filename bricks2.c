#include <stdbool.h>
#include <SDL2/SDL.h>
#include "images.h"
#include "randomgenerate.h"
#include "ball.h"
#include "bricks.h"
#include "audio.h"


void initGame2(struct Brick bricks[][brick_columns],SDL_Renderer* renderer,SDL_Texture* t1,SDL_Texture* t2,SDL_Texture* t3)
{
    int k=0;

    for (int i = 0; i < brick_rows; i++) {
        for (int j = 0; j < brick_columns; j++) {
           bricks[i][j].rect.x = i* (brick_width+50)+10;    // Calculate the x position for each brick
            bricks[i][j].rect.y =  (j+1)*(brick_height+30)+10;   // Calculate the y position for each brick
            bricks[i][j].rect.w = brick_width;
            bricks[i][j].rect.h = brick_height;
            bricks[i][j].visible = 1;
            bricks[i][j].strength=2;
            if (k<10)
            render_image(renderer,t2,&bricks[i][j].rect);
           else if(k>=10&&k<20)
                   render_image(renderer,t2,&bricks[i][j].rect);
           else
               render_image(renderer,t1,&bricks[i][j].rect);

            k++;
        }
                             // All bricks start as visible

    }
}
void renderBricks2(SDL_Renderer* renderer, struct Brick bricks[ brick_rows][ brick_columns],int *cnt,SDL_Texture* t1,SDL_Texture* t2,SDL_Texture* t3,SDL_Texture* t4){
    int k=0;
    SDL_Rect rect2;
    for (int i = 0; i < brick_rows; i++) {
        for (int j = 0; j < brick_columns; j++)
        {
            if (bricks[i][j].visible&&bricks[i][j].strength==2) {
              if (k<10)
            render_image(renderer,t2,&bricks[i][j].rect);
           else if(k>=10&&k<20)
                   render_image(renderer,t2,&bricks[i][j].rect);
           else
               render_image(renderer,t1,&bricks[i][j].rect);

            k++;

            }

            else if(bricks[i][j].strength==1&&bricks[i][j].visible)
            {
                rect2.x=bricks[i][j].rect.x-10;
                rect2.y=bricks[i][j].rect.y-10;
                rect2.w=bricks[i][j].rect.w+40;
                rect2.h=bricks[i][j].rect.h+10;
                render_image(renderer,t4,&rect2);
                if (k<10)
                render_image(renderer,t2,&bricks[i][j].rect);
                else if(k>=10&&k<20)
                   render_image(renderer,t2,&bricks[i][j].rect);
                else
                    render_image(renderer,t1,&bricks[i][j].rect);

                k++;
            }
            else if(bricks[i][j].strength==0){
                 ball.velX+=ball.velX/16;
                ball.velY+=ball.velY/16;
                *cnt+=1;
                k++;
            }
             ball.velX-=ball.velX/16;
            ball.velY-=ball.velY/16;
        }
    }
}
bool checkcollision2(SDL_Rect ball,SDL_Rect brick)
{

    return SDL_HasIntersection(&ball,&brick);
}

void brickdestroy2(SDL_Renderer* renderer,struct Brick bricks[brick_rows][brick_columns])
{
    SDL_Rect ballRect = { ball.x, ball.y, ball.width, ball.height};

    for(int i = 0; i < brick_rows; i++)
    {
        for (int j = 0; j < brick_columns; j++)
        {
                if (bricks[i][j].visible &&(checkcollision(ballRect, bricks[i][j].rect))&&bricks[i][j].strength==2)
                {
                     Mix_Chunk* brickcollision =init_WAV("bricksound.wav");
                    Mix_PlayChannel(-1,brickcollision,0);
                    // Disable the brick
                    bricks[i][j].strength-=1;
                    if(ballRect.y+ballRect.h<=bricks[i][j].rect.y+bricks[i][j].rect.w||ballRect.x+ballRect.w>=bricks[i][j].rect.y){

                        ball.velY =-ball.velY;
                    }
                    else if(ballRect.y+ball.height>=bricks[i][j].rect.y)
                        ball.velY=-ball.velY;
                    else{
                        ball.velY=-ball.velY;
                         ball.velX=-ball.velX;
                    }
                    // Reverse ball direction
                }
                else if(bricks[i][j].strength==1&&bricks[i][j].visible &&(checkcollision(ballRect, bricks[i][j].rect))){
                    bricks[i][j].visible=0;
                    bricks[i][j].strength--;
                     Mix_Chunk* brickcollision =init_WAV("bricksound.wav");
                    Mix_PlayChannel(-1,brickcollision,0);
                    if(ballRect.y+ballRect.h<=bricks[i][j].rect.y+bricks[i][j].rect.w||ballRect.x+ballRect.w>=bricks[i][j].rect.y){

                        ball.velY =-ball.velY;
                    }
                    else if(ballRect.y+ball.height>=bricks[i][j].rect.y)
                        ball.velY=-ball.velY;
                    else{
                        ball.velY=-ball.velY;
                         ball.velX=-ball.velX;
                    }
                }
            }
        }
}
