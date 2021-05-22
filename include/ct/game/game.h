#ifndef GAME_GAME
#define GAME_GAME

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "stbttf_sdl.h"
#include "engine.h"
#include "world.h"
#include "scene_map.h"
#include "ct_array.h"
#include "constants.h"
#include "map.h"
#include "utils.h"
#include "shared_sprite.h"
#include "shared_item.h"
#include "unit_sprite.h"
#include "item.h"
#include "ability.h"
#include "inventory.h"
#include "shared_ability.h"
#include "shared_unit.h"
#include "ui.h"

struct CT_StackTrace;

typedef struct Game {
  Engine engine;
  SpriteDB sprite_db;
  UnitDB unit_db;
  ItemDB item_db;
  AbilityDB ability_db;
  World world;
  SDL_Point tile_size;
  SDL_Point max_map_size;
  SDL_Point move_grid_tile_size;
  int move_grid_ratio;
  Ability temp_ability;
  SharedAbility temp_shared_ability;
  Item temp_item;
  SharedItem temp_shared_item;
  Unit temp_unit;
} Game;

void void_mfunc_Game_start_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Game* self);
int int_mfunc_Game_get_current_frame_GamePtr_int_Uint32_Uint32(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Game* self, int srcs_size, Uint32 anim_speed, Uint32 spawn_time);
void void_mfunc_Game_update_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Game* self);
void void_mfunc_Game_draw_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Game* self);

#endif // GAME_GAME
