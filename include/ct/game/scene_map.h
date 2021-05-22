#ifndef GAME_SCENE_MAP
#define GAME_SCENE_MAP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "stbttf_sdl.h"
#include "engine.h"
#include "ct_array.h"
#include "constants.h"
#include "game_database.h"

struct CT_StackTrace;

typedef struct SceneMap {
  GameDatabase game_database;
} SceneMap;


#endif // GAME_SCENE_MAP
