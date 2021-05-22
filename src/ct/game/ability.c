#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "ct_stacktrace.h"
#include "ability.h"
#include "engine.h"
#include "image.h"
#include "utils.h"
#include "image.h"
#include "ct_array.h"
#include "sprite.h"
#include "constants.h"
#include "game.h"

void void_mfunc_Ability_set_to_AbilityPtr_GamePtr_AbilityName(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Ability* self, Game* game, AbilityName ability_name) {
    int ability_name_as_int = 0;
    SDL_Rect src2 = {0};
    SDL_Rect src1 = {0};
    SDL_Rect src = {0};
    int w = 0;
    int x = 0;
    SDL_Rect portrait_src = {0};
    SDL_Rect src0 = {0};
    int i = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    void_clear_Array_SDL_Rect_10Ptr(ct_stacktrace, 12, 41, &self->sprite.srcs);
    void_clear_Array_SDL_Rect_10Ptr(ct_stacktrace, 12, 42, &self->portrait.srcs);
    self->ability_name = ability_name;
    self->sprite.spawn_time = game->engine.current_time;
    self->sprite.render_dst.is_camera_rendered = true;
    self->sprite.image = Image_mfunc_Engine_get_image_EnginePtr_ImageName(ct_stacktrace, 12, 47, &game->engine, ImageName_Abilities);
    self->portrait.image = Image_mfunc_Engine_get_image_EnginePtr_ImageName(ct_stacktrace, 12, 48, &game->engine, ImageName_Items);
    if (ability_name == AbilityName_NA) {
        printf("%s\n", "Ability.set_to - attempted to call with AbilityName.NA.");
        ct_stacktrace_push(ct_stacktrace, 12, 52);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    else if (ability_name == AbilityName_MeleeAttack) {
        self->sprite.anim_speed = 60;
        self->is_projectile = false;
        self->stats.damage = 20;
        self->stats.range = 30;
        self->stats.max_skill_points = 10;
        portrait_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 12, 59, 20, 20, 20, 20);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 12, 60, &self->portrait.srcs, &portrait_src);
        x = 0;
        w = 30;
        for (i = 0; i < 8; i += 1) {
            src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 12, 64, x, 32, w, 30);
            void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 12, 65, &self->sprite.srcs, &src);
            x += w;
    }
}
    else if (ability_name == AbilityName_Fire) {
        self->sprite.anim_speed = 100;
        self->is_projectile = true;
        self->projectile_speed = 2.0;
        self->start_offset = SDL_Point_create_point_int_int(ct_stacktrace, 12, 71, 0, -30);
        self->delay = 500;
        self->stats.damage = 20;
        self->stats.range = 100;
        self->stats.max_skill_points = 10;
        portrait_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 12, 76, 0, 20, 20, 20);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 12, 77, &self->portrait.srcs, &portrait_src);
        src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 12, 78, 64, 0, 16, 21);
        src1 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 12, 79, 80, 0, 16, 21);
        src2 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 12, 80, 96, 0, 16, 21);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 12, 81, &self->sprite.srcs, &src0);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 12, 82, &self->sprite.srcs, &src1);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 12, 83, &self->sprite.srcs, &src2);
}
    else {
        ability_name_as_int = (int)(ability_name);
        printf("%s %d\n", "Ability.set_to. Ability name not handled. AbilityName:", ability_name_as_int);
        ct_stacktrace_push(ct_stacktrace, 12, 87);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

