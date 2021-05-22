#ifndef GAME_SHARED_ABILITY
#define GAME_SHARED_ABILITY

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
#include "ability.h"

struct CT_StackTrace;
struct Game;

typedef struct AbilityDB {
  Array_Ability_200 abilities;
} AbilityDB;

typedef struct SharedAbility {
  Ability* ability;
  RenderDst render_dst;
  int current_frame_idx;
  Uint32 spawn_time;
  int skill_points;
  int handle;
  bool in_use_in_pool;
} SharedAbility;

typedef struct Array_SharedAbility_30 {
  SharedAbility arr[30];
  int size;
  int capacity;
} Array_SharedAbility_30;

typedef struct Array_SharedAbility_10 {
  SharedAbility arr[10];
  int size;
  int capacity;
} Array_SharedAbility_10;

typedef struct Array_SharedAbility_5000 {
  SharedAbility arr[5000];
  int size;
  int capacity;
} Array_SharedAbility_5000;

void void_mfunc_AbilityDB_init_AbilityDBPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, AbilityDB* self, struct Game* game);
void void_mfunc_SharedAbility_set_to_SharedAbilityPtr_GamePtr_AbilityName(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, SharedAbility* self, struct Game* game, AbilityName ability_name);
void void_mfunc_SharedAbility_init_SharedAbilityPtr_GamePtr_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, SharedAbility* self, struct Game* game, int handle);
void void_mfunc_SharedAbility_update_SharedAbilityPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, SharedAbility* self, struct Game* game);
void void_mfunc_SharedAbility_draw_SharedAbilityPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, SharedAbility* self, struct Game* game);

#endif // GAME_SHARED_ABILITY
