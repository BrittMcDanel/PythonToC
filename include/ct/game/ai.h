#ifndef GAME_AI
#define GAME_AI

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "stbttf_sdl.h"
#include "engine.h"
#include "utils.h"
#include "ct_array.h"
#include "constants.h"

struct CT_StackTrace;

typedef struct AIAbility {
  int unit_ability_handle;
  AIAbilityCondition condition;
  bool is_empty;
} AIAbility;

typedef struct Array_AIAbility_30 {
  AIAbility arr[30];
  int size;
  int capacity;
} Array_AIAbility_30;

void void_mfunc_AIAbility_clear_AIAbilityPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, AIAbility* self);
void void_mfunc_AIAbility_set_AIAbilityPtr_int_AIAbilityCondition(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, AIAbility* self, int unit_ability_handle, AIAbilityCondition condition);

#endif // GAME_AI
