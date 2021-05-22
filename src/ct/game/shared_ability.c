#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "ct_stacktrace.h"
#include "shared_ability.h"
#include "engine.h"
#include "image.h"
#include "utils.h"
#include "image.h"
#include "ct_array.h"
#include "constants.h"
#include "ability.h"
#include "game.h"

void void_mfunc_AbilityDB_init_AbilityDBPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, AbilityDB* self, Game* game) {
    AbilityName ability_name = (AbilityName) 0;
    int last_enum_idx = 0;
    int i = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->abilities.size = 200;
    last_enum_idx = 3;
    if (last_enum_idx > (self->abilities.size - 1)) {
        printf("%s\n", "AbilityDB.init - AbilityName's last enum idx is > abilities capacity.");
        ct_stacktrace_push(ct_stacktrace, 13, 19);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    for (i = 1; i < last_enum_idx; i += 1) {
        ability_name = (AbilityName)(i);
        void_mfunc_Ability_set_to_AbilityPtr_GamePtr_AbilityName(ct_stacktrace, 13, 23, &game->temp_ability, game, ability_name);
        if (i < 0 || i > self->abilities.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->abilities.size);
                ct_stacktrace_push(ct_stacktrace, 13, 24);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            self->abilities.arr[i] = game->temp_ability;
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_SharedAbility_set_to_SharedAbilityPtr_GamePtr_AbilityName(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, SharedAbility* self, Game* game, AbilityName ability_name) {
    int ability_name_as_int = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (ability_name == AbilityName_NA) {
        printf("%s\n", "SharedAbility.set_to. Cannot set to AbilityName.NA.");
        ct_stacktrace_push(ct_stacktrace, 26, 57);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    ability_name_as_int = (int)(ability_name);
    if (ability_name_as_int < 0 || ability_name_as_int > game->ability_db.abilities.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", ability_name_as_int, game->ability_db.abilities.size);
            ct_stacktrace_push(ct_stacktrace, 26, 59);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        self->ability = &game->ability_db.abilities.arr[ability_name_as_int];
    self->render_dst.is_camera_rendered = true;
    self->current_frame_idx = 0;
    self->spawn_time = game->engine.current_time;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_SharedAbility_init_SharedAbilityPtr_GamePtr_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, SharedAbility* self, Game* game, int handle) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->handle = handle;
    self->in_use_in_pool = false;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_SharedAbility_update_SharedAbilityPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, SharedAbility* self, Game* game) {
    SDL_Rect* src = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->ability == NULL) {
        printf("%s\n", "Item.update - item is NULL.");
        ct_stacktrace_push(ct_stacktrace, 156, 43);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    self->current_frame_idx = int_mfunc_Game_get_current_frame_GamePtr_int_Uint32_Uint32(ct_stacktrace, 156, 44, game, self->ability->sprite.srcs.size, self->ability->sprite.anim_speed, self->spawn_time);
    if (self->current_frame_idx < 0 || self->current_frame_idx > self->ability->sprite.srcs.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->current_frame_idx, self->ability->sprite.srcs.size);
            ct_stacktrace_push(ct_stacktrace, 156, 45);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        src = &self->ability->sprite.srcs.arr[self->current_frame_idx];
    self->render_dst.dst.w = src->w;
    self->render_dst.dst.h = src->h;
    void_mfunc_RenderDst_update_RenderDstPtr_SDL_PointPtr_int(ct_stacktrace, 156, 48, &self->render_dst, &game->engine.camera.dst, game->engine.scale);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_SharedAbility_draw_SharedAbilityPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, SharedAbility* self, Game* game) {
    SDL_Rect* src = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->current_frame_idx < 0 || self->current_frame_idx > self->ability->sprite.srcs.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->current_frame_idx, self->ability->sprite.srcs.size);
            ct_stacktrace_push(ct_stacktrace, 206, 51);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        src = &self->ability->sprite.srcs.arr[self->current_frame_idx];
    SDL_RenderCopy(game->engine.renderer, self->ability->sprite.image.texture, src, &self->render_dst.scaled_dst);
    ct_stacktrace_pop(ct_stacktrace);
}

