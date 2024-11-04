/*#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PADDLE_WIDTH 100
#define PADDLE_HEIGHT 20
#define BALL_SIZE 10
#define BRICK_WIDTH 75
#define BRICK_HEIGHT 30
#define BRICKS_PER_ROW 10
#define BRICK_ROWS 5

typedef struct {
    int x, y, width, height;
} Paddle;

typedef struct {
    int x, y, dx, dy;
} Ball;

typedef struct {
    int x, y, alive;
} Brick;

void initBricks(Brick bricks[BRICK_ROWS][BRICKS_PER_ROW]) {
    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICKS_PER_ROW; j++) {
            bricks[i][j].x = j * (BRICK_WIDTH + 5);
            bricks[i][j].y = i * (BRICK_HEIGHT + 5);
            bricks[i][j].alive = 1; // Brick is alive
        }
    }
}

int main(int argc, char *argv[]) {
    int i=0;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Brick Breaker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    Paddle paddle = {SCREEN_WIDTH / 2 - PADDLE_WIDTH / 2, SCREEN_HEIGHT - PADDLE_HEIGHT - 10, PADDLE_WIDTH, PADDLE_HEIGHT};
    Ball ball = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 5, -5};
    Brick bricks[BRICK_ROWS][BRICKS_PER_ROW];
    initBricks(bricks);

    int running = 1;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_LEFT] && paddle.x > 0) {
            paddle.x -= 5;
        }
        if (state[SDL_SCANCODE_RIGHT] && paddle.x < SCREEN_WIDTH - PADDLE_WIDTH) {
            paddle.x += 5;
        }

        // Update ball position
        ball.x += ball.dx;
        ball.y += ball.dy;

        // Ball collision with walls
        if (ball.x <= 0 || ball.x >= SCREEN_WIDTH - BALL_SIZE) {
            ball.dx = -ball.dx;
        }
        if (ball.y <= 0) {
            ball.dy = -ball.dy;
        } else if (ball.y >= SCREEN_HEIGHT) {
            // Ball missed the paddle (game over logic can go here)
            if(i>3)
                running = 0;
            i++;
        }

        // Ball collision with paddle
        if (ball.y + BALL_SIZE >= paddle.y && ball.x + BALL_SIZE >= paddle.x && ball.x <= paddle.x + PADDLE_WIDTH) {
            ball.dy = -ball.dy;
            ball.y = paddle.y - BALL_SIZE; // Adjust ball position
        }

        // Ball collision with bricks
        for (int i = 0; i < BRICK_ROWS; i++) {
            for (int j = 0; j < BRICKS_PER_ROW; j++) {
                if (bricks[i][j].alive) {
                    if (ball.x + BALL_SIZE >= bricks[i][j].x && ball.x <= bricks[i][j].x + BRICK_WIDTH &&
                        ball.y + BALL_SIZE >= bricks[i][j].y && ball.y <= bricks[i][j].y + BRICK_HEIGHT) {
                        bricks[i][j].alive = 0; // Destroy brick
                        ball.dy = -ball.dy;
                    }
                }
            }
        }

        // Rendering
        SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 2, 255, 255, 255);
        SDL_Rect paddleRect = {paddle.x, paddle.y, paddle.width, paddle.height};
        SDL_RenderFillRect(renderer, &paddleRect);

        SDL_Rect ballRect = {ball.x, ball.y, BALL_SIZE, BALL_SIZE};
        SDL_RenderFillRect(renderer, &ballRect);

        for (int i = 0; i < BRICK_ROWS; i++) {
            for (int j = 0; j < BRICKS_PER_ROW; j++) {
                if (bricks[i][j].alive) {
                    SDL_Rect brickRect = {bricks[i][j].x, bricks[i][j].y, BRICK_WIDTH, BRICK_HEIGHT};
                    SDL_RenderFillRect(renderer, &brickRect);
                }
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Roughly 60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}*/


