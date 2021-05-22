#ifndef GAME_COMP_POSITION
#define GAME_COMP_POSITION

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "stbttf_sdl.h"
#include "utils.h"

struct CT_StackTrace;

typedef struct CompPosition {
  int go_idx;
  SDL_Rect dst;
} CompPosition;

typedef struct Array_CompPosition_3000 {
  CompPosition arr[3000];
  int size;
  int capacity;
} Array_CompPosition_3000;


#endif // GAME_COMP_POSITION
