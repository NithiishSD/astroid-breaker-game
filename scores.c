
#include "scores.h"

void save_userdetails(char *username, int curlevel,int score,int maxlevel,int time)
{
    FILE *file = fopen("scores.txt", "a+");
    if (file != NULL) {
        fprintf(file, "%s %d %d %d %d\n", username,curlevel,score,time,maxlevel);

    }
    fclose(file);
}
void load_userdetails(char *username,int curlevel,int *maxscore,int *maxtime)
{

        int c=1;
        FILE *fp=fopen("scores.txt","r");
        if(fp!=NULL){
             int score,time,presentlevel,pretime[10];
              char str[50];
             while(1){
                       if(feof(fp))
                                 break;


                        fscanf(fp,"%s %d %d %d %*d",str,&presentlevel,&score,&time);
                        if(c&&time!=0&&presentlevel==curlevel&&strcmp(str,username)==0){//this is for because the least time is always zero
                            *maxtime=time;
                            c=0;
                        }

                       if(strcmp(str,username)==0&&presentlevel==curlevel)
                       {
                                    if(*maxscore<score)
                                               *maxscore=score;
                                    if(time<(*maxtime)&&time!=0)
                                                 *maxtime=time;

                        }

              }

        }
}
int loadmaxlevel(char* username)
{
    int maxlevel=1;
     FILE *fp=fopen("scores.txt","r");
        if(fp!=NULL){
             int level;
              char str[50];
             while(1){
                       if(feof(fp))
                                 break;


                        fscanf(fp,"%s %*d %*d %*d %d",str,&level);
                        if(strcmp(str,username)==0){
                            if(maxlevel<level)
                                maxlevel=level;
                        }

             }
        }
        return maxlevel;
}
int checkuser(char *username){
        FILE *fp=fopen("scores.txt","r");
        if(fp!=NULL){
                 char str[50];
                    int score,time,level,presentlevel;

             while(1){
                    if(feof(fp))
                        break;

                    fscanf(fp,"%s %d %d %d %d",str,&presentlevel,&score,&time,&level);
                    if(strcmp(str,username)==0)
                       {
                           return 1;
                       }

            }
        }
        return 0;
}




