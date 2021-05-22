#ifndef GAME_ABILITY
#define GAME_ABILITY

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

struct CT_StackTrace;
struct Game;

typedef struct AbilityStats {
  Uint64 damage;
  int range;
  int max_skill_points;
} AbilityStats;

typedef struct Ability {
  AbilityName ability_name;
  AbilityStats stats;
  Sprite sprite;
  Sprite portrait;
  bool is_projectile;
  double projectile_speed;
  SDL_Point start_offset;
  Uint32 delay;
  int handle;
  bool in_use_in_pool;
} Ability;

typedef struct Array_Ability_200 {
  Ability arr[200];
  int size;
  int capacity;
} Array_Ability_200;

void void_mfunc_Ability_set_to_AbilityPtr_GamePtr_AbilityName(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Ability* self, struct Game* game, AbilityName ability_name);

#endif // GAME_ABILITY
