#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdlib.h>
#include <windows.h>
#include <SDL2/SDL_ttf.h>

#include "randomgenerate.h"
#include "ball.h"
#include "bricks.h"
#include "paddle.h"
#include "images.h"
#include "audio.h"
#include "text.h"
#include "scores.h"
#define width 1500
#define height 850

int lvlpage(char*);//declaration
int startgame();
typedef struct
{
    SDL_Rect startlevel;
    char state;

}levels;
 levels level[6];



int main(int argc,char **argv)
{
    int *maxlevel=(int*)malloc(4);
    int *chosenlvl=(int*)malloc(4);
    char username[100];
    SDL_Log("\t\t\t\t\t\tWELCOME TO ASTROID BREAKER GAME ");
    SDL_Log("enter the user name to enter the game");

    scanf("%s",username);
    if(!checkuser(username)){//new user
            save_userdetails(username,1,0,1,0);
    }


    int levelplay=1;
    homescreen: *chosenlvl=lvlpage(username);

if(*chosenlvl){
        if(*chosenlvl==1)
                levelplay=1;
        else
            levelplay=2;

    int maxscore=0;
    int besttime=0;
    load_userdetails(username,*chosenlvl,&maxscore,&besttime);
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_AUDIO);
    TTF_Init();
    SDL_Init(SDL_INIT_TIMER);

    //initialise sdlimage for importing jpg image
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG|IMG_INIT_WEBP);
    Mix_Init(MIX_INIT_MP3|MIX_INIT_WAVPACK);
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);


    Mix_Music *backgroundmusic=init_audio("background.mp3");
    Mix_VolumeMusic(10);

    //create an SDL window
    lvl2:SDL_Window *window=SDL_CreateWindow("thriller brick buster game ",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_ALLOW_HIGHDPI|SDL_WINDOW_BORDERLESS);

    //create renderer to accelerate and sync with display refresh rate
    SDL_Renderer *rendererpointer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
     //initialize the SDL for video type


    SDL_Texture* image_texture=images_init(rendererpointer,"Space-Background-Images.jpg");//background image load
    SDL_Texture* ball_image_texture=images_init(rendererpointer,"earth.png");//ball image
    SDL_Texture* paddle_image_texture=images_init(rendererpointer,"pngwing.png");
    SDL_Texture* brick1_image_texture=images_init(rendererpointer,"brick1.png");
    SDL_Texture* brick2_image_texture=images_init(rendererpointer,"brick2.png");
    SDL_Texture* brick3_image_texture=images_init(rendererpointer,"brick3.png");
    SDL_Texture* brickbreak_image_texture=images_init(rendererpointer,"brick5.png");
    SDL_Rect* image_location=image_present_location(0,0,width,height);//location for background image


    //play the music
    label1: Mix_PlayMusic(backgroundmusic,-1);//label for retry
    int score=0;
    int life=3,brickvanish=0,brickvanish2=0;
    int *cnt=&brickvanish;
    int running=1,x,y,c=1;
    int resume=1,tryagain=1,paused=0,lvl2try=0;


    char timer[50];
    char lifes[20];

    char mscore[100];
    char btime[100];
    char leveldisplay[50];
    SDL_Rect timerect={5,20,100,30};
    SDL_Rect liferect={1350,20,100,30};
    SDL_Rect maxscoreloc={900,20,200,30};
    SDL_Rect btimeloc={200,20,200,30};
    SDL_Rect lvldisplayloc={600,20,200,30};

    SDL_Event event2;//values for pause menu
    SDL_Rect rectpause={0,0,500,600};
    SDL_Rect rect1={150,0,200,100};
    SDL_Rect rect2={180,150,150,100};
    SDL_Rect rect3={180,300,150,100};
    SDL_Rect rect4={180,450,150,100};
    SDL_Window* window2;
    SDL_Renderer* renderer2;

    SDL_Event event3;//values for try again menu
    SDL_Window* window3;
    SDL_Renderer* renderer3;

    SDL_Rect rect_head={20,0,480,100};

    //values for window 4(completed window)
    SDL_Window* window4;
    SDL_Renderer* renderer4;
    SDL_Event event4;
    TTF_Font* font=TTF_OpenFont("GloriousChristmas-BLWWB.ttf",30);//including fonts

    SDL_Color color={255,100,200};
    UINT32 pausetime,time;
    UINT32 start_time=SDL_GetTicks();

     UINT32 lvl2time=SDL_GetTicks();

    struct Brick bricks[brick_rows][brick_columns];//initializing the values to brick structure
    if(*chosenlvl==1)
        initGame(bricks,rendererpointer,brick1_image_texture,brick2_image_texture,brick3_image_texture);//initial present of all bricks
    else if(*chosenlvl==2)
            initGame2(bricks,rendererpointer,brick1_image_texture,brick2_image_texture,brick3_image_texture);
    initBall(width/2,600);//initialing the values to ball
    initPaddle(rendererpointer,paddle_image_texture);

    //we explicitly start the game from the second level if the chosen is second
    while(running)
    {
                SDL_Event event;
                while(SDL_PollEvent(&event))
                {

                    if(event.type==SDL_QUIT)
                    {
                        running=0;

                    }
                    //to detect whether there is key pressed
                    else if(event.type==SDL_KEYDOWN)
                    {
                        switch(event.key.keysym.sym)
                         {
                            case SDLK_p://for pausing the music
                                if(Mix_PausedMusic())
                                    Mix_ResumeMusic();
                                else
                                    Mix_PauseMusic();

                                break;

                            case SDLK_ESCAPE://for pausing the game
                                resume=!resume;
                                            //initializing pause window
                                if(!resume&&tryagain){

                                         window2=SDL_CreateWindow("",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,500,600,SDL_WINDOW_ALWAYS_ON_TOP|SDL_WINDOW_BORDERLESS);
                                         renderer2=SDL_CreateRenderer(window2,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
                                        SDL_Texture* pausebackground_image_texture=images_init(renderer2,"pausebackground.jpg");
                                        SDL_Texture* font_texture=text_init(renderer2,font,"NEW GAME",&color);
                                        SDL_Texture* font_head_texture=text_init(renderer2,font,"PAUSE MENU",&color);
                                        SDL_Texture* font_quit_texture=text_init(renderer2,font,"QUIT",&color);
                                        SDL_Texture* font_resume_texture=text_init(renderer2,font,"RESUME",&color);
                                        SDL_RenderClear(renderer2);
                                        render_image(renderer2,pausebackground_image_texture,&rectpause);
                                        if(Mix_PausedMusic())
                                                 paused=1;

                                        Mix_PauseMusic();


                                        render_text(renderer2,font_head_texture,&rect1);
                                        render_text(renderer2,font_resume_texture,&rect2);
                                        render_text(renderer2,font_texture,&rect3);
                                        render_text(renderer2,font_quit_texture,&rect4);
                                        SDL_RenderPresent(renderer2);



                                }
                                break;
                         }
                    }



                }

            if(resume&&tryagain)//starting of the game
                {
                    Uint32 current_time = SDL_GetTicks();//geting the time

                    if(levelplay==2||chosenlvl==2)//choosing between chosen level or the level after completing the level1
                    {
                       time=current_time-lvl2time;

                    }
                    else
                        time = (current_time - start_time);

                    render_image(rendererpointer,image_texture,image_location);//for background
                    snprintf(timer,50,"time:%d s",time/1000);
                    snprintf(lifes,20,"life left: %d",life);
                    snprintf(leveldisplay,20,"level: %d",levelplay);
                    snprintf(mscore,100,"max score: %d",maxscore);
                    snprintf(btime,100,"best time : %d s",besttime);

                    SDL_Texture* time_texture=text_init(rendererpointer,font,timer,&color);
                    render_text(rendererpointer,time_texture,&timerect);//presenting timer
                     SDL_Texture* life_texture=text_init(rendererpointer,font,lifes,&color);
                    render_text(rendererpointer,life_texture,&liferect);//presenting life
                    SDL_Texture* mscore_texture=text_init(rendererpointer,font,mscore,&color);
                    render_text(rendererpointer,mscore_texture,&maxscoreloc);//presenting max score
                    SDL_Texture* btime_texture=text_init(rendererpointer,font,btime,&color);
                    render_text(rendererpointer,btime_texture,&btimeloc);//presenting max score
                    SDL_Texture* leveldisp_texture=text_init(rendererpointer,font,leveldisplay,&color);
                    render_text(rendererpointer,leveldisp_texture,&lvldisplayloc);//presenting max score


                    //rendering the ball and padddle which is common for the all level
                    moveBall();
                    renderball_image(rendererpointer,ball_image_texture);
                    movePaddle(&event);
                    render_image_Paddle(rendererpointer,paddle_image_texture);
                    checkBallCollision(width,height);

                    if(levelplay==2||*chosenlvl==2)
                        renderBricks2(rendererpointer,bricks,cnt,brick1_image_texture,brick2_image_texture,brick3_image_texture,brickbreak_image_texture);
                    else{
                        renderBricks(rendererpointer,bricks,cnt,brick1_image_texture,brick2_image_texture,brick3_image_texture);
                    }
                    if(brickvanish==brick_rows*brick_columns)
                    {//initiation of second leveland completion of first level
                            score=(int)time/10000+life*100+brickvanish;
                            save_userdetails(username,*chosenlvl,score,2,time/1000);
                            *maxlevel=2;
                            level[1].state='u';//label for retry
                            cnt=&brickvanish2;
                            levelplay=2;
                            lvl2time=SDL_GetTicks();
                            score=0;
                            life=3;//reseting the ball life
                            SDL_RenderPresent(rendererpointer);


                            if(!lvl2try){
                                lvl2complete:Mix_PauseMusic();
                                SDL_RenderClear(rendererpointer);//the below code is to make completion window
                                window4=SDL_CreateWindow("",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,500,600,SDL_WINDOW_ALWAYS_ON_TOP|SDL_WINDOW_BORDERLESS);
                                renderer4=SDL_CreateRenderer(window4,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
                                SDL_Texture* background_com_tex=images_init(renderer4,"tryagainbackground..png");
                                SDL_Texture* head_com_tex=text_init(renderer4,font,"CONGRATS  YOU   WON",&color);
                                SDL_Texture* tryagain_com_tex=text_init(renderer4,font,"TRY AGAIN",&color);
                                SDL_Texture* nextlvl_tex=text_init(renderer4,font,"NEXT LEVEL",&color);
                                SDL_Texture* quit_tex=text_init(renderer4,font,"QUIT",&color);
                                render_image(renderer4,background_com_tex,&rectpause);
                                render_text(renderer4,head_com_tex,&rect_head);
                                render_text(renderer4,tryagain_com_tex,&rect2);
                                render_text(renderer4,nextlvl_tex,&rect3);
                                render_text(renderer4,quit_tex,&rect4);
                                SDL_RenderPresent(renderer4);
                                c=1;
                                lvl2try=1;
                                while(c)
                                {


                                    while(SDL_PollEvent(&event4))
                                    {

                                    SDL_GetMouseState(&x,&y);
                                    SDL_Rect mouserect={x,y,2,2};
                                    if(event4.type==SDL_MOUSEBUTTONDOWN){
                                            if(SDL_HasIntersection(&rect3,&mouserect)){//for next level
                                                        initBall(width/2,600);

                                                        initGame2(bricks,rendererpointer,brick1_image_texture,brick2_image_texture,brick3_image_texture);


                                                        SDL_DestroyWindow(window4);
                                                        Mix_ResumeMusic();
                                                        c=0;
                                                        break;





                                            }
                                            else if(SDL_HasIntersection(&mouserect,&rect4)){//for quit from game
                                                SDL_DestroyWindow(window4);
                                                running=0;
                                                IMG_Quit();
                                                SDL_DestroyTexture(image_texture);
                                                SDL_DestroyTexture(ball_image_texture);
                                                SDL_DestroyTexture(paddle_image_texture);
                                                SDL_DestroyTexture(brick1_image_texture);
                                                SDL_DestroyTexture(brick2_image_texture);
                                                SDL_DestroyTexture(brick3_image_texture);
                                                SDL_DestroyTexture(brickbreak_image_texture);
                                                Mix_FreeMusic(backgroundmusic);
                                                TTF_CloseFont(font);


                                                Mix_CloseAudio();
                                                //free memory for image
                                                SDL_DestroyRenderer(rendererpointer);
                                                SDL_DestroyWindow(window);
                                                SDL_DestroyWindow(window2);
                                                SDL_DestroyRenderer(renderer3);
                                                goto homescreen;
                                                c=0;
                                            }
                                            else if(SDL_HasIntersection(&mouserect,&rect2)){//tryagain option
                                                SDL_DestroyWindow(window4);
                                                if(levelplay==1)
                                                    goto label1;
                                                else{
                                                    lvl2try=1;//to avoid the window create when we retry
                                                    goto lvl2;

                                                    }
                                            }



                                        }
                                }
                        }
                    }
                }


                if(ball.y>height){// ball life
                        if(life==1)
                        {
                            tryagain=!tryagain;
                            Mix_PauseMusic();
                            window3=SDL_CreateWindow("",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,500,600,SDL_WINDOW_ALWAYS_ON_TOP|SDL_WINDOW_BORDERLESS);
                            renderer3=SDL_CreateRenderer(window3,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

                            SDL_Texture* background_texture=images_init(renderer3,"tryagainbackground..png");
                            render_image(renderer3,background_texture,&rectpause);
                            SDL_Texture* font_head_texture=text_init(renderer3,font,"LOST ALL YOUR LIFES",&color);
                            render_image(renderer3,font_head_texture,&rect_head);
                            SDL_Texture* tryagain_texture=text_init(renderer3,font,"Try Again",&color);
                            render_text(renderer3,tryagain_texture,&rect3);
                            SDL_Texture* quit_texture=text_init(renderer3,font,"quit",&color);
                            render_text(renderer3,quit_texture,&rect4);
                            SDL_Texture* heart_texture=images_init(renderer3,"heart.png");
                            render_image(renderer3,heart_texture,&rect2);

                            SDL_RenderPresent(renderer3);
                            SDL_Delay(100);
                            SDL_Texture* heart_break_texture=images_init(renderer3,"heartbreak.png");
                            render_image(renderer3,heart_break_texture,&rect2);

                            SDL_RenderPresent(renderer3);

                            while(1){
                                while(SDL_PollEvent(&event3))
                                {
                                        SDL_GetMouseState(&x,&y);
                                        SDL_Rect mouserect={x,y,2,2};
                                        if(event3.type==SDL_MOUSEBUTTONDOWN){
                                        if(SDL_HasIntersection(&rect3,&mouserect)){
                                                        SDL_DestroyWindow(window3);

                                                        if(levelplay==1)
                                                            goto label1;//restarting the game so label 1
                                                        else{
                                                            lvl2try=1;//to avoid the creation of the window while retry
                                                            goto lvl2;

                                                        }


                                        }
                                        else if(SDL_HasIntersection(&mouserect,&rect4)){
                                            SDL_DestroyWindow(window3);
                                            running=0;
                                             IMG_Quit();
                                            SDL_DestroyTexture(image_texture);
                                            SDL_DestroyTexture(ball_image_texture);
                                            SDL_DestroyTexture(paddle_image_texture);
                                            SDL_DestroyTexture(brick1_image_texture);
                                            SDL_DestroyTexture(brick2_image_texture);
                                            SDL_DestroyTexture(brick3_image_texture);
                                            SDL_DestroyTexture(brickbreak_image_texture);
                                            Mix_FreeMusic(backgroundmusic);
                                            TTF_CloseFont(font);


                                            Mix_CloseAudio();
                                            //free memory for image
                                            SDL_DestroyRenderer(rendererpointer);
                                            SDL_DestroyWindow(window);
                                            SDL_DestroyWindow(window2);
                                            SDL_DestroyRenderer(renderer3);
                                            goto homescreen;

                                        }
                                }

                            }



                        }
                    }
                    life--;
                    initBall(width/2,500);
                }
                brickvanish=0;
                if(brickvanish2==brick_columns*brick_rows)//condition checking for the bricks2
                {
                    score=(int)time/10000+life*100+brickvanish;
                    save_userdetails(username,2,score,2,time);
                    lvl2try=0;
                    goto lvl2complete;//this to go for the completion window
                }
                brickvanish2=0;

                if(levelplay==2||*chosenlvl==2)
                    brickdestroy2(rendererpointer,bricks);
                else
                    brickdestroy(rendererpointer,bricks);

                SDL_RenderPresent(rendererpointer);
                SDL_Delay(16);

            }
            else if(tryagain)
                {//rendering the pause window

                    pausetime=SDL_GetTicks();//the time in pause menu
                    SDL_RenderPresent(renderer2);
                    while(SDL_PollEvent(&event2))
                    {


                                SDL_GetMouseState(&x,&y);
                                SDL_Rect mouserect={x,y,2,2};
                                if(event2.type==SDL_MOUSEBUTTONDOWN){
                                        if(SDL_HasIntersection(&rect3,&mouserect)){
                                                        SDL_DestroyWindow(window2);
                                                         if(levelplay==1)//retry for level 1
                                                            goto label1;
                                                        else{
                                                            lvl2try=1;
                                                            goto lvl2;//retry for level 2

                                                            }

                                        }
                                        else if(SDL_HasIntersection(&mouserect,&rect4)){
                                            SDL_DestroyWindow(window2);
                                            IMG_Quit();//free up all memory
                                            SDL_DestroyTexture(image_texture);
                                            SDL_DestroyTexture(ball_image_texture);
                                            SDL_DestroyTexture(paddle_image_texture);
                                            SDL_DestroyTexture(brick1_image_texture);
                                            SDL_DestroyTexture(brick2_image_texture);
                                            SDL_DestroyTexture(brick3_image_texture);
                                            SDL_DestroyTexture(brickbreak_image_texture);
                                            Mix_FreeMusic(backgroundmusic);
                                            TTF_CloseFont(font);


                                            Mix_CloseAudio();
                                            //free memory for image
                                            SDL_DestroyRenderer(rendererpointer);
                                            SDL_DestroyWindow(window);
                                            SDL_DestroyWindow(window2);
                                            SDL_DestroyRenderer(renderer3);
                                            goto homescreen;



                                        }
                                        else if(SDL_HasIntersection(&mouserect,&rect2)){
                                            SDL_DestroyWindow(window2);
                                            if(!paused){
                                                    Mix_ResumeMusic();
                                                    paused=0;

                                            }
                                            resume=!resume;
                                        }



                                }
                }
            }
        }

    // to release the memory
    IMG_Quit();
    SDL_DestroyTexture(image_texture);
    SDL_DestroyTexture(ball_image_texture);
    SDL_DestroyTexture(paddle_image_texture);
    SDL_DestroyTexture(brick1_image_texture);
    SDL_DestroyTexture(brick2_image_texture);
    SDL_DestroyTexture(brick3_image_texture);
    SDL_DestroyTexture(brickbreak_image_texture);
    Mix_FreeMusic(backgroundmusic);
    TTF_CloseFont(font);
    free(chosenlvl);

    Mix_CloseAudio();
    //free memory for image
    SDL_DestroyRenderer(rendererpointer);
    SDL_DestroyWindow(window);
    SDL_DestroyWindow(window2);
    SDL_DestroyRenderer(renderer3);
    SDL_Quit();


}



    return 0;

}
int lvlpage(char *username)
{
    if(startgame()){
    SDL_Init(SDL_INIT_VIDEO);//the label is to come back to level page when we give exit in the pause
    SDL_Init(SDL_INIT_AUDIO);
    TTF_Init();
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG|IMG_INIT_WEBP);
    int x,y;
    TTF_Font* font=TTF_OpenFont("GloriousChristmas-BLWWB.ttf",30);//including fonts
    SDL_Color color={250,0,0};
    char leveltext[50];
    SDL_Rect title={450,30,500,100};
    SDL_Rect rectlevel={0,0,width,height};
     SDL_Rect rect4={700,650,150,100};

    int maxulevel;
    maxulevel=loadmaxlevel(username);

    for(int i=0;i<6;i++)
    {

        level[i].startlevel.x =i*(200+20)+10;    // Calculate the x position for each brick
        level[i].startlevel.y = 200;   // Calculate the y position for each brick

        level[i].startlevel.w=200;
        level[i].startlevel.h=100;
        if(i+1>maxulevel)
            level[i].state='l';
        else
            level[i].state='u';
    }
    SDL_Event levelevent;
    SDL_Window *windowstart=SDL_CreateWindow("",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_BORDERLESS|SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *rendererstart=SDL_CreateRenderer(windowstart,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    SDL_Texture *level_background=images_init(rendererstart,"level_background.png");
    render_image(rendererstart,level_background,&rectlevel);

    level[0].state=1;//the first level is always unlocked

    SDL_Texture *level_title=text_init(rendererstart,font,"LEVEL SELECTION",&color);
    render_text(rendererstart,level_title,&title);
    SDL_Texture* quit_tex=text_init(rendererstart,font,"EXIT",&color);
    render_text(rendererstart,quit_tex,&rect4);

    for(int i=0;i<6;i++)
    {
        if(level[i].state=='l')
        {
            SDL_Texture *lock_image=images_init(rendererstart,"lock.png");
            render_image(rendererstart,lock_image,&level[i].startlevel);
        }
        SDL_SetRenderDrawColor(rendererstart,200,200,200,200);
        SDL_RenderDrawRect(rendererstart,&level[i].startlevel);
        SDL_RenderPresent(rendererstart);
        snprintf(leveltext,50,"level: %d",i+1);
        SDL_Texture *level_texture=text_init(rendererstart,font,leveltext,&color);
        render_text(rendererstart,level_texture,&level[i].startlevel);
    }
    SDL_RenderPresent(rendererstart);
        int c=1;
        while(c)
        {


                while(SDL_PollEvent(&levelevent))
                {

                                    SDL_GetMouseState(&x,&y);
                                    SDL_Rect mouserect={x,y,4,4};
                                    if(levelevent.type==SDL_MOUSEBUTTONDOWN){
                                            if(SDL_HasIntersection(&level[0].startlevel,&mouserect)){
                                                        SDL_DestroyWindow(windowstart);


                                                        c=0;

                                                        return 1;


                                            }
                                            else if(SDL_HasIntersection(&level[1].startlevel,&mouserect)){
                                                    if(level[1].state=='u'){

                                                        SDL_DestroyWindow(windowstart);
                                                        c=0;

                                                        return 2;
                                                    }

                                            }

                                            else if(SDL_HasIntersection(&rect4,&mouserect)){
                                                        SDL_DestroyWindow(windowstart);
                                                        c=0;
                                                        return 0;

                                            }


                                        }
                                }
                        }


    }
}
int startgame()
{
     SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG|IMG_INIT_WEBP);
    int x,y;
    SDL_Rect rectlevel={0,0,width,height};
   SDL_Rect rect4={700,520,150,100};


    SDL_Event startevent;
    SDL_Window *windowstart=SDL_CreateWindow("",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_BORDERLESS|SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *rendererstart=SDL_CreateRenderer(windowstart,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    SDL_Texture *level_background=images_init(rendererstart,"startimage2.jpeg");
    render_image(rendererstart,level_background,&rectlevel);
     SDL_RenderPresent(rendererstart);
        int c=1;
        while(c)
                        {


                            while(SDL_PollEvent(&startevent))
                            {

                                    SDL_GetMouseState(&x,&y);
                                    SDL_Rect mouserect={x,y,2,2};
                                    if(startevent.type==SDL_MOUSEBUTTONDOWN){
                                            if(SDL_HasIntersection(&rect4,&mouserect)){
                                                        SDL_DestroyWindow(windowstart);


                                                        c=0;
                                                        return 1;


                                            }
                                    }
                            }
                        }
}


