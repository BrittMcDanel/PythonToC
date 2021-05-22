#ifndef GAME_TWEEN
#define GAME_TWEEN

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "stbttf_sdl.h"
#include "constants.h"
#include "utils.h"

struct CT_StackTrace;
struct Game;

typedef struct TweenCompletion {
  bool initial_has_started;
  bool completed;
} TweenCompletion;

typedef struct TweenCallback {
  TweenHigherLevelType tween_higher_level_type;
  TweenType tween_type;
  HandleType handle_type;
  int handle;
  SDL_Point tile_point;
  int warp_point_handle;
  bool is_final_point_in_path;
  int acting_unit_handle;
  int receiving_unit_handle;
  int merchant_unit_handle;
  int map_handle;
} TweenCallback;

typedef struct TweenXY {
  SDL_Rect start_val;
  SDL_Rect* val;
  SDL_Rect target_val;
  SDL_Rect* target_val_ptr;
  double speed;
  bool is_constant_speed;
  Uint32 spawn_time;
  Uint32 duration;
  Uint32 delay;
  bool has_started;
  DoublePoint double_point;
  TweenCallback callback;
  bool remove_in_update;
  int handle;
  bool in_use_in_pool;
} TweenXY;

typedef struct Array_TweenXY_20000 {
  TweenXY arr[20000];
  int size;
  int capacity;
} Array_TweenXY_20000;

void void_mfunc_TweenXY_init_TweenXYPtr_GamePtr_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, TweenXY* self, struct Game* game, int handle);
TweenCompletion TweenCompletion_mfunc_TweenXY_update_TweenXYPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, TweenXY* self, struct Game* game);
void void_mfunc_TweenXY_set_TweenXYPtr_GamePtr_SDL_RectPtr_SDL_RectPtr_SDL_RectPtr_bool_double_Uint32_Uint32_TweenCallbackPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, TweenXY* self, struct Game* game, struct SDL_Rect* start_val, struct SDL_Rect* val, struct SDL_Rect* target_val, bool is_constant_speed, double speed, Uint32 duration, Uint32 delay, TweenCallback* callback);

#endif // GAME_TWEEN
