#ifndef GAME_SHARED_ITEM
#define GAME_SHARED_ITEM

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
#include "item.h"

struct CT_StackTrace;
struct Game;

typedef struct ItemDB {
  Array_Item_200 items;
} ItemDB;

typedef struct SharedItem {
  Item* item;
  RenderDst render_dst;
  int quantity;
  int drop_chance;
  int current_frame_idx;
  Uint32 spawn_time;
  int handle;
  bool in_use_in_pool;
} SharedItem;

typedef struct Array_SharedItem_5 {
  SharedItem arr[5];
  int size;
  int capacity;
} Array_SharedItem_5;

typedef struct Array_SharedItem_5000 {
  SharedItem arr[5000];
  int size;
  int capacity;
} Array_SharedItem_5000;

void void_mfunc_ItemDB_init_ItemDBPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, ItemDB* self, struct Game* game);
void void_mfunc_SharedItem_set_to_SharedItemPtr_GamePtr_ItemName_int_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, SharedItem* self, struct Game* game, ItemName item_name, int quantity, int drop_chance);
void void_mfunc_SharedItem_init_SharedItemPtr_GamePtr_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, SharedItem* self, struct Game* game, int handle);
void void_mfunc_SharedItem_update_SharedItemPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, SharedItem* self, struct Game* game);
void void_mfunc_SharedItem_draw_SharedItemPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, SharedItem* self, struct Game* game);

#endif // GAME_SHARED_ITEM
