#include <SDL2/SDL.h>
#include "ball.h"
#include "paddle.h"
#include "images.h"
#include "audio.h"
struct Ball ball;

void initBall( int x, int y)
{
    ball.x =x ; //Initialising positions
    ball.y = y;
    ball.width = 20; //Initialising dimensions
    ball.height = 20;
    ball.velX = 6;
    ball.velY = -6;

}


void moveBall()
{
    ball.x += ball.velX; //Moving the ball based on velocity
    ball.y += ball.velY;
}

void checkBallCollision(int screen_width, int screen_height)//to check the collision with paddle wall
{
      Mix_Chunk* collisionwall =init_WAV("wallsound.wav");
    // Ball hits the wall
    if (ball.x < 0 || ball.x + ball.width >= screen_width||ball.y+ball.width>=screen_width)
    {

        ball.velX=-ball.velX;

        Mix_PlayChannel(-1,collisionwall,0);
    }
    // Ball hits top
    if (ball.y < 0)
    {
        Mix_PlayChannel(-1,collisionwall,0);
        ball.velY = -ball.velY;
    }


    if(ball.velX==0)
        ball.velX+=ball.velX/16;
    // Ball hits paddle
     SDL_Rect ballRect = { ball.x, ball.y, ball.width, ball.height};
     SDL_Rect paddleRect = { paddle.x, paddle.y, paddle.paddlewidth,paddle.paddleheight };
    if (checkcollision(ballRect,paddleRect))
    {
        Mix_Chunk* collision =init_WAV("ballhit.wav");
        Mix_PlayChannel(-1,collision,0);
        if((ball.x+ball.width>=paddle.x&&ball.x<paddle.x&&ball.y>paddle.y)&&(ball.x<=paddle.x+paddle.paddlewidth&&ball.x>=paddle.x+paddle.paddlewidth))//checking for the side collision
        {
            ball.velX = -ball.velX;
        }

        else if(ball.y+ball.height>=paddle.y&&ball.y<paddle.y&&ball.x>paddle.x&&ball.x+ball.width<paddle.x+paddle.paddlewidth)
        {

            ball.velY=-ball.velY;
            if(paddle.velocity==0){
                if(ball.velX>0)
                    ball.velX-=ball.velX/8;
                else
                    ball.velX+=ball.velX/8;
            }
            else if(paddle.velocity<0)//reducing the speed of the ball
            {
                if(ball.velX>0)
                {
                    ball.velX=-(+ball.velX+paddle.velocity);
                }
                else
                    ball.velX=-(ball.velX+paddle.velocity/4);
            }
            else
            {
                if(ball.velX>0)
                {
                    ball.velX=(ball.velX+paddle.velocity/4);
                }
                else
                    ball.velX=(ball.velX+paddle.velocity/4);
            }
        }


        else
            ball.velX=-ball.velX;
    }
}


void renderball_image(SDL_Renderer* renderer,SDL_Texture* ball_image_texture)
{
     SDL_Rect ballRect = { ball.x, ball.y, ball.width, ball.height};

    SDL_SetRenderDrawColor(renderer,255,255,0,255);
    SDL_RenderDrawRect(renderer,&ballRect);
    render_image(renderer,ball_image_texture,&ballRect);

}
