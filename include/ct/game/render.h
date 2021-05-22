#ifndef GAME_RENDER
#define GAME_RENDER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "stbttf_sdl.h"
#include "engine.h"
#include "image.h"
#include "utils.h"
#include "image.h"
#include "ct_array.h"

struct CT_StackTrace;

typedef struct RenderSprite {
  SDL_Texture* texture;
  SDL_Rect src;
  SDL_Rect dst;
  int layer;
  bool is_hidden;
} RenderSprite;


#endif // GAME_RENDER
