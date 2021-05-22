#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "ct_stacktrace.h"
#include "ui_sprite.h"
#include "engine.h"
#include "image.h"
#include "utils.h"
#include "image.h"
#include "ct_array.h"
#include "input_events.h"
#include "shared_sprite.h"
#include "game.h"

void void_mfunc_UISprite_update_UISpritePtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UISprite* self, Game* game) {
    bool is_mouse_over = false;
    SDL_Rect* src = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->shared_srcs == NULL) {
        printf("%s\n", "Sprite.update - shared srcs is NULL.");
        ct_stacktrace_push(ct_stacktrace, 152, 24);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    if (self->shared_srcs->srcs.size == 0) {
        printf("%s\n", "Sprite.update - srcs.size is 0.");
        ct_stacktrace_push(ct_stacktrace, 152, 27);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    if (self->anim_speed == 0) {
        printf("%s\n", "Sprite.update - anim_speed is 0.");
        ct_stacktrace_push(ct_stacktrace, 152, 30);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    self->current_frame_idx = int_mfunc_Game_get_current_frame_GamePtr_int_Uint32_Uint32(ct_stacktrace, 152, 31, game, self->shared_srcs->srcs.size, self->anim_speed, self->spawn_time);
    if (self->current_frame_idx < 0 || self->current_frame_idx > self->shared_srcs->srcs.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->current_frame_idx, self->shared_srcs->srcs.size);
            ct_stacktrace_push(ct_stacktrace, 152, 32);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        src = &self->shared_srcs->srcs.arr[self->current_frame_idx];
    self->render_dst.dst.w = src->w;
    self->render_dst.dst.h = src->h;
    void_mfunc_RenderDst_update_RenderDstPtr_SDL_PointPtr_int(ct_stacktrace, 152, 35, &self->render_dst, &game->engine.camera.dst, game->engine.scale);
    is_mouse_over = bool_rect_contains_point_SDL_RectPtr_SDL_PointPtr(ct_stacktrace, 152, 38, &self->render_dst.dst, &game->engine.mouse_point_scaled);
    void_mfunc_InputEvents_update_InputEventsPtr_GamePtr_bool(ct_stacktrace, 152, 39, &self->input_events, game, is_mouse_over);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_UISprite_draw_UISpritePtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UISprite* self, Game* game) {
    SDL_Rect* src = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->current_frame_idx < 0 || self->current_frame_idx > self->shared_srcs->srcs.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->current_frame_idx, self->shared_srcs->srcs.size);
            ct_stacktrace_push(ct_stacktrace, 203, 42);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        src = &self->shared_srcs->srcs.arr[self->current_frame_idx];
    SDL_RenderCopy(game->engine.renderer, self->shared_srcs->image.texture, src, &self->render_dst.scaled_dst);
    ct_stacktrace_pop(ct_stacktrace);
}

