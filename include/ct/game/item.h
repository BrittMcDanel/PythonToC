#ifndef GAME_ITEM
#define GAME_ITEM

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

typedef struct Item {
  ItemName item_name;
  ItemType item_type;
  Sprite sprite;
  Uint64 cost;
} Item;

typedef struct Array_Item_200 {
  Item arr[200];
  int size;
  int capacity;
} Array_Item_200;

void void_mfunc_Item_set_to_ItemPtr_GamePtr_ItemName(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Item* self, struct Game* game, ItemName item_name);

#endif // GAME_ITEM
