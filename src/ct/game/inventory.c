#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "ct_stacktrace.h"
#include "inventory.h"
#include "engine.h"
#include "image.h"
#include "utils.h"
#include "image.h"
#include "ct_array.h"
#include "sprite.h"
#include "constants.h"
#include "shared_item.h"
#include "game.h"

void void_mfunc_Inventory_init_InventoryPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Inventory* self) {
    int i = 0;
    InventorySlot* slot = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->slots.size = 50;
    for (i = 0; i < self->slots.size; i++) {
        slot = &self->slots.arr[i];
        slot->slot_is_empty = true;
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Inventory_clear_slot_InventoryPtr_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Inventory* self, int slot_idx) {
    InventorySlot* slot = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (slot_idx < 0 || slot_idx > self->slots.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", slot_idx, self->slots.size);
            ct_stacktrace_push(ct_stacktrace, 90, 70);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        slot = &self->slots.arr[slot_idx];
    slot->slot_is_empty = true;
    ct_stacktrace_pop(ct_stacktrace);
}

int int_mfunc_Inventory_next_empty_slot_handle_InventoryPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Inventory* self) {
    InventorySlot* slot = NULL;
    int i = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    for (i = 0; i < self->slots.size; i++) {
        slot = &self->slots.arr[i];
        if (slot->slot_is_empty) {
                        ct_stacktrace_pop(ct_stacktrace);
return i;
    }
}
        ct_stacktrace_pop(ct_stacktrace);
return -1;
}

void void_mfunc_Inventory_add_item_InventoryPtr_GamePtr_ItemName_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Inventory* self, Game* game, ItemName item_name, int quantity) {
    int empty_handle = 0;
    int i = 0;
    InventorySlot* empty_slot = NULL;
    InventorySlot* slot = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    for (i = 0; i < self->slots.size; i++) {
        slot = &self->slots.arr[i];
        if (slot->slot_is_empty) {
            continue;
}
        if (slot->shared_item.item->item_name == item_name) {
            slot->shared_item.quantity += quantity;
                        ct_stacktrace_pop(ct_stacktrace);
return;
    }
}
    empty_handle = int_mfunc_Inventory_next_empty_slot_handle_InventoryPtr(ct_stacktrace, 107, 52, self);
    if (empty_handle == -1) {
        printf("%s\n", "Inventory is full. cannot add item.");
}
    else {
        if (empty_handle < 0 || empty_handle > self->slots.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", empty_handle, self->slots.size);
                ct_stacktrace_push(ct_stacktrace, 107, 56);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            empty_slot = &self->slots.arr[empty_handle];
        void_mfunc_SharedItem_set_to_SharedItemPtr_GamePtr_ItemName_int_int(ct_stacktrace, 107, 57, &empty_slot->shared_item, game, item_name, quantity, 0);
        empty_slot->slot_is_empty = false;
    }
    ct_stacktrace_pop(ct_stacktrace);
}

bool bool_mfunc_Inventory_inventory_is_empty_InventoryPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Inventory* self) {
    int i = 0;
    InventorySlot* slot = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    for (i = 0; i < self->slots.size; i++) {
        slot = &self->slots.arr[i];
        if (slot->slot_is_empty) {
            continue;
}
                ct_stacktrace_pop(ct_stacktrace);
return false;
}
        ct_stacktrace_pop(ct_stacktrace);
return true;
}

bool bool_mfunc_Inventory_has_merchant_sellable_items_InventoryPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Inventory* self) {
    int i = 0;
    InventorySlot* slot = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    for (i = 0; i < self->slots.size; i++) {
        slot = &self->slots.arr[i];
        if (slot->slot_is_empty) {
            continue;
}
        if (slot->shared_item.item->item_type == ItemType_Useable) {
                        ct_stacktrace_pop(ct_stacktrace);
return true;
    }
}
        ct_stacktrace_pop(ct_stacktrace);
return false;
}

