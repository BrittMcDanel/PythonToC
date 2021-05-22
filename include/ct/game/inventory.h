#ifndef GAME_INVENTORY
#define GAME_INVENTORY

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
#include "shared_item.h"

struct CT_StackTrace;
struct Game;

typedef struct InventorySlot {
  SharedItem shared_item;
  bool slot_is_empty;
} InventorySlot;

typedef struct Array_InventorySlot_50 {
  InventorySlot arr[50];
  int size;
  int capacity;
} Array_InventorySlot_50;

typedef struct Inventory {
  Array_InventorySlot_50 slots;
} Inventory;

void void_mfunc_Inventory_init_InventoryPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Inventory* self);
void void_mfunc_Inventory_clear_slot_InventoryPtr_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Inventory* self, int slot_idx);
int int_mfunc_Inventory_next_empty_slot_handle_InventoryPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Inventory* self);
void void_mfunc_Inventory_add_item_InventoryPtr_GamePtr_ItemName_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Inventory* self, struct Game* game, ItemName item_name, int quantity);
bool bool_mfunc_Inventory_inventory_is_empty_InventoryPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Inventory* self);
bool bool_mfunc_Inventory_has_merchant_sellable_items_InventoryPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Inventory* self);

#endif // GAME_INVENTORY
