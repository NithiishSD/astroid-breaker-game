 #include <SDL2/SDL_mixer.h>
 #include "audio.h"
 Mix_Music* init_audio(char* file)
 {

    return Mix_LoadMUS(file);

 }
Mix_Chunk* init_WAV(char* file){

   return Mix_LoadWAV(file);
 }
