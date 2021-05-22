#ifndef GAME_SHARED_UNIT
#define GAME_SHARED_UNIT

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
#include "unit.h"

struct CT_StackTrace;
struct Game;

typedef struct UnitDB {
  Array_Unit_200 units;
} UnitDB;

void void_mfunc_UnitDB_init_UnitDBPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitDB* self, struct Game* game);
struct Unit* UnitPtr_mfunc_UnitDB_get_unit_UnitDBPtr_UnitName(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitDB* self, UnitName unit_name);

#endif // GAME_SHARED_UNIT
