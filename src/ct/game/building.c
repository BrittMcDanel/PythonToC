#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "ct_stacktrace.h"
#include "building.h"
#include "engine.h"
#include "image.h"
#include "utils.h"
#include "image.h"
#include "ct_array.h"
#include "sprite.h"
#include "constants.h"
#include "input_events.h"
#include "game.h"

void void_mfunc_Building_init_BuildingPtr_GamePtr_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Building* self, Game* game, int handle) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->handle = handle;
    self->in_use_in_pool = false;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Building_set_to_BuildingPtr_GamePtr_BuildingName_SDL_PointPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Building* self, Game* game, BuildingName building_name, SDL_Point* move_grid_tile_point) {
    SDL_Rect src = {0};
    int building_name_as_int = 0;
    int i = 0;
    SDL_Point world_point = {0};
    int src_w = 0;
    SDL_Rect src0 = {0};
    SDL_Point move_grid_hit_box_size_dims = {0};
    int src_h = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->tile_point_hit_box.x = move_grid_tile_point->x;
    self->tile_point_hit_box.y = move_grid_tile_point->y;
    world_point = SDL_Point_tile_point_to_world_point_SDL_PointPtr_SDL_PointPtr(ct_stacktrace, 63, 47, move_grid_tile_point, &game->move_grid_tile_size);
    self->sprite.render_dst.dst.x = world_point.x;
    self->sprite.render_dst.dst.y = world_point.y;
    void_clear_Array_SDL_Rect_10Ptr(ct_stacktrace, 63, 51, &self->sprite.srcs);
    self->building_name = building_name;
    self->sprite.spawn_time = game->engine.current_time;
    self->sprite.render_dst.is_camera_rendered = true;
    self->is_shop = false;
    self->building_type = BuildingType_NA;
    self->door_tile_point = *move_grid_tile_point;
    if (building_name == BuildingName_NA) {
        printf("%s\n", "Building.set_to - attempted to call with AbilityName.NA.");
        ct_stacktrace_push(ct_stacktrace, 63, 62);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    else if (building_name == BuildingName_PlayerLeague) {
        self->building_type = BuildingType_League;
        self->sprite.image = Image_mfunc_Engine_get_image_EnginePtr_ImageName(ct_stacktrace, 63, 65, &game->engine, ImageName_Buildings);
        self->sprite.anim_speed = 100;
        src_w = 140;
        src_h = 200;
        move_grid_hit_box_size_dims = SDL_Point_get_move_grid_size_dims_int_int_SDL_PointPtr(ct_stacktrace, 63, 69, src_w, src_h, &game->move_grid_tile_size);
        self->tile_point_hit_box.w = move_grid_hit_box_size_dims.x;
        self->tile_point_hit_box.h = move_grid_hit_box_size_dims.y;
        src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 63, 72, 0, 0, src_w, src_h);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 63, 73, &self->sprite.srcs, &src0);
        self->door_tile_point.x = (move_grid_tile_point->x + 30);
        self->door_tile_point.y = (move_grid_tile_point->y + 80);
}
    else if (building_name == BuildingName_Shop0) {
        self->building_type = BuildingType_PotionShop;
        self->is_shop = true;
        self->sprite.image = Image_mfunc_Engine_get_image_EnginePtr_ImageName(ct_stacktrace, 63, 79, &game->engine, ImageName_Buildings);
        self->sprite.anim_speed = 100;
        src_w = 140;
        src_h = 200;
        move_grid_hit_box_size_dims = SDL_Point_get_move_grid_size_dims_int_int_SDL_PointPtr(ct_stacktrace, 63, 83, src_w, src_h, &game->move_grid_tile_size);
        self->tile_point_hit_box.w = move_grid_hit_box_size_dims.x;
        self->tile_point_hit_box.h = move_grid_hit_box_size_dims.y;
        src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 63, 86, 140, 0, src_w, src_h);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 63, 87, &self->sprite.srcs, &src0);
        self->door_tile_point.x = (move_grid_tile_point->x + 30);
        self->door_tile_point.y = (move_grid_tile_point->y + 80);
}
    else if (building_name == BuildingName_RecruitmentCenter0) {
        self->building_type = BuildingType_RecruitmentShop;
        self->sprite.image = Image_mfunc_Engine_get_image_EnginePtr_ImageName(ct_stacktrace, 63, 92, &game->engine, ImageName_Buildings);
        self->sprite.anim_speed = 100;
        src_w = 140;
        src_h = 200;
        move_grid_hit_box_size_dims = SDL_Point_get_move_grid_size_dims_int_int_SDL_PointPtr(ct_stacktrace, 63, 96, src_w, src_h, &game->move_grid_tile_size);
        self->tile_point_hit_box.w = move_grid_hit_box_size_dims.x;
        self->tile_point_hit_box.h = move_grid_hit_box_size_dims.y;
        src0 = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 63, 99, 280, 0, src_w, src_h);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 63, 100, &self->sprite.srcs, &src0);
        self->door_tile_point.x = (move_grid_tile_point->x + 30);
        self->door_tile_point.y = (move_grid_tile_point->y + 80);
}
    else if (building_name == BuildingName_TeleportationStone) {
        self->sprite.image = Image_mfunc_Engine_get_image_EnginePtr_ImageName(ct_stacktrace, 63, 104, &game->engine, ImageName_Buildings);
        self->sprite.anim_speed = 150;
        src_w = 80;
        src_h = 160;
        move_grid_hit_box_size_dims = SDL_Point_get_move_grid_size_dims_int_int_SDL_PointPtr(ct_stacktrace, 63, 108, src_w, src_h, &game->move_grid_tile_size);
        self->tile_point_hit_box.w = move_grid_hit_box_size_dims.x;
        self->tile_point_hit_box.h = move_grid_hit_box_size_dims.y;
        src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 63, 111, 0, 864, src_w, src_h);
        void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 63, 112, &self->sprite.srcs, &src);
        for (i = 0; i < 6; i += 1) {
            src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 63, 114, (i * src_w), 864, src_w, src_h);
            void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(ct_stacktrace, 63, 115, &self->sprite.srcs, &src);
    }
}
    else {
        building_name_as_int = (int)(building_name);
        printf("%s %d\n", "Building.set_to. Building name not handled. BulidingName:", building_name_as_int);
        ct_stacktrace_push(ct_stacktrace, 63, 119);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Building_on_click_BuildingPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Building* self, Game* game) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->building_name == BuildingName_RecruitmentCenter0) {
        void_mfunc_RecruitNoviceModal_set_visible_RecruitNoviceModalPtr_bool(ct_stacktrace, 163, 42, &game->world.ui.recruit_novice_modal, true);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Building_update_BuildingPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Building* self, Game* game) {
    bool is_mouse_over = false;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    void_mfunc_Sprite_update_SpritePtr_GamePtr(ct_stacktrace, 164, 28, &self->sprite, game);
    if (!(game->world.ui.is_mouse_over_ui)) {
        is_mouse_over = bool_rect_contains_point_SDL_RectPtr_SDL_PointPtr(ct_stacktrace, 164, 32, &self->sprite.render_dst.dst, &game->engine.mouse_point_scaled_with_camera);
        void_mfunc_InputEvents_update_InputEventsPtr_GamePtr_bool(ct_stacktrace, 164, 33, &self->input_events, game, is_mouse_over);
        if (self->input_events.is_click) {
            void_mfunc_Building_on_click_BuildingPtr_GamePtr(ct_stacktrace, 164, 35, self, game);
        }
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Building_draw_BuildingPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Building* self, Game* game) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    void_mfunc_Sprite_draw_SpritePtr_GamePtr(ct_stacktrace, 199, 38, &self->sprite, game);
    ct_stacktrace_pop(ct_stacktrace);
}

