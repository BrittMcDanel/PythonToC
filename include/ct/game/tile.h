#ifndef GAME_TILE
#define GAME_TILE

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
struct Game;

typedef struct Tile {
  SharedSprite sprite;
} Tile;

typedef struct Array_Tile_10000 {
  Tile arr[10000];
  int size;
  int capacity;
} Array_Tile_10000;

void void_mfunc_Tile_update_TilePtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Tile* self, struct Game* game);
void void_mfunc_Tile_draw_TilePtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Tile* self, struct Game* game);

#endif // GAME_TILE
