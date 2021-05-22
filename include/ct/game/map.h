#ifndef GAME_MAP
#define GAME_MAP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "stbttf_sdl.h"
#include "audio.h"
#include "engine.h"
#include "image.h"
#include "utils.h"
#include "image.h"
#include "ct_array.h"
#include "sprite.h"
#include "tile.h"
#include "render.h"
#include "constants.h"
#include "text.h"
#include "unit.h"
#include "tween.h"
#include "ability.h"
#include "shared_sprite.h"
#include "warp_point.h"

struct CT_StackTrace;
struct Game;

typedef struct Map {
  int rows;
  int cols;
  int move_grid_rows;
  int move_grid_cols;
  Array_Tile_10000 tiles;
  Array_WarpPoint_7 warp_points;
  Array_int_100 building_handles;
  Array_int_300 unit_handles;
  Array_int_300 ability_handles;
  Array_int_300 item_handles;
  Array_int_300 damage_text_handles;
  Unit unit_temporary;
  bool is_town_map;
  int handle;
  bool in_use_in_pool;
} Map;

typedef struct Array_Map_100 {
  Map arr[100];
  int size;
  int capacity;
} Array_Map_100;

void void_mfunc_Map_init_MapPtr_GamePtr_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Map* self, struct Game* game, int handle);
void void_mfunc_Map_create_initial_overworld_MapPtr_GamePtr_int_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Map* self, struct Game* game, int rows, int cols);
bool bool_mfunc_Map_unit_occupies_tile_point_move_grid_MapPtr_GamePtr_SDL_RectPtr_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Map* self, struct Game* game, struct SDL_Rect* tile_point_hit_box, int skip_unit_handle);
SDL_Point SDL_Point_mfunc_Map_get_random_unoccupied_move_grid_tile_point_MapPtr_GamePtr_SDL_RectPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Map* self, struct Game* game, struct SDL_Rect* tile_point_hit_box);
void void_mfunc_Map_create_initial_MapPtr_GamePtr_int_int_bool(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Map* self, struct Game* game, int rows, int cols, bool is_town_map);
bool bool_mfunc_Map_in_bounds_move_grid_MapPtr_SDL_PointPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Map* self, struct SDL_Point* p);
SDL_Point SDL_Point_mfunc_Map_get_random_merchant_shop_point_MapPtr_GamePtr_SDL_RectPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Map* self, struct Game* game, struct SDL_Rect* tile_point_hit_box);
SDL_Point SDL_Point_mfunc_Map_get_random_town_point_MapPtr_GamePtr_SDL_RectPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Map* self, struct Game* game, struct SDL_Rect* tile_point_hit_box);
int int_mfunc_Map_update_MapPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Map* self, struct Game* game);
void void_mfunc_Map_update_visible_map_MapPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Map* self, struct Game* game);
void void_mfunc_Map_units_insertion_sort_MapPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Map* self, struct Game* game);
void void_mfunc_Map_draw_MapPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Map* self, struct Game* game);

#endif // GAME_MAP
