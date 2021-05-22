#ifndef GAME_SPRITE
#define GAME_SPRITE

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

struct CT_StackTrace;
struct Game;

typedef struct Sprite {
  Image image;
  RenderDst render_dst;
  Array_SDL_Rect_10 srcs;
  int current_frame_idx;
  Uint32 anim_speed;
  Uint32 spawn_time;
} Sprite;

void void_mfunc_Sprite_update_SpritePtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Sprite* self, struct Game* game);
void void_mfunc_Sprite_draw_SpritePtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Sprite* self, struct Game* game);
void void_mfunc_Sprite_draw_at_SpritePtr_GamePtr_SDL_RectPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Sprite* self, struct Game* game, struct SDL_Rect* unscaled_dst);

#endif // GAME_SPRITE
