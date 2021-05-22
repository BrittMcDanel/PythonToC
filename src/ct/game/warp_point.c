#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "ct_stacktrace.h"
#include "warp_point.h"
#include "engine.h"
#include "image.h"
#include "utils.h"
#include "image.h"
#include "ct_array.h"
#include "constants.h"
#include "shared_sprite.h"
#include "game.h"

void void_mfunc_WarpPoint_set_WarpPointPtr_GamePtr_WarpPointName_SDL_PointPtr_SDL_PointPtr_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, WarpPoint* self, Game* game, WarpPointName warp_point_name, SDL_Point* tile_point, SDL_Point* warp_to_tile_point, int warp_to_map_handle) {
    SDL_Point world_point = {0};
    SDL_Rect src = {0};

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->warp_point_name = warp_point_name;
    self->tile_point = *tile_point;
    self->tile_point_move_grid.x = (self->tile_point.x * game->move_grid_ratio);
    self->tile_point_move_grid.y = (self->tile_point.y * game->move_grid_ratio);
    self->warp_to_tile_point = *warp_to_tile_point;
    self->warp_to_tile_point_move_grid.x = self->warp_to_tile_point.x;
    self->warp_to_tile_point_move_grid.y = self->warp_to_tile_point.y;
    self->warp_to_tile_point_move_grid.x *= game->move_grid_ratio;
    self->warp_to_tile_point_move_grid.y *= game->move_grid_ratio;
    self->warp_to_map_handle = warp_to_map_handle;
    world_point = SDL_Point_tile_point_to_world_point_SDL_PointPtr_SDL_PointPtr(ct_stacktrace, 52, 31, &self->tile_point_move_grid, &game->move_grid_tile_size);
    self->sprite.render_dst.dst.x = world_point.x;
    self->sprite.render_dst.dst.y = world_point.y;
    if (warp_point_name == WarpPointName_Standard) {
        src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 52, 36, 0, 20, 40, 40);
        self->sprite.shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 52, 37, &game->sprite_db, game, ImageName_Tiles, &src);
        self->sprite.anim_speed = 100;
        self->sprite.render_dst.is_camera_rendered = true;
}
    else if (warp_point_name == WarpPointName_Town) {
        src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 52, 41, 20, 0, 20, 20);
        self->sprite.shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 52, 42, &game->sprite_db, game, ImageName_Tiles, &src);
        self->sprite.anim_speed = 100;
        self->sprite.render_dst.is_camera_rendered = true;
}
    else if (warp_point_name == WarpPointName_Forest) {
        src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 52, 46, 40, 0, 20, 20);
        self->sprite.shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 52, 47, &game->sprite_db, game, ImageName_Tiles, &src);
        self->sprite.anim_speed = 100;
        self->sprite.render_dst.is_camera_rendered = true;
    }
    ct_stacktrace_pop(ct_stacktrace);
}

