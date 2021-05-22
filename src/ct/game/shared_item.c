#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "ct_stacktrace.h"
#include "shared_item.h"
#include "engine.h"
#include "image.h"
#include "utils.h"
#include "image.h"
#include "ct_array.h"
#include "constants.h"
#include "item.h"
#include "game.h"

void void_mfunc_ItemDB_init_ItemDBPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, ItemDB* self, Game* game) {
    ItemName item_name = (ItemName) 0;
    int last_enum_idx = 0;
    int i = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->items.size = 200;
    last_enum_idx = 7;
    if (last_enum_idx > (self->items.size - 1)) {
        printf("%s\n", "ItemDB.init - ItemName's last enum idx is > items capacity.");
        ct_stacktrace_push(ct_stacktrace, 11, 19);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    for (i = 1; i < last_enum_idx; i += 1) {
        item_name = (ItemName)(i);
        void_mfunc_Item_set_to_ItemPtr_GamePtr_ItemName(ct_stacktrace, 11, 23, &game->temp_item, game, item_name);
        if (i < 0 || i > self->items.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->items.size);
                ct_stacktrace_push(ct_stacktrace, 11, 24);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            self->items.arr[i] = game->temp_item;
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_SharedItem_set_to_SharedItemPtr_GamePtr_ItemName_int_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, SharedItem* self, Game* game, ItemName item_name, int quantity, int drop_chance) {
    int item_name_as_int = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (item_name == ItemName_NA) {
        printf("%s\n", "SharedItem.set_to. Cannot set to ItemName.NA.");
        ct_stacktrace_push(ct_stacktrace, 28, 58);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    if ((drop_chance < 0 || drop_chance > 100)) {
        printf("%s %d\n", "SharedItem.set_to. Item drop chance must be >= 0 and <= 100 , found drop chance:", drop_chance);
        ct_stacktrace_push(ct_stacktrace, 28, 61);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    item_name_as_int = (int)(item_name);
    if (item_name_as_int < 0 || item_name_as_int > game->item_db.items.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", item_name_as_int, game->item_db.items.size);
            ct_stacktrace_push(ct_stacktrace, 28, 63);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        self->item = &game->item_db.items.arr[item_name_as_int];
    self->quantity = quantity;
    self->drop_chance = drop_chance;
    self->render_dst.is_camera_rendered = true;
    self->current_frame_idx = 0;
    self->spawn_time = game->engine.current_time;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_SharedItem_init_SharedItemPtr_GamePtr_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, SharedItem* self, Game* game, int handle) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->handle = handle;
    self->in_use_in_pool = false;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_SharedItem_update_SharedItemPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, SharedItem* self, Game* game) {
    SDL_Rect* src = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->item == NULL) {
        printf("%s\n", "Item.update - item is NULL.");
        ct_stacktrace_push(ct_stacktrace, 155, 44);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    self->current_frame_idx = int_mfunc_Game_get_current_frame_GamePtr_int_Uint32_Uint32(ct_stacktrace, 155, 45, game, self->item->sprite.srcs.size, self->item->sprite.anim_speed, self->spawn_time);
    if (self->current_frame_idx < 0 || self->current_frame_idx > self->item->sprite.srcs.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->current_frame_idx, self->item->sprite.srcs.size);
            ct_stacktrace_push(ct_stacktrace, 155, 46);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        src = &self->item->sprite.srcs.arr[self->current_frame_idx];
    self->render_dst.dst.w = src->w;
    self->render_dst.dst.h = src->h;
    void_mfunc_RenderDst_update_RenderDstPtr_SDL_PointPtr_int(ct_stacktrace, 155, 49, &self->render_dst, &game->engine.camera.dst, game->engine.scale);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_SharedItem_draw_SharedItemPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, SharedItem* self, Game* game) {
    SDL_Rect* src = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->current_frame_idx < 0 || self->current_frame_idx > self->item->sprite.srcs.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->current_frame_idx, self->item->sprite.srcs.size);
            ct_stacktrace_push(ct_stacktrace, 205, 52);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        src = &self->item->sprite.srcs.arr[self->current_frame_idx];
    SDL_RenderCopy(game->engine.renderer, self->item->sprite.image.texture, src, &self->render_dst.scaled_dst);
    ct_stacktrace_pop(ct_stacktrace);
}

