#ifndef GAME_WARP_POINT
#define GAME_WARP_POINT

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
#include "constants.h"
#include "shared_sprite.h"

struct CT_StackTrace;
struct Game;

typedef struct WarpPoint {
  WarpPointName warp_point_name;
  SDL_Point tile_point;
  SDL_Point tile_point_move_grid;
  SDL_Point warp_to_tile_point;
  SDL_Point warp_to_tile_point_move_grid;
  int warp_to_map_handle;
  SharedSprite sprite;
} WarpPoint;

typedef struct Array_WarpPoint_7 {
  WarpPoint arr[7];
  int size;
  int capacity;
} Array_WarpPoint_7;

void void_mfunc_WarpPoint_set_WarpPointPtr_GamePtr_WarpPointName_SDL_PointPtr_SDL_PointPtr_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, WarpPoint* self, struct Game* game, WarpPointName warp_point_name, struct SDL_Point* tile_point, struct SDL_Point* warp_to_tile_point, int warp_to_map_handle);

#endif // GAME_WARP_POINT
