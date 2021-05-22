#ifndef GAME_COMPONENTS
#define GAME_COMPONENTS

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

typedef struct CPosition {
  int go_handle;
  SDL_Rect dst;
} CPosition;

typedef struct Array_CPosition_3000 {
  CPosition arr[3000];
  int size;
  int capacity;
} Array_CPosition_3000;

typedef struct CSprite {
  int go_handle;
  Image image;
  SDL_Rect src;
} CSprite;

typedef struct Array_CSprite_3000 {
  CSprite arr[3000];
  int size;
  int capacity;
} Array_CSprite_3000;


#endif // GAME_COMPONENTS
