#ifndef GAME_GAME_DATA
#define GAME_GAME_DATA

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "stbttf_sdl.h"
#include "image.h"
#include "utils.h"
#include "image.h"
#include "ct_array.h"
#include "sprite.h"
#include "shared_sprite.h"

struct CT_StackTrace;

typedef struct GameData {
  Uint64 money;
} GameData;


#endif // GAME_GAME_DATA
