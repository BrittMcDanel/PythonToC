#ifndef GAME_WORLD
#define GAME_WORLD

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "stbttf_sdl.h"
#include "ct_array.h"
#include "image.h"
#include "utils.h"
#include "image.h"
#include "unit.h"
#include "map.h"
#include "utils.h"
#include "constants.h"
#include "guild.h"
#include "building.h"
#include "tween.h"
#include "path_finder.h"
#include "ability.h"
#include "shared_ability.h"
#include "shared_item.h"
#include "text.h"
#include "ui.h"
#include "game_data.h"

struct CT_StackTrace;
struct Game;

typedef struct World {
  UI ui;
  Array_Map_100 maps;
  Array_Building_2000 buildings;
  Array_Unit_3000 units;
  Array_Guild_100 guilds;
  Array_SharedItem_5000 items;
  Array_SharedAbility_5000 abilities;
  Array_TextSM_5000 damage_texts;
  Array_TweenXY_20000 tween_xys;
  int maps_last_in_use_handle;
  int buildings_last_in_use_handle;
  int units_last_in_use_handle;
  int guilds_last_in_use_handle;
  int items_last_in_use_handle;
  int abilities_last_in_use_handle;
  int damage_texts_last_in_use_handle;
  int tween_xys_last_in_use_handle;
  int visible_map_handle;
  PathFinder path_finder;
  SDL_Point mouse_down_tile_point;
} World;

int int_mfunc_World_get_handle_WorldPtr_HandleType(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, World* self, HandleType handle_type);
void void_mfunc_World_create_initial_maps_WorldPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, World* self, struct Game* game);
void void_mfunc_World_create_guilds_WorldPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, World* self, struct Game* game);
void void_mfunc_World_create_initial_units_WorldPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, World* self, struct Game* game);
void void_mfunc_World_init_WorldPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, World* self, struct Game* game);
void void_mfunc_World_release_handle_WorldPtr_HandleType_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, World* self, HandleType handle_type, int handle);
void void_mfunc_World_remove_all_tweens_WorldPtr_TweenType_HandleType_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, World* self, TweenType tween_type, HandleType handle_type, int handle);
void void_mfunc_World_handle_tween_on_start_WorldPtr_GamePtr_TweenCallbackPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, World* self, struct Game* game, struct TweenCallback* tween_callback);
void void_mfunc_World_remove_all_tweens_with_higher_level_type_WorldPtr_TweenHigherLevelType_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, World* self, TweenHigherLevelType tween_higher_level_type, int handle);
void void_mfunc_World_handle_tween_on_complete_WorldPtr_GamePtr_TweenCallbackPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, World* self, struct Game* game, struct TweenCallback* tween_callback);
void void_mfunc_World_update_tween_arr_WorldPtr_GamePtr_Array_TweenXY_20000Ptr_int_HandleType(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, World* self, struct Game* game, struct Array_TweenXY_20000* arr, int last_in_use_handle, HandleType tween_handle_type);
void void_mfunc_World_update_WorldPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, World* self, struct Game* game);
void void_mfunc_World_draw_WorldPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, World* self, struct Game* game);

#endif // GAME_WORLD
