#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "ct_stacktrace.h"
#include "shared_sprite.h"
#include "engine.h"
#include "image.h"
#include "utils.h"
#include "image.h"
#include "ct_array.h"
#include "constants.h"
#include "game.h"

void void_mfunc_SpriteDB_init_SpriteDBPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, SpriteDB* self, Game* game) {
    int i = 0;
    SDL_Rect src0 = {0};
    int icon_dims = 0;
    Image tile_image = {0};
    Image ui_image = {0};
    Image item_image = {0};
    SpriteSrcs* shared_srcs = NULL;
    int guild_capacity = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    tile_image = Image_mfunc_Engine_get_image_EnginePtr_ImageName(ct_stacktrace, 8, 21, &game->engine, ImageName_Tiles);
    ui_image = Image_mfunc_Engine_get_image_EnginePtr_ImageName(ct_stacktrace, 8, 22, &game->engine, ImageName_UI);
    item_image = Image_mfunc_Engine_get_image_EnginePtr_ImageName(ct_stacktrace, 8, 23, &game->engine, ImageName_Items);
    shared_srcs = SpriteSrcsPtr_next_Array_SpriteSrcs_200Ptr(ct_stacktrace, 8, 26, &self->srcs);
    shared_srcs->image = tile_image;
    src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 8, 28, 0, 0, 20, 20);
    void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 8, 29, &shared_srcs->srcs, &src0);
    shared_srcs = SpriteSrcsPtr_next_Array_SpriteSrcs_200Ptr(ct_stacktrace, 8, 31, &self->srcs);
    shared_srcs->image = tile_image;
    src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 8, 33, 0, 20, 40, 40);
    void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 8, 34, &shared_srcs->srcs, &src0);
    src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 8, 35, 40, 20, 40, 40);
    void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 8, 36, &shared_srcs->srcs, &src0);
    shared_srcs = SpriteSrcsPtr_next_Array_SpriteSrcs_200Ptr(ct_stacktrace, 8, 38, &self->srcs);
    shared_srcs->image = tile_image;
    src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 8, 40, 20, 0, 20, 20);
    void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 8, 41, &shared_srcs->srcs, &src0);
    shared_srcs = SpriteSrcsPtr_next_Array_SpriteSrcs_200Ptr(ct_stacktrace, 8, 43, &self->srcs);
    shared_srcs->image = tile_image;
    src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 8, 45, 40, 0, 20, 20);
    void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 8, 46, &shared_srcs->srcs, &src0);
    shared_srcs = SpriteSrcsPtr_next_Array_SpriteSrcs_200Ptr(ct_stacktrace, 8, 49, &self->srcs);
    shared_srcs->image = item_image;
    src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 8, 51, 20, 40, 20, 20);
    void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 8, 52, &shared_srcs->srcs, &src0);
    shared_srcs = SpriteSrcsPtr_next_Array_SpriteSrcs_200Ptr(ct_stacktrace, 8, 54, &self->srcs);
    shared_srcs->image = item_image;
    src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 8, 56, 0, 60, 16, 16);
    void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 8, 57, &shared_srcs->srcs, &src0);
    guild_capacity = 100;
    icon_dims = 16;
    for (i = 0; i < guild_capacity; i += 1) {
        shared_srcs = SpriteSrcsPtr_next_Array_SpriteSrcs_200Ptr(ct_stacktrace, 8, 62, &self->srcs);
        shared_srcs->image = item_image;
        src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 8, 64, (i * icon_dims), 60, icon_dims, icon_dims);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 8, 65, &shared_srcs->srcs, &src0);
}
    shared_srcs = SpriteSrcsPtr_next_Array_SpriteSrcs_200Ptr(ct_stacktrace, 8, 68, &self->srcs);
    shared_srcs->image = ui_image;
    src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 8, 70, 0, 0, 60, 30);
    void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 8, 71, &shared_srcs->srcs, &src0);
    shared_srcs = SpriteSrcsPtr_next_Array_SpriteSrcs_200Ptr(ct_stacktrace, 8, 73, &self->srcs);
    shared_srcs->image = ui_image;
    src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 8, 75, 0, 32, 180, 165);
    void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 8, 76, &shared_srcs->srcs, &src0);
    shared_srcs = SpriteSrcsPtr_next_Array_SpriteSrcs_200Ptr(ct_stacktrace, 8, 78, &self->srcs);
    shared_srcs->image = ui_image;
    src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 8, 80, 0, 1688, 640, 360);
    void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 8, 81, &shared_srcs->srcs, &src0);
    shared_srcs = SpriteSrcsPtr_next_Array_SpriteSrcs_200Ptr(ct_stacktrace, 8, 83, &self->srcs);
    shared_srcs->image = ui_image;
    src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 8, 85, 640, 1786, 544, 262);
    void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 8, 86, &shared_srcs->srcs, &src0);
    shared_srcs = SpriteSrcsPtr_next_Array_SpriteSrcs_200Ptr(ct_stacktrace, 8, 88, &self->srcs);
    shared_srcs->image = ui_image;
    src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 8, 90, 0, 1664, 10, 10);
    void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 8, 91, &shared_srcs->srcs, &src0);
    shared_srcs = SpriteSrcsPtr_next_Array_SpriteSrcs_200Ptr(ct_stacktrace, 8, 93, &self->srcs);
    shared_srcs->image = ui_image;
    src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 8, 95, 10, 1664, 10, 10);
    void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 8, 96, &shared_srcs->srcs, &src0);
    shared_srcs = SpriteSrcsPtr_next_Array_SpriteSrcs_200Ptr(ct_stacktrace, 8, 98, &self->srcs);
    shared_srcs->image = ui_image;
    src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 8, 100, 0, 240, 80, 40);
    void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 8, 101, &shared_srcs->srcs, &src0);
    shared_srcs = SpriteSrcsPtr_next_Array_SpriteSrcs_200Ptr(ct_stacktrace, 8, 103, &self->srcs);
    shared_srcs->image = ui_image;
    src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 8, 105, 0, 288, 24, 24);
    void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 8, 106, &shared_srcs->srcs, &src0);
    shared_srcs = SpriteSrcsPtr_next_Array_SpriteSrcs_200Ptr(ct_stacktrace, 8, 108, &self->srcs);
    shared_srcs->image = ui_image;
    src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 8, 110, 24, 288, 24, 24);
    void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 8, 111, &shared_srcs->srcs, &src0);
    shared_srcs = SpriteSrcsPtr_next_Array_SpriteSrcs_200Ptr(ct_stacktrace, 8, 113, &self->srcs);
    shared_srcs->image = ui_image;
    src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 8, 115, 48, 288, 24, 24);
    void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 8, 116, &shared_srcs->srcs, &src0);
    shared_srcs = SpriteSrcsPtr_next_Array_SpriteSrcs_200Ptr(ct_stacktrace, 8, 118, &self->srcs);
    shared_srcs->image = ui_image;
    src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 8, 120, 0, 320, 24, 44);
    void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 8, 121, &shared_srcs->srcs, &src0);
    shared_srcs = SpriteSrcsPtr_next_Array_SpriteSrcs_200Ptr(ct_stacktrace, 8, 123, &self->srcs);
    shared_srcs->image = ui_image;
    src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 8, 125, 0, 364, 64, 25);
    void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 8, 126, &shared_srcs->srcs, &src0);
    shared_srcs = SpriteSrcsPtr_next_Array_SpriteSrcs_200Ptr(ct_stacktrace, 8, 128, &self->srcs);
    shared_srcs->image = ui_image;
    src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 8, 130, 0, 389, 24, 24);
    void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 8, 131, &shared_srcs->srcs, &src0);
    shared_srcs = SpriteSrcsPtr_next_Array_SpriteSrcs_200Ptr(ct_stacktrace, 8, 133, &self->srcs);
    shared_srcs->image = ui_image;
    src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 8, 135, 0, 413, 13, 12);
    void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 8, 136, &shared_srcs->srcs, &src0);
    shared_srcs = SpriteSrcsPtr_next_Array_SpriteSrcs_200Ptr(ct_stacktrace, 8, 138, &self->srcs);
    shared_srcs->image = ui_image;
    src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 8, 140, 0, 425, 9, 6);
    void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 8, 141, &shared_srcs->srcs, &src0);
    shared_srcs = SpriteSrcsPtr_next_Array_SpriteSrcs_200Ptr(ct_stacktrace, 8, 143, &self->srcs);
    shared_srcs->image = ui_image;
    src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 8, 145, 0, 431, 80, 80);
    void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 8, 146, &shared_srcs->srcs, &src0);
    shared_srcs = SpriteSrcsPtr_next_Array_SpriteSrcs_200Ptr(ct_stacktrace, 8, 148, &self->srcs);
    shared_srcs->image = ui_image;
    src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 8, 150, 0, 512, 80, 20);
    void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 8, 151, &shared_srcs->srcs, &src0);
    shared_srcs = SpriteSrcsPtr_next_Array_SpriteSrcs_200Ptr(ct_stacktrace, 8, 153, &self->srcs);
    shared_srcs->image = ui_image;
    src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 8, 155, 60, 0, 60, 24);
    void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 8, 156, &shared_srcs->srcs, &src0);
    ct_stacktrace_pop(ct_stacktrace);
}

SpriteSrcs* SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, SpriteDB* self, Game* game, ImageName image_name, SDL_Rect* rect) {
    SpriteSrcs* shared_srcs = NULL;
    SDL_Rect* first_shared_src = NULL;
    int i = 0;
    int image_name_as_int = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    for (i = 0; i < self->srcs.size; i++) {
        shared_srcs = &self->srcs.arr[i];
        if (0 < 0 || 0 > shared_srcs->srcs.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", 0, shared_srcs->srcs.size);
                ct_stacktrace_push(ct_stacktrace, 20, 161);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            first_shared_src = &shared_srcs->srcs.arr[0];
        if ((shared_srcs->image.image_name == image_name && bool_rects_are_equal_SDL_RectPtr_SDL_RectPtr(ct_stacktrace, 20, 162, first_shared_src, rect))) {
                        ct_stacktrace_pop(ct_stacktrace);
return shared_srcs;
    }
}
    image_name_as_int = (int)(image_name);
    printf("%s %d %s %d %d %d %d\n", "SharedSpriteDB.find - rect not found. image_name:", image_name_as_int, "rect:", rect->x, rect->y, rect->w, rect->h);
    ct_stacktrace_push(ct_stacktrace, 20, 167);
    ct_stacktrace_print(ct_stacktrace);
    exit(1);
    if (0 < 0 || 0 > self->srcs.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", 0, self->srcs.size);
            ct_stacktrace_push(ct_stacktrace, 20, 168);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
            ct_stacktrace_pop(ct_stacktrace);
return &self->srcs.arr[0];
}

void void_mfunc_SharedSprite_update_SharedSpritePtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, SharedSprite* self, Game* game) {
    SDL_Rect* src = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->shared_srcs == NULL) {
        printf("%s\n", "Sprite.update - shared srcs is NULL.");
        ct_stacktrace_push(ct_stacktrace, 158, 181);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    if (self->shared_srcs->srcs.size == 0) {
        printf("%s\n", "Sprite.update - srcs.size is 0.");
        ct_stacktrace_push(ct_stacktrace, 158, 184);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    if (self->anim_speed == 0) {
        printf("%s\n", "Sprite.update - anim_speed is 0.");
        ct_stacktrace_push(ct_stacktrace, 158, 187);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    self->current_frame_idx = int_mfunc_Game_get_current_frame_GamePtr_int_Uint32_Uint32(ct_stacktrace, 158, 188, game, self->shared_srcs->srcs.size, self->anim_speed, self->spawn_time);
    if (self->current_frame_idx < 0 || self->current_frame_idx > self->shared_srcs->srcs.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->current_frame_idx, self->shared_srcs->srcs.size);
            ct_stacktrace_push(ct_stacktrace, 158, 189);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        src = &self->shared_srcs->srcs.arr[self->current_frame_idx];
    self->render_dst.dst.w = src->w;
    self->render_dst.dst.h = src->h;
    void_mfunc_RenderDst_update_RenderDstPtr_SDL_PointPtr_int(ct_stacktrace, 158, 192, &self->render_dst, &game->engine.camera.dst, game->engine.scale);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_SharedSprite_draw_SharedSpritePtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, SharedSprite* self, Game* game) {
    SDL_Rect* src = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->current_frame_idx < 0 || self->current_frame_idx > self->shared_srcs->srcs.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->current_frame_idx, self->shared_srcs->srcs.size);
            ct_stacktrace_push(ct_stacktrace, 196, 195);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        src = &self->shared_srcs->srcs.arr[self->current_frame_idx];
    SDL_RenderCopy(game->engine.renderer, self->shared_srcs->image.texture, src, &self->render_dst.scaled_dst);
    ct_stacktrace_pop(ct_stacktrace);
}

