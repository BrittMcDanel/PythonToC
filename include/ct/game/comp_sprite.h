#ifndef GAME_COMP_SPRITE
#define GAME_COMP_SPRITE

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "stbttf_sdl.h"
#include "image.h"
#include "utils.h"
#include "image.h"

struct CT_StackTrace;

typedef struct CompSprite {
  Image image;
  SDL_Rect src;
} CompSprite;

typedef struct Array_CompSprite_3000 {
  CompSprite arr[3000];
  int size;
  int capacity;
} Array_CompSprite_3000;


#endif // GAME_COMP_SPRITE
