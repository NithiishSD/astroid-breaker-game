
#include "paddle.h"
#include "randomgenerate.h"
#include "images.h"
int PADDLE_WIDTH = 200;//no constant because we need it for arithmetic operation
int PADDLE_HEIGHT =10 ;
int SCREEN_WIDTH =1500 ;
int SCREEN_HEIGHT = 850;
int  PADDLE_SPEED =8;
struct Paddle paddle;



void initPaddle(SDL_Renderer* renderer,SDL_Texture*t1)
{   //the x y coordinates is the top left edge of the object
    paddle.x = SCREEN_WIDTH/2-PADDLE_WIDTH/2; // Center the paddle horizontally
    paddle.y = SCREEN_HEIGHT - PADDLE_HEIGHT-40; // Position the paddle near the bottom
    paddle.paddlewidth = PADDLE_WIDTH;
    paddle.paddleheight = PADDLE_HEIGHT;
    paddle.velocity = PADDLE_SPEED;
    SDL_Rect paddleRect = { paddle.x, paddle.y, paddle.paddlewidth, PADDLE_HEIGHT+70};
    render_image(renderer,t1,&paddleRect);
}
void movePaddle(SDL_Event* event)
{
    const int8_t* state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_LEFT] && paddle.x > 0) {
            paddle.x -= PADDLE_SPEED;
            paddle.velocity=-PADDLE_SPEED;
        }
        else
            paddle.velocity=0;
        if (state[SDL_SCANCODE_RIGHT] && paddle.x < SCREEN_WIDTH - PADDLE_WIDTH) {
            paddle.x += PADDLE_SPEED;
            paddle.velocity=PADDLE_SPEED;
        }
        else
            paddle.velocity=0;
}
void render_image_Paddle(SDL_Renderer* renderer,SDL_Texture* paddle_image_texture)
{

    SDL_Rect paddleRect = { paddle.x,paddle.y-30,paddle.paddlewidth,paddle.paddleheight+70};
    SDL_Rect paddleRect1 = { paddle.x,paddle.y,paddle.paddlewidth,paddle.paddleheight};
     SDL_SetRenderDrawColor(renderer,255,255,0,255);
    SDL_RenderDrawRect(renderer,&paddleRect1);
    render_image(renderer,paddle_image_texture,&paddleRect);


}
