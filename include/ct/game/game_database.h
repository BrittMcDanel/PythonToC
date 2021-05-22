#ifndef GAME_GAME_DATABASE
#define GAME_GAME_DATABASE

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "stbttf_sdl.h"
#include "components.h"
#include "ct_array.h"
#include "game_object.h"
#include "image.h"

struct CT_StackTrace;

typedef struct GameDatabase {
  Array_GameObject_5000 game_objects;
  Array_CPosition_3000 c_positions;
  Array_CSprite_3000 c_sprites;
  Array_GameObject_5000 render_sprite_table;
} GameDatabase;


#endif // GAME_GAME_DATABASE
