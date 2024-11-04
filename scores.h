#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
void save_userdetails(char *username, int curlevel,int score,int maxlevel,int time);
void load_userdetails(char *username,int curlevel,int *maxscore,int *maxtime);
int checkuser(char *username);
int loadmaxlevel(char* username);
