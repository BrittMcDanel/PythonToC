#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "ct_stacktrace.h"
#include "unit_sprite.h"
#include "engine.h"
#include "utils.h"
#include "constants.h"
#include "image.h"
#include "ct_array.h"
#include "game.h"

void void_mfunc_UnitSprite_set_to_UnitSpritePtr_GamePtr_UnitName(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitSprite* self, Game* game, UnitName unit_name) {
    int unit_name_as_int = 0;
    SDL_Rect idle_down_src2 = {0};
    SDL_Rect idle_down_src1 = {0};
    SDL_Rect overworld_idle_down_src2 = {0};
    SDL_Rect overworld_idle_down_src0 = {0};
    SDL_Rect sit_down_src0 = {0};
    SDL_Rect idle_down_src0 = {0};
    SDL_Rect overworld_idle_down_src1 = {0};
    SDL_Rect idle_down_src3 = {0};
    SDL_Rect cast_down_src0 = {0};

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->anim_state = UnitAnimState_Idle;
    void_clear_Array_SDL_Rect_10Ptr(ct_stacktrace, 22, 89, &self->idle_down);
    void_clear_Array_SDL_Rect_10Ptr(ct_stacktrace, 22, 90, &self->cast_down);
    void_clear_Array_SDL_Rect_3Ptr(ct_stacktrace, 22, 91, &self->sit_down);
    void_clear_Array_SDL_Rect_10Ptr(ct_stacktrace, 22, 92, &self->overworld_idle_down);
    self->render_dst.is_camera_rendered = true;
    self->spawn_time = game->engine.current_time;
    self->idle_anim_speed = 1;
    self->cast_anim_speed = 1;
    self->sit_anim_speed = 1;
    self->overworld_idle_anim_speed = 1;
    if (unit_name == UnitName_RandomTownsPerson0) {
        self->image = Image_mfunc_Engine_get_image_EnginePtr_ImageName(ct_stacktrace, 22, 103, &game->engine, ImageName_Units);
        self->idle_anim_speed = 130;
        self->cast_anim_speed = 240;
        self->sit_anim_speed = 100;
        self->overworld_idle_anim_speed = 130;
        self->hit_box_size = SDL_Point_create_point_int_int(ct_stacktrace, 22, 108, 20, 40);
        idle_down_src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 109, 260, 0, 20, 40);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 110, &self->idle_down, &idle_down_src0);
}
    else if (unit_name == UnitName_Merchant) {
        self->image = Image_mfunc_Engine_get_image_EnginePtr_ImageName(ct_stacktrace, 22, 112, &game->engine, ImageName_Units);
        self->idle_anim_speed = 130;
        self->cast_anim_speed = 240;
        self->sit_anim_speed = 100;
        self->overworld_idle_anim_speed = 130;
        self->hit_box_size = SDL_Point_create_point_int_int(ct_stacktrace, 22, 117, 20, 40);
        idle_down_src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 118, 220, 0, 20, 40);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 119, &self->idle_down, &idle_down_src0);
        cast_down_src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 120, 80, 0, 20, 40);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 121, &self->cast_down, &cast_down_src0);
        sit_down_src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 122, 240, 0, 20, 40);
        void_push_Array_SDL_Rect_3Ptr_SDL_RectPtr(ct_stacktrace, 22, 123, &self->sit_down, &sit_down_src0);
        overworld_idle_down_src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 124, 20, 40, 20, 20);
        overworld_idle_down_src1 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 125, 40, 40, 20, 20);
        overworld_idle_down_src2 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 126, 60, 40, 20, 20);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 127, &self->overworld_idle_down, &overworld_idle_down_src0);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 128, &self->overworld_idle_down, &overworld_idle_down_src1);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 129, &self->overworld_idle_down, &overworld_idle_down_src0);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 130, &self->overworld_idle_down, &overworld_idle_down_src2);
}
    else if (unit_name == UnitName_Explorer) {
        self->image = Image_mfunc_Engine_get_image_EnginePtr_ImageName(ct_stacktrace, 22, 132, &game->engine, ImageName_Units);
        self->idle_anim_speed = 130;
        self->cast_anim_speed = 240;
        self->sit_anim_speed = 100;
        self->overworld_idle_anim_speed = 130;
        self->hit_box_size = SDL_Point_create_point_int_int(ct_stacktrace, 22, 137, 20, 40);
        idle_down_src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 138, 0, 0, 20, 40);
        idle_down_src1 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 139, 40, 0, 20, 40);
        idle_down_src2 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 140, 0, 0, 20, 40);
        idle_down_src3 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 141, 60, 0, 20, 40);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 142, &self->idle_down, &idle_down_src0);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 143, &self->idle_down, &idle_down_src1);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 144, &self->idle_down, &idle_down_src2);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 145, &self->idle_down, &idle_down_src3);
        cast_down_src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 146, 80, 0, 20, 40);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 147, &self->cast_down, &cast_down_src0);
        sit_down_src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 148, 200, 0, 20, 40);
        void_push_Array_SDL_Rect_3Ptr_SDL_RectPtr(ct_stacktrace, 22, 149, &self->sit_down, &sit_down_src0);
        overworld_idle_down_src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 150, 20, 40, 20, 20);
        overworld_idle_down_src1 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 151, 40, 40, 20, 20);
        overworld_idle_down_src2 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 152, 60, 40, 20, 20);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 153, &self->overworld_idle_down, &overworld_idle_down_src0);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 154, &self->overworld_idle_down, &overworld_idle_down_src1);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 155, &self->overworld_idle_down, &overworld_idle_down_src0);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 156, &self->overworld_idle_down, &overworld_idle_down_src2);
}
    else if (unit_name == UnitName_Mage) {
        self->image = Image_mfunc_Engine_get_image_EnginePtr_ImageName(ct_stacktrace, 22, 158, &game->engine, ImageName_Units);
        self->idle_anim_speed = 100;
        self->cast_anim_speed = 240;
        self->sit_anim_speed = 100;
        self->overworld_idle_anim_speed = 130;
        self->hit_box_size = SDL_Point_create_point_int_int(ct_stacktrace, 22, 163, 20, 40);
        idle_down_src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 164, 20, 0, 20, 40);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 165, &self->idle_down, &idle_down_src0);
        cast_down_src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 166, 100, 0, 20, 40);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 167, &self->cast_down, &cast_down_src0);
        sit_down_src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 168, 200, 0, 20, 40);
        void_push_Array_SDL_Rect_3Ptr_SDL_RectPtr(ct_stacktrace, 22, 169, &self->sit_down, &sit_down_src0);
        overworld_idle_down_src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 170, 80, 40, 20, 20);
        overworld_idle_down_src1 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 171, 100, 40, 20, 20);
        overworld_idle_down_src2 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 172, 120, 40, 20, 20);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 173, &self->overworld_idle_down, &overworld_idle_down_src0);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 174, &self->overworld_idle_down, &overworld_idle_down_src1);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 175, &self->overworld_idle_down, &overworld_idle_down_src0);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 176, &self->overworld_idle_down, &overworld_idle_down_src2);
}
    else if (unit_name == UnitName_Wizard) {
        self->image = Image_mfunc_Engine_get_image_EnginePtr_ImageName(ct_stacktrace, 22, 178, &game->engine, ImageName_Units);
        self->idle_anim_speed = 100;
        self->cast_anim_speed = 240;
        self->sit_anim_speed = 100;
        self->overworld_idle_anim_speed = 130;
        self->hit_box_size = SDL_Point_create_point_int_int(ct_stacktrace, 22, 183, 20, 40);
        idle_down_src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 184, 120, 0, 20, 40);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 185, &self->idle_down, &idle_down_src0);
        cast_down_src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 186, 160, 0, 20, 40);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 187, &self->cast_down, &cast_down_src0);
        sit_down_src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 188, 200, 0, 20, 40);
        void_push_Array_SDL_Rect_3Ptr_SDL_RectPtr(ct_stacktrace, 22, 189, &self->sit_down, &sit_down_src0);
        overworld_idle_down_src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 190, 20, 40, 20, 20);
        overworld_idle_down_src1 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 191, 40, 40, 20, 20);
        overworld_idle_down_src2 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 192, 60, 40, 20, 20);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 193, &self->overworld_idle_down, &overworld_idle_down_src0);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 194, &self->overworld_idle_down, &overworld_idle_down_src1);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 195, &self->overworld_idle_down, &overworld_idle_down_src0);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 196, &self->overworld_idle_down, &overworld_idle_down_src2);
}
    else if (unit_name == UnitName_Scholar) {
        self->image = Image_mfunc_Engine_get_image_EnginePtr_ImageName(ct_stacktrace, 22, 198, &game->engine, ImageName_Units);
        self->idle_anim_speed = 100;
        self->cast_anim_speed = 240;
        self->sit_anim_speed = 100;
        self->overworld_idle_anim_speed = 130;
        self->hit_box_size = SDL_Point_create_point_int_int(ct_stacktrace, 22, 203, 20, 40);
        idle_down_src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 204, 140, 0, 20, 40);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 205, &self->idle_down, &idle_down_src0);
        cast_down_src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 206, 180, 0, 20, 40);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 207, &self->cast_down, &cast_down_src0);
        sit_down_src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 208, 200, 0, 20, 40);
        void_push_Array_SDL_Rect_3Ptr_SDL_RectPtr(ct_stacktrace, 22, 209, &self->sit_down, &sit_down_src0);
        overworld_idle_down_src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 210, 20, 40, 20, 20);
        overworld_idle_down_src1 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 211, 40, 40, 20, 20);
        overworld_idle_down_src2 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 212, 60, 40, 20, 20);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 213, &self->overworld_idle_down, &overworld_idle_down_src0);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 214, &self->overworld_idle_down, &overworld_idle_down_src1);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 215, &self->overworld_idle_down, &overworld_idle_down_src0);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 216, &self->overworld_idle_down, &overworld_idle_down_src2);
}
    else if (unit_name == UnitName_Slime) {
        self->image = Image_mfunc_Engine_get_image_EnginePtr_ImageName(ct_stacktrace, 22, 218, &game->engine, ImageName_Units);
        self->idle_anim_speed = 100;
        self->cast_anim_speed = 300;
        self->sit_anim_speed = 100;
        self->hit_box_size = SDL_Point_create_point_int_int(ct_stacktrace, 22, 222, 20, 18);
        idle_down_src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 223, 0, 40, 20, 18);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 224, &self->idle_down, &idle_down_src0);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 225, &self->cast_down, &idle_down_src0);
}
    else if (unit_name == UnitName_Bunny) {
        self->image = Image_mfunc_Engine_get_image_EnginePtr_ImageName(ct_stacktrace, 22, 227, &game->engine, ImageName_Units);
        self->idle_anim_speed = 100;
        self->cast_anim_speed = 300;
        self->sit_anim_speed = 100;
        self->hit_box_size = SDL_Point_create_point_int_int(ct_stacktrace, 22, 231, 20, 28);
        idle_down_src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 232, 0, 64, 20, 28);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 233, &self->idle_down, &idle_down_src0);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 234, &self->cast_down, &idle_down_src0);
}
    else if (unit_name == UnitName_Bat) {
        self->image = Image_mfunc_Engine_get_image_EnginePtr_ImageName(ct_stacktrace, 22, 236, &game->engine, ImageName_Units);
        self->idle_anim_speed = 100;
        self->cast_anim_speed = 300;
        self->sit_anim_speed = 100;
        self->hit_box_size = SDL_Point_create_point_int_int(ct_stacktrace, 22, 240, 20, 26);
        idle_down_src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 241, 0, 96, 20, 26);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 242, &self->idle_down, &idle_down_src0);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 243, &self->cast_down, &idle_down_src0);
}
    else if (unit_name == UnitName_Stump) {
        self->image = Image_mfunc_Engine_get_image_EnginePtr_ImageName(ct_stacktrace, 22, 245, &game->engine, ImageName_Units);
        self->idle_anim_speed = 100;
        self->cast_anim_speed = 300;
        self->sit_anim_speed = 100;
        self->hit_box_size = SDL_Point_create_point_int_int(ct_stacktrace, 22, 249, 28, 38);
        idle_down_src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 250, 0, 128, 28, 37);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 251, &self->idle_down, &idle_down_src0);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 252, &self->cast_down, &idle_down_src0);
}
    else if (unit_name == UnitName_Shroomed) {
        self->image = Image_mfunc_Engine_get_image_EnginePtr_ImageName(ct_stacktrace, 22, 254, &game->engine, ImageName_Units);
        self->idle_anim_speed = 100;
        self->cast_anim_speed = 300;
        self->sit_anim_speed = 100;
        self->hit_box_size = SDL_Point_create_point_int_int(ct_stacktrace, 22, 258, 26, 34);
        idle_down_src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 22, 259, 0, 165, 26, 33);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 260, &self->idle_down, &idle_down_src0);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 22, 261, &self->cast_down, &idle_down_src0);
}
    else {
        unit_name_as_int = (int)(unit_name);
        printf("%s %d\n", "UnitSprite.set_to. Unit name not handled. UnitName:", unit_name_as_int);
        ct_stacktrace_push(ct_stacktrace, 22, 265);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_UnitSprite_play_animation_UnitSpritePtr_GamePtr_UnitAnimState(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitSprite* self, Game* game, UnitAnimState anim_state) {
    Uint32 anim_duration = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->anim_state = anim_state;
    if (self->anim_state == UnitAnimState_NA) {
        printf("%s\n", "UnitSprite.play_animation. Animation is NA.");
        ct_stacktrace_push(ct_stacktrace, 113, 53);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    else if (self->anim_state == UnitAnimState_Cast) {
        self->playing_one_shot_anim = true;
        anim_duration = (Uint32)((self->cast_down.size * self->cast_anim_speed));
        self->anim_finish_time = (game->engine.current_time + anim_duration);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_UnitSprite_set_current_src_UnitSpritePtr_GamePtr_bool(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitSprite* self, Game* game, bool on_overworld_map) {
    int alive_time = 0;
    int current_frame = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if ((((self->idle_anim_speed == 0 || self->cast_anim_speed == 0) || self->sit_anim_speed == 0) || self->overworld_idle_anim_speed == 0)) {
        printf("%s\n", "Unitsprite.set_current_src - an anim speed is 0.");
        ct_stacktrace_push(ct_stacktrace, 144, 62);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    alive_time = (game->engine.current_time - self->spawn_time);
    if (self->anim_state == UnitAnimState_NA) {
        printf("%s\n", "UnitSprite.set_current_src - AnimState is NA.");
        ct_stacktrace_push(ct_stacktrace, 144, 66);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    else if (self->anim_state == UnitAnimState_Idle) {
        if (self->idle_down.size == 0) {
            ct_stacktrace_push(ct_stacktrace, 144, 69);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
}
        if (on_overworld_map) {
            current_frame = (alive_time / self->overworld_idle_anim_speed) % self->overworld_idle_down.size;
            if (current_frame < 0 || current_frame > self->overworld_idle_down.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", current_frame, self->overworld_idle_down.size);
                    ct_stacktrace_push(ct_stacktrace, 144, 72);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                self->current_src = self->overworld_idle_down.arr[current_frame];
}
        else {
            current_frame = (alive_time / self->idle_anim_speed) % self->idle_down.size;
            if (current_frame < 0 || current_frame > self->idle_down.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", current_frame, self->idle_down.size);
                    ct_stacktrace_push(ct_stacktrace, 144, 75);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                self->current_src = self->idle_down.arr[current_frame];
    }
}
    else if (self->anim_state == UnitAnimState_Cast) {
        if (self->cast_down.size == 0) {
            ct_stacktrace_push(ct_stacktrace, 144, 78);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
}
        current_frame = (alive_time / self->cast_anim_speed) % self->cast_down.size;
        if (current_frame < 0 || current_frame > self->cast_down.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", current_frame, self->cast_down.size);
                ct_stacktrace_push(ct_stacktrace, 144, 80);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            self->current_src = self->cast_down.arr[current_frame];
}
    else if (self->anim_state == UnitAnimState_Sit) {
        if (self->sit_down.size == 0) {
            ct_stacktrace_push(ct_stacktrace, 144, 83);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
}
        current_frame = (alive_time / self->sit_anim_speed) % self->sit_down.size;
        if (current_frame < 0 || current_frame > self->sit_down.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", current_frame, self->sit_down.size);
                ct_stacktrace_push(ct_stacktrace, 144, 85);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            self->current_src = self->sit_down.arr[current_frame];
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_UnitSprite_update_UnitSpritePtr_GamePtr_bool(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitSprite* self, Game* game, bool on_overworld_map) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if ((self->playing_one_shot_anim && game->engine.current_time > self->anim_finish_time)) {
        self->playing_one_shot_anim = false;
        self->anim_state = UnitAnimState_Idle;
}
    void_mfunc_UnitSprite_set_current_src_UnitSpritePtr_GamePtr_bool(ct_stacktrace, 148, 32, self, game, on_overworld_map);
    self->render_dst.dst.w = self->current_src.w;
    self->render_dst.dst.h = self->current_src.h;
    void_mfunc_RenderDst_update_RenderDstPtr_SDL_PointPtr_int(ct_stacktrace, 148, 35, &self->render_dst, &game->engine.camera.dst, game->engine.scale);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_UnitSprite_draw_UnitSpritePtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitSprite* self, Game* game) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    SDL_RenderCopy(game->engine.renderer, self->image.texture, &self->current_src, &self->render_dst.scaled_dst);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_UnitSprite_draw_idle_at_UnitSpritePtr_GamePtr_SDL_RectPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitSprite* self, Game* game, SDL_Rect* unscaled_dst) {
    SDL_Rect* idle_src_0 = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (0 < 0 || 0 > self->idle_down.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", 0, self->idle_down.size);
            ct_stacktrace_push(ct_stacktrace, 209, 42);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        idle_src_0 = &self->idle_down.arr[0];
    unscaled_dst->w = idle_src_0->w;
    unscaled_dst->h = idle_src_0->h;
    void_set_scaled_rect_SDL_RectPtr_int(ct_stacktrace, 209, 45, unscaled_dst, game->engine.scale);
    SDL_RenderCopy(game->engine.renderer, self->image.texture, idle_src_0, unscaled_dst);
    ct_stacktrace_pop(ct_stacktrace);
}

