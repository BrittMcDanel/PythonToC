#ifndef GAME_SHARED_SPRITE
#define GAME_SHARED_SPRITE

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

struct CT_StackTrace;
struct Game;

typedef struct SpriteSrcs {
  Image image;
  Array_SDL_Rect_10 srcs;
} SpriteSrcs;

typedef struct Array_SpriteSrcs_200 {
  SpriteSrcs arr[200];
  int size;
  int capacity;
} Array_SpriteSrcs_200;

typedef struct SpriteDB {
  Array_SpriteSrcs_200 srcs;
} SpriteDB;

typedef struct SharedSprite {
  SpriteSrcs* shared_srcs;
  RenderDst render_dst;
  int current_frame_idx;
  Uint32 anim_speed;
  Uint32 spawn_time;
} SharedSprite;

void void_mfunc_SpriteDB_init_SpriteDBPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, SpriteDB* self, struct Game* game);
SpriteSrcs* SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, SpriteDB* self, struct Game* game, ImageName image_name, struct SDL_Rect* rect);
void void_mfunc_SharedSprite_update_SharedSpritePtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, SharedSprite* self, struct Game* game);
void void_mfunc_SharedSprite_draw_SharedSpritePtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, SharedSprite* self, struct Game* game);

#endif // GAME_SHARED_SPRITE
