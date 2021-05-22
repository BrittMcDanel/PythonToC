#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "ct_stacktrace.h"
#include "sprite.h"
#include "engine.h"
#include "image.h"
#include "utils.h"
#include "image.h"
#include "ct_array.h"
#include "game.h"

void void_mfunc_Sprite_update_SpritePtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Sprite* self, Game* game) {
    SDL_Rect* src = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->srcs.size == 0) {
        printf("%s\n", "Sprite.get_current_frame - srcs.size is 0.");
        ct_stacktrace_push(ct_stacktrace, 160, 20);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    if (self->anim_speed == 0) {
        printf("%s\n", "Sprite.get_current_frame - anim_speed is 0.");
        ct_stacktrace_push(ct_stacktrace, 160, 23);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    self->current_frame_idx = int_mfunc_Game_get_current_frame_GamePtr_int_Uint32_Uint32(ct_stacktrace, 160, 24, game, self->srcs.size, self->anim_speed, self->spawn_time);
    if (self->current_frame_idx < 0 || self->current_frame_idx > self->srcs.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->current_frame_idx, self->srcs.size);
            ct_stacktrace_push(ct_stacktrace, 160, 25);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        src = &self->srcs.arr[self->current_frame_idx];
    self->render_dst.dst.w = src->w;
    self->render_dst.dst.h = src->h;
    void_mfunc_RenderDst_update_RenderDstPtr_SDL_PointPtr_int(ct_stacktrace, 160, 28, &self->render_dst, &game->engine.camera.dst, game->engine.scale);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Sprite_draw_SpritePtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Sprite* self, Game* game) {
    SDL_Rect* src = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->current_frame_idx < 0 || self->current_frame_idx > self->srcs.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->current_frame_idx, self->srcs.size);
            ct_stacktrace_push(ct_stacktrace, 198, 31);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        src = &self->srcs.arr[self->current_frame_idx];
    SDL_RenderCopy(game->engine.renderer, self->image.texture, src, &self->render_dst.scaled_dst);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Sprite_draw_at_SpritePtr_GamePtr_SDL_RectPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Sprite* self, Game* game, SDL_Rect* unscaled_dst) {
    SDL_Rect* src = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (0 < 0 || 0 > self->srcs.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", 0, self->srcs.size);
            ct_stacktrace_push(ct_stacktrace, 208, 36);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        src = &self->srcs.arr[0];
    unscaled_dst->w = src->w;
    unscaled_dst->h = src->h;
    void_set_scaled_rect_SDL_RectPtr_int(ct_stacktrace, 208, 39, unscaled_dst, game->engine.scale);
    SDL_RenderCopy(game->engine.renderer, self->image.texture, src, unscaled_dst);
    ct_stacktrace_pop(ct_stacktrace);
}

