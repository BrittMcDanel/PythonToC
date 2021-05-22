#ifndef GAME_AUDIO
#define GAME_AUDIO

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "stbttf_sdl.h"
#include "ct_array.h"
#include "constants.h"
#include "utils.h"

struct CT_StackTrace;

typedef struct BGMAudio {
  BGMAudioName audio_name;
  Mix_Music* audio;
} BGMAudio;

typedef struct Array_BGMAudio_50 {
  BGMAudio arr[50];
  int size;
  int capacity;
} Array_BGMAudio_50;

typedef struct SEAudio {
  SEAudioName audio_name;
  Mix_Chunk* audio;
} SEAudio;

typedef struct Array_SEAudio_100 {
  SEAudio arr[100];
  int size;
  int capacity;
} Array_SEAudio_100;


#endif // GAME_AUDIO
