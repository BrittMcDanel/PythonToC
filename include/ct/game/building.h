#ifndef GAME_BUILDING
#define GAME_BUILDING

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
#include "sprite.h"
#include "constants.h"
#include "input_events.h"

struct CT_StackTrace;
struct Game;

typedef struct Building {
  BuildingName building_name;
  BuildingType building_type;
  SDL_Rect tile_point_hit_box;
  SDL_Point door_tile_point;
  Sprite sprite;
  bool is_shop;
  InputEvents input_events;
  int handle;
  bool in_use_in_pool;
} Building;

typedef struct Array_Building_2000 {
  Building arr[2000];
  int size;
  int capacity;
} Array_Building_2000;

void void_mfunc_Building_init_BuildingPtr_GamePtr_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Building* self, struct Game* game, int handle);
void void_mfunc_Building_set_to_BuildingPtr_GamePtr_BuildingName_SDL_PointPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Building* self, struct Game* game, BuildingName building_name, struct SDL_Point* move_grid_tile_point);
void void_mfunc_Building_on_click_BuildingPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Building* self, struct Game* game);
void void_mfunc_Building_update_BuildingPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Building* self, struct Game* game);
void void_mfunc_Building_draw_BuildingPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Building* self, struct Game* game);

#endif // GAME_BUILDING
