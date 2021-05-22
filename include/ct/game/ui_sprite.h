#ifndef GAME_UI_SPRITE
#define GAME_UI_SPRITE

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
#include "input_events.h"
#include "shared_sprite.h"

struct CT_StackTrace;
struct Game;

typedef struct UISprite {
  Image image;
  RenderDst render_dst;
  SpriteSrcs* shared_srcs;
  int current_frame_idx;
  Uint32 anim_speed;
  Uint32 spawn_time;
  UIEvent ui_event;
  InputEvents input_events;
} UISprite;

typedef struct Array_UISprite_2 {
  UISprite arr[2];
  int size;
  int capacity;
} Array_UISprite_2;

typedef struct Array_UISprite_30 {
  UISprite arr[30];
  int size;
  int capacity;
} Array_UISprite_30;

typedef struct Array_UISprite_6 {
  UISprite arr[6];
  int size;
  int capacity;
} Array_UISprite_6;

typedef struct Array_UISprite_9 {
  UISprite arr[9];
  int size;
  int capacity;
} Array_UISprite_9;

typedef struct Array_UISprite_50 {
  UISprite arr[50];
  int size;
  int capacity;
} Array_UISprite_50;

typedef struct Array_UISprite_12 {
  UISprite arr[12];
  int size;
  int capacity;
} Array_UISprite_12;

typedef struct Array_UISprite_5 {
  UISprite arr[5];
  int size;
  int capacity;
} Array_UISprite_5;

typedef struct Array_UISprite_10 {
  UISprite arr[10];
  int size;
  int capacity;
} Array_UISprite_10;

void void_mfunc_UISprite_update_UISpritePtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UISprite* self, struct Game* game);
void void_mfunc_UISprite_draw_UISpritePtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UISprite* self, struct Game* game);

#endif // GAME_UI_SPRITE
