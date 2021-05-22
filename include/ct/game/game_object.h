#ifndef GAME_GAME_OBJECT
#define GAME_GAME_OBJECT

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "stbttf_sdl.h"
#include "image.h"

struct CT_StackTrace;

typedef struct GameObject {
  int go_idx;
  int c_position_idx;
  int c_sprite_idx;
} GameObject;

typedef struct Array_GameObject_5000 {
  GameObject arr[5000];
  int size;
  int capacity;
} Array_GameObject_5000;


#endif // GAME_GAME_OBJECT
