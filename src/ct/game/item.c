#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "ct_stacktrace.h"
#include "item.h"
#include "engine.h"
#include "image.h"
#include "utils.h"
#include "image.h"
#include "ct_array.h"
#include "sprite.h"
#include "constants.h"
#include "game.h"

void void_mfunc_Item_set_to_ItemPtr_GamePtr_ItemName(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Item* self, Game* game, ItemName item_name) {
    int item_name_as_int = 0;
    SDL_Rect src0 = {0};

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    void_clear_Array_SDL_Rect_10Ptr(ct_stacktrace, 10, 25, &self->sprite.srcs);
    self->item_name = item_name;
    self->sprite.spawn_time = game->engine.current_time;
    self->sprite.render_dst.is_camera_rendered = true;
    self->item_type = ItemType_Misc;
    if (item_name == ItemName_NA) {
        printf("%s\n", "Item.set_to - attempted to call with ItemName.NA.");
        ct_stacktrace_push(ct_stacktrace, 10, 34);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    else if (item_name == ItemName_Jelly) {
        self->sprite.image = Image_mfunc_Engine_get_image_EnginePtr_ImageName(ct_stacktrace, 10, 36, &game->engine, ImageName_Items);
        self->sprite.anim_speed = 100;
        src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 10, 38, 20, 0, 20, 20);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 10, 39, &self->sprite.srcs, &src0);
        self->cost = 17;
}
    else if (item_name == ItemName_FurPelt) {
        self->sprite.image = Image_mfunc_Engine_get_image_EnginePtr_ImageName(ct_stacktrace, 10, 42, &game->engine, ImageName_Items);
        self->sprite.anim_speed = 100;
        src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 10, 44, 40, 0, 20, 20);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 10, 45, &self->sprite.srcs, &src0);
        self->cost = 32;
}
    else if (item_name == ItemName_Branch) {
        self->sprite.image = Image_mfunc_Engine_get_image_EnginePtr_ImageName(ct_stacktrace, 10, 48, &game->engine, ImageName_Items);
        self->sprite.anim_speed = 100;
        src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 10, 50, 60, 0, 20, 20);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 10, 51, &self->sprite.srcs, &src0);
        self->cost = 44;
}
    else if (item_name == ItemName_Mushroom) {
        self->sprite.image = Image_mfunc_Engine_get_image_EnginePtr_ImageName(ct_stacktrace, 10, 54, &game->engine, ImageName_Items);
        self->sprite.anim_speed = 100;
        src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 10, 56, 80, 0, 20, 20);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 10, 57, &self->sprite.srcs, &src0);
        self->cost = 38;
}
    else if (item_name == ItemName_BatWing) {
        self->sprite.image = Image_mfunc_Engine_get_image_EnginePtr_ImageName(ct_stacktrace, 10, 60, &game->engine, ImageName_Items);
        self->sprite.anim_speed = 100;
        src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 10, 62, 100, 0, 20, 20);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 10, 63, &self->sprite.srcs, &src0);
        self->cost = 27;
}
    else if (item_name == ItemName_Apple) {
        self->item_type = ItemType_Useable;
        self->sprite.image = Image_mfunc_Engine_get_image_EnginePtr_ImageName(ct_stacktrace, 10, 67, &game->engine, ImageName_Items);
        self->sprite.anim_speed = 100;
        src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 10, 69, 120, 0, 20, 20);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 10, 70, &self->sprite.srcs, &src0);
        self->cost = 50;
}
    else {
        item_name_as_int = (int)(item_name);
        printf("%s %d\n", "Item.set_to. Item name not handled. ItemName:", item_name_as_int);
        ct_stacktrace_push(ct_stacktrace, 10, 75);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

