#ifndef GAME_UNIT_SPRITE
#define GAME_UNIT_SPRITE

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "stbttf_sdl.h"
#include "engine.h"
#include "utils.h"
#include "constants.h"
#include "image.h"
#include "ct_array.h"

struct CT_StackTrace;
struct Game;

typedef struct UnitSprite {
  Image image;
  SDL_Rect current_src;
  RenderDst render_dst;
  UnitAnimState anim_state;
  SDL_Point hit_box_size;
  Array_SDL_Rect_10 idle_down;
  Array_SDL_Rect_10 cast_down;
  Array_SDL_Rect_3 sit_down;
  Array_SDL_Rect_10 overworld_idle_down;
  Uint32 idle_anim_speed;
  Uint32 cast_anim_speed;
  Uint32 sit_anim_speed;
  Uint32 overworld_idle_anim_speed;
  Uint32 spawn_time;
  Uint32 anim_finish_time;
  bool playing_one_shot_anim;
} UnitSprite;

void void_mfunc_UnitSprite_set_to_UnitSpritePtr_GamePtr_UnitName(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitSprite* self, struct Game* game, UnitName unit_name);
void void_mfunc_UnitSprite_play_animation_UnitSpritePtr_GamePtr_UnitAnimState(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitSprite* self, struct Game* game, UnitAnimState anim_state);
void void_mfunc_UnitSprite_set_current_src_UnitSpritePtr_GamePtr_bool(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitSprite* self, struct Game* game, bool on_overworld_map);
void void_mfunc_UnitSprite_update_UnitSpritePtr_GamePtr_bool(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitSprite* self, struct Game* game, bool on_overworld_map);
void void_mfunc_UnitSprite_draw_UnitSpritePtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitSprite* self, struct Game* game);
void void_mfunc_UnitSprite_draw_idle_at_UnitSpritePtr_GamePtr_SDL_RectPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitSprite* self, struct Game* game, struct SDL_Rect* unscaled_dst);

#endif // GAME_UNIT_SPRITE
