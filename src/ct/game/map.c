#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "ct_stacktrace.h"
#include "map.h"
#include "audio.h"
#include "engine.h"
#include "image.h"
#include "utils.h"
#include "image.h"
#include "ct_array.h"
#include "sprite.h"
#include "tile.h"
#include "render.h"
#include "constants.h"
#include "text.h"
#include "unit.h"
#include "tween.h"
#include "ability.h"
#include "shared_sprite.h"
#include "warp_point.h"
#include "game.h"

void void_mfunc_Map_init_MapPtr_GamePtr_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Map* self, Game* game, int handle) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->handle = handle;
    self->in_use_in_pool = false;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Map_create_initial_overworld_MapPtr_GamePtr_int_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Map* self, Game* game, int rows, int cols) {
    SDL_Point warp_to_tile_point = {0};
    int i = 0;
    SpriteSrcs* shared_srcs = NULL;
    SDL_Point tile_point = {0};
    Tile tile = {0};
    SDL_Point dst = {0};
    WarpPoint warp_point = {0};
    SDL_Rect src = {0};
    int j = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (rows > game->max_map_size.x) {
        printf("%s %s %d %s %d\n", "Map.create_initial. rows is > game.max_map_size.x", "\nrows:", rows, "\nmax_map_size.x", game->max_map_size.x);
        ct_stacktrace_push(ct_stacktrace, 53, 101);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    if (cols > game->max_map_size.y) {
        printf("%s %s %d %s %d\n", "Map.create_initial. cols is > game.max_map_size.y", "\ncols:", cols, "\nmax_map_size.y", game->max_map_size.y);
        ct_stacktrace_push(ct_stacktrace, 53, 104);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    self->is_town_map = false;
    self->rows = rows;
    self->cols = cols;
    self->move_grid_rows = (rows * game->move_grid_ratio);
    self->move_grid_cols = (cols * game->move_grid_ratio);
    for (i = 0; i < rows; i += 1) {
        for (j = 0; j < cols; j += 1) {
            tile_point = SDL_Point_create_point_int_int(ct_stacktrace, 53, 115, i, j);
            dst = SDL_Point_tile_point_to_world_point_SDL_PointPtr_SDL_PointPtr(ct_stacktrace, 53, 116, &tile_point, &game->tile_size);
            src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 53, 117, 0, 0, 20, 20);
            shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 53, 118, &game->sprite_db, game, ImageName_Tiles, &src);
            tile.sprite.shared_srcs = shared_srcs;
            tile.sprite.render_dst.dst.x = dst.x;
            tile.sprite.render_dst.dst.y = dst.y;
            tile.sprite.anim_speed = 100;
            tile.sprite.render_dst.is_camera_rendered = true;
            void_push_Array_Tile_10000Ptr_TilePtr(ct_stacktrace, 53, 124, &self->tiles, &tile);
    }
}
    tile_point = SDL_Point_create_point_int_int(ct_stacktrace, 53, 127, 10, 15);
    warp_to_tile_point = SDL_Point_create_point_int_int(ct_stacktrace, 53, 128, (rows - 2), 15);
    void_mfunc_WarpPoint_set_WarpPointPtr_GamePtr_WarpPointName_SDL_PointPtr_SDL_PointPtr_int(ct_stacktrace, 53, 129, &warp_point, game, WarpPointName_Forest, &tile_point, &warp_to_tile_point, 1);
    void_push_Array_WarpPoint_7Ptr_WarpPointPtr(ct_stacktrace, 53, 130, &self->warp_points, &warp_point);
    tile_point = SDL_Point_create_point_int_int(ct_stacktrace, 53, 132, 22, 8);
    warp_to_tile_point = SDL_Point_create_point_int_int(ct_stacktrace, 53, 133, 0, 20);
    void_mfunc_WarpPoint_set_WarpPointPtr_GamePtr_WarpPointName_SDL_PointPtr_SDL_PointPtr_int(ct_stacktrace, 53, 134, &warp_point, game, WarpPointName_Town, &tile_point, &warp_to_tile_point, 2);
    void_push_Array_WarpPoint_7Ptr_WarpPointPtr(ct_stacktrace, 53, 135, &self->warp_points, &warp_point);
    tile_point = SDL_Point_create_point_int_int(ct_stacktrace, 53, 137, 32, 18);
    warp_to_tile_point = SDL_Point_create_point_int_int(ct_stacktrace, 53, 138, (rows - 2), 15);
    void_mfunc_WarpPoint_set_WarpPointPtr_GamePtr_WarpPointName_SDL_PointPtr_SDL_PointPtr_int(ct_stacktrace, 53, 139, &warp_point, game, WarpPointName_Forest, &tile_point, &warp_to_tile_point, 3);
    void_push_Array_WarpPoint_7Ptr_WarpPointPtr(ct_stacktrace, 53, 140, &self->warp_points, &warp_point);
    ct_stacktrace_pop(ct_stacktrace);
}

bool bool_mfunc_Map_unit_occupies_tile_point_move_grid_MapPtr_GamePtr_SDL_RectPtr_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Map* self, Game* game, SDL_Rect* tile_point_hit_box, int skip_unit_handle) {
    int unit_handle = 0;
    Unit* unit = NULL;
    int i = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    for (i = 0; i < self->unit_handles.size; i += 1) {
        if (i < 0 || i > self->unit_handles.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->unit_handles.size);
                ct_stacktrace_push(ct_stacktrace, 59, 263);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit_handle = self->unit_handles.arr[i];
        if (unit_handle == skip_unit_handle) {
            continue;
}
        if (unit_handle < 0 || unit_handle > game->world.units.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", unit_handle, game->world.units.size);
                ct_stacktrace_push(ct_stacktrace, 59, 266);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit = &game->world.units.arr[unit_handle];
        if (bool_rect_contains_rect_SDL_RectPtr_SDL_RectPtr(ct_stacktrace, 59, 267, tile_point_hit_box, &unit->tile_point_hit_box)) {
                        ct_stacktrace_pop(ct_stacktrace);
return true;
    }
}
        ct_stacktrace_pop(ct_stacktrace);
return false;
}

SDL_Point SDL_Point_mfunc_Map_get_random_unoccupied_move_grid_tile_point_MapPtr_GamePtr_SDL_RectPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Map* self, Game* game, SDL_Rect* tile_point_hit_box) {
    SDL_Point p = {0};
    int iters = 0;
    SDL_Rect hit_box_cpy = {0};
    int max_iters = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    iters = 0;
    max_iters = 500;
    hit_box_cpy = *tile_point_hit_box;
    p = SDL_Point_create_point_int_int(ct_stacktrace, 60, 247, hit_box_cpy.x, hit_box_cpy.y);
    while (iters < max_iters) {
        iters += 1;
        p.x = int_mfunc_Engine_get_rand_int_EnginePtr_int_int(ct_stacktrace, 60, 250, &game->engine, 0, (self->move_grid_rows - 1));
        p.y = int_mfunc_Engine_get_rand_int_EnginePtr_int_int(ct_stacktrace, 60, 251, &game->engine, 0, (self->move_grid_cols - 1));
        hit_box_cpy.x = p.x;
        hit_box_cpy.y = p.y;
        if (!(bool_mfunc_Map_unit_occupies_tile_point_move_grid_MapPtr_GamePtr_SDL_RectPtr_int(ct_stacktrace, 60, 254, self, game, &hit_box_cpy, -1))) {
                        ct_stacktrace_pop(ct_stacktrace);
return p;
    }
}
    printf("%s\n", "Could not find random unoccupied point.");
        ct_stacktrace_pop(ct_stacktrace);
return SDL_Point_create_point_int_int(ct_stacktrace, 60, 259, 0, 0);
}

void void_mfunc_Map_create_initial_MapPtr_GamePtr_int_int_bool(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Map* self, Game* game, int rows, int cols, bool is_town_map) {
    UnitName rand_unit_name = (UnitName) 0;
    int rand_unit_enum_int = 0;
    int num_enemies = 0;
    SDL_Rect src = {0};
    WarpPoint warp_point = {0};
    int unit_handle = 0;
    SDL_Point dst = {0};
    int i = 0;
    SDL_Point warp_to_tile_point = {0};
    Tile tile = {0};
    SDL_Point tile_point = {0};
    int j = 0;
    Unit* unit = NULL;
    SpriteSrcs* shared_srcs = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (rows > game->max_map_size.x) {
        printf("%s %s %d %s %d\n", "Map.create_initial. rows is > game.max_map_size.x", "\nrows:", rows, "\nmax_map_size.x", game->max_map_size.x);
        ct_stacktrace_push(ct_stacktrace, 62, 44);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    if (cols > game->max_map_size.y) {
        printf("%s %s %d %s %d\n", "Map.create_initial. cols is > game.max_map_size.y", "\ncols:", cols, "\nmax_map_size.y", game->max_map_size.y);
        ct_stacktrace_push(ct_stacktrace, 62, 47);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    self->is_town_map = is_town_map;
    self->rows = rows;
    self->cols = cols;
    self->move_grid_rows = (rows * game->move_grid_ratio);
    self->move_grid_cols = (cols * game->move_grid_ratio);
    for (i = 0; i < rows; i += 1) {
        for (j = 0; j < cols; j += 1) {
            tile_point = SDL_Point_create_point_int_int(ct_stacktrace, 62, 58, i, j);
            dst = SDL_Point_tile_point_to_world_point_SDL_PointPtr_SDL_PointPtr(ct_stacktrace, 62, 59, &tile_point, &game->tile_size);
            src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 62, 60, 0, 0, 20, 20);
            shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 62, 61, &game->sprite_db, game, ImageName_Tiles, &src);
            tile.sprite.shared_srcs = shared_srcs;
            tile.sprite.render_dst.dst.x = dst.x;
            tile.sprite.render_dst.dst.y = dst.y;
            tile.sprite.anim_speed = 100;
            tile.sprite.render_dst.is_camera_rendered = true;
            void_push_Array_Tile_10000Ptr_TilePtr(ct_stacktrace, 62, 67, &self->tiles, &tile);
    }
}
    if (self->handle == 1) {
        tile_point = SDL_Point_create_point_int_int(ct_stacktrace, 62, 71, (rows - 2), 15);
        warp_to_tile_point = SDL_Point_create_point_int_int(ct_stacktrace, 62, 72, (10 + 1), 15);
        void_mfunc_WarpPoint_set_WarpPointPtr_GamePtr_WarpPointName_SDL_PointPtr_SDL_PointPtr_int(ct_stacktrace, 62, 73, &warp_point, game, WarpPointName_Standard, &tile_point, &warp_to_tile_point, 0);
        void_push_Array_WarpPoint_7Ptr_WarpPointPtr(ct_stacktrace, 62, 74, &self->warp_points, &warp_point);
}
    else if (self->handle == 2) {
        tile_point = SDL_Point_create_point_int_int(ct_stacktrace, 62, 76, 0, 20);
        warp_to_tile_point = SDL_Point_create_point_int_int(ct_stacktrace, 62, 77, (22 - 1), 8);
        void_mfunc_WarpPoint_set_WarpPointPtr_GamePtr_WarpPointName_SDL_PointPtr_SDL_PointPtr_int(ct_stacktrace, 62, 78, &warp_point, game, WarpPointName_Standard, &tile_point, &warp_to_tile_point, 0);
        void_push_Array_WarpPoint_7Ptr_WarpPointPtr(ct_stacktrace, 62, 79, &self->warp_points, &warp_point);
}
    else if (self->handle == 3) {
        tile_point = SDL_Point_create_point_int_int(ct_stacktrace, 62, 81, (rows - 2), 15);
        warp_to_tile_point = SDL_Point_create_point_int_int(ct_stacktrace, 62, 82, (32 - 1), 18);
        void_mfunc_WarpPoint_set_WarpPointPtr_GamePtr_WarpPointName_SDL_PointPtr_SDL_PointPtr_int(ct_stacktrace, 62, 83, &warp_point, game, WarpPointName_Standard, &tile_point, &warp_to_tile_point, 0);
        void_push_Array_WarpPoint_7Ptr_WarpPointPtr(ct_stacktrace, 62, 84, &self->warp_points, &warp_point);
}
    if (!(self->is_town_map)) {
        num_enemies = int_mfunc_Engine_get_rand_int_EnginePtr_int_int(ct_stacktrace, 62, 88, &game->engine, 20, 40);
        for (i = 0; i < num_enemies; i += 1) {
            unit_handle = int_mfunc_World_get_handle_WorldPtr_HandleType(ct_stacktrace, 62, 90, &game->world, HandleType_Unit);
            if (unit_handle < 0 || unit_handle > game->world.units.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", unit_handle, game->world.units.size);
                    ct_stacktrace_push(ct_stacktrace, 62, 91);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                unit = &game->world.units.arr[unit_handle];
            rand_unit_enum_int = int_mfunc_Engine_get_rand_int_EnginePtr_int_int(ct_stacktrace, 62, 92, &game->engine, 7, 11);
            rand_unit_name = (UnitName)(rand_unit_enum_int);
            void_mfunc_Unit_set_to_UnitPtr_GamePtr_UnitName_Faction(ct_stacktrace, 62, 94, unit, game, rand_unit_name, Faction_Enemy);
            void_mfunc_Unit_join_map_UnitPtr_GamePtr_MapPtr(ct_stacktrace, 62, 95, unit, game, self);
            void_mfunc_Unit_set_random_spawn_point_UnitPtr_GamePtr(ct_stacktrace, 62, 96, unit, game);
        }
    }
    ct_stacktrace_pop(ct_stacktrace);
}

bool bool_mfunc_Map_in_bounds_move_grid_MapPtr_SDL_PointPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Map* self, SDL_Point* p) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
        ct_stacktrace_pop(ct_stacktrace);
return (((p->x >= 0 && p->x <= (self->move_grid_rows - 1)) && p->y >= 0) && p->y <= (self->move_grid_cols - 1));
}

SDL_Point SDL_Point_mfunc_Map_get_random_merchant_shop_point_MapPtr_GamePtr_SDL_RectPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Map* self, Game* game, SDL_Rect* tile_point_hit_box) {
    SDL_Point self_tile_point = {0};
    SDL_Point p = {0};
    int iters = 0;
    int max_iters = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    iters = 0;
    max_iters = 500;
    p = SDL_Point_create_point_int_int(ct_stacktrace, 109, 213, 0, 0);
    self_tile_point = SDL_Point_create_point_int_int(ct_stacktrace, 109, 214, tile_point_hit_box->x, tile_point_hit_box->y);
    while (iters < max_iters) {
        iters += 1;
        p.x = int_mfunc_Engine_get_rand_int_EnginePtr_int_int(ct_stacktrace, 109, 217, &game->engine, 0, (self->move_grid_rows - 1));
        p.y = int_mfunc_Engine_get_rand_int_EnginePtr_int_int(ct_stacktrace, 109, 218, &game->engine, 0, (self->move_grid_cols - 1));
        if (bool_points_are_equal_SDL_PointPtr_SDL_PointPtr(ct_stacktrace, 109, 220, &self_tile_point, &p)) {
            continue;
}
                ct_stacktrace_pop(ct_stacktrace);
return p;
}
    printf("%s\n", "Could not find random unoccupied point.");
        ct_stacktrace_pop(ct_stacktrace);
return SDL_Point_create_point_int_int(ct_stacktrace, 109, 225, 0, 0);
}

SDL_Point SDL_Point_mfunc_Map_get_random_town_point_MapPtr_GamePtr_SDL_RectPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Map* self, Game* game, SDL_Rect* tile_point_hit_box) {
    SDL_Point self_tile_point = {0};
    SDL_Point p = {0};
    int iters = 0;
    int max_iters = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    iters = 0;
    max_iters = 500;
    p = SDL_Point_create_point_int_int(ct_stacktrace, 114, 230, 0, 0);
    self_tile_point = SDL_Point_create_point_int_int(ct_stacktrace, 114, 231, tile_point_hit_box->x, tile_point_hit_box->y);
    while (iters < max_iters) {
        iters += 1;
        p.x = int_mfunc_Engine_get_rand_int_EnginePtr_int_int(ct_stacktrace, 114, 234, &game->engine, 0, (self->move_grid_rows - 1));
        p.y = int_mfunc_Engine_get_rand_int_EnginePtr_int_int(ct_stacktrace, 114, 235, &game->engine, 0, (self->move_grid_cols - 1));
        if (!(bool_points_are_equal_SDL_PointPtr_SDL_PointPtr(ct_stacktrace, 114, 237, &self_tile_point, &p))) {
                        ct_stacktrace_pop(ct_stacktrace);
return p;
    }
}
    printf("%s\n", "Could not find random unoccupied point.");
        ct_stacktrace_pop(ct_stacktrace);
return SDL_Point_create_point_int_int(ct_stacktrace, 114, 241, 0, 0);
}

int int_mfunc_Map_update_MapPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Map* self, Game* game) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
        ct_stacktrace_pop(ct_stacktrace);
return 0;
}

void void_mfunc_Map_update_visible_map_MapPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Map* self, Game* game) {
    Building* building = NULL;
    int building_handle = 0;
    WarpPoint* warp_point = NULL;
    Tile* tile = NULL;
    int i = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    for (i = 0; i < self->tiles.size; i++) {
        tile = &self->tiles.arr[i];
        void_mfunc_Tile_update_TilePtr_GamePtr(ct_stacktrace, 165, 149, tile, game);
}
    for (i = 0; i < self->warp_points.size; i++) {
        warp_point = &self->warp_points.arr[i];
        void_mfunc_SharedSprite_update_SharedSpritePtr_GamePtr(ct_stacktrace, 165, 151, &warp_point->sprite, game);
}
    for (i = 0; i < self->building_handles.size; i += 1) {
        if (i < 0 || i > self->building_handles.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->building_handles.size);
                ct_stacktrace_push(ct_stacktrace, 165, 154);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            building_handle = self->building_handles.arr[i];
        if (building_handle < 0 || building_handle > game->world.buildings.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", building_handle, game->world.buildings.size);
                ct_stacktrace_push(ct_stacktrace, 165, 155);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            building = &game->world.buildings.arr[building_handle];
        void_mfunc_Building_update_BuildingPtr_GamePtr(ct_stacktrace, 165, 156, building, game);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Map_units_insertion_sort_MapPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Map* self, Game* game) {
    int next_idx = 0;
    Unit* unit_key_j = NULL;
    Unit* unit_key = NULL;
    int key_j = 0;
    int j = 0;
    int i = 0;
    int key = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    for (i = 1; i < self->unit_handles.size; i += 1) {
        if (i < 0 || i > self->unit_handles.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->unit_handles.size);
                ct_stacktrace_push(ct_stacktrace, 200, 190);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            key = self->unit_handles.arr[i];
        j = (i - 1);
        if (j < 0 || j > self->unit_handles.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", j, self->unit_handles.size);
                ct_stacktrace_push(ct_stacktrace, 200, 192);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            key_j = self->unit_handles.arr[j];
        if (key < 0 || key > game->world.units.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", key, game->world.units.size);
                ct_stacktrace_push(ct_stacktrace, 200, 193);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit_key = &game->world.units.arr[key];
        if (key_j < 0 || key_j > game->world.units.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", key_j, game->world.units.size);
                ct_stacktrace_push(ct_stacktrace, 200, 194);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit_key_j = &game->world.units.arr[key_j];
        while ((j >= 0 && unit_key_j->tile_point_hit_box.y > unit_key->tile_point_hit_box.y)) {
            next_idx = (j + 1);
            if (next_idx < 0 || next_idx > self->unit_handles.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", next_idx, self->unit_handles.size);
                    ct_stacktrace_push(ct_stacktrace, 200, 200);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                if (j < 0 || j > self->unit_handles.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", j, self->unit_handles.size);
                    ct_stacktrace_push(ct_stacktrace, 200, 200);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                self->unit_handles.arr[next_idx] = self->unit_handles.arr[j];
            j -= 1;
            if (j >= 0) {
                if (j < 0 || j > self->unit_handles.size - 1) {
                        printf("Out of bounds error: idx: %d size: %d.\n", j, self->unit_handles.size);
                        ct_stacktrace_push(ct_stacktrace, 200, 204);
                        ct_stacktrace_print(ct_stacktrace);
                        exit(1);
                    }
                    key_j = self->unit_handles.arr[j];
                if (key_j < 0 || key_j > game->world.units.size - 1) {
                        printf("Out of bounds error: idx: %d size: %d.\n", key_j, game->world.units.size);
                        ct_stacktrace_push(ct_stacktrace, 200, 205);
                        ct_stacktrace_print(ct_stacktrace);
                        exit(1);
                    }
                    unit_key_j = &game->world.units.arr[key_j];
    }
}
        next_idx = (j + 1);
        if (next_idx < 0 || next_idx > self->unit_handles.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", next_idx, self->unit_handles.size);
                ct_stacktrace_push(ct_stacktrace, 200, 208);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            self->unit_handles.arr[next_idx] = key;
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Map_draw_MapPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Map* self, Game* game) {
    TextSM* damage_text = NULL;
    Building* building = NULL;
    int building_handle = 0;
    int unit_handle = 0;
    int i = 0;
    SharedItem* item = NULL;
    WarpPoint* warp_point = NULL;
    Tile* tile = NULL;
    Unit* unit = NULL;
    int item_handle = 0;
    int ability_handle = 0;
    SharedAbility* ability = NULL;
    int damage_text_handle = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    for (i = 0; i < self->tiles.size; i++) {
        tile = &self->tiles.arr[i];
        void_mfunc_Tile_draw_TilePtr_GamePtr(ct_stacktrace, 207, 160, tile, game);
}
    for (i = 0; i < self->warp_points.size; i++) {
        warp_point = &self->warp_points.arr[i];
        void_mfunc_SharedSprite_draw_SharedSpritePtr_GamePtr(ct_stacktrace, 207, 162, &warp_point->sprite, game);
}
    for (i = 0; i < self->building_handles.size; i += 1) {
        if (i < 0 || i > self->building_handles.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->building_handles.size);
                ct_stacktrace_push(ct_stacktrace, 207, 164);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            building_handle = self->building_handles.arr[i];
        if (building_handle < 0 || building_handle > game->world.buildings.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", building_handle, game->world.buildings.size);
                ct_stacktrace_push(ct_stacktrace, 207, 165);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            building = &game->world.buildings.arr[building_handle];
        void_mfunc_Building_draw_BuildingPtr_GamePtr(ct_stacktrace, 207, 166, building, game);
}
    void_mfunc_Map_units_insertion_sort_MapPtr_GamePtr(ct_stacktrace, 207, 168, self, game);
    for (i = 0; i < self->unit_handles.size; i += 1) {
        if (i < 0 || i > self->unit_handles.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->unit_handles.size);
                ct_stacktrace_push(ct_stacktrace, 207, 170);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit_handle = self->unit_handles.arr[i];
        if (unit_handle < 0 || unit_handle > game->world.units.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", unit_handle, game->world.units.size);
                ct_stacktrace_push(ct_stacktrace, 207, 171);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit = &game->world.units.arr[unit_handle];
        if (!(bool_mfunc_Range_value_is_at_min_RangePtr(ct_stacktrace, 207, 173, &unit->stats.hp))) {
            void_mfunc_Unit_draw_UnitPtr_GamePtr(ct_stacktrace, 207, 174, unit, game);
    }
}
    for (i = 0; i < self->item_handles.size; i += 1) {
        if (i < 0 || i > self->item_handles.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->item_handles.size);
                ct_stacktrace_push(ct_stacktrace, 207, 176);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            item_handle = self->item_handles.arr[i];
        if (item_handle < 0 || item_handle > game->world.items.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", item_handle, game->world.items.size);
                ct_stacktrace_push(ct_stacktrace, 207, 177);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            item = &game->world.items.arr[item_handle];
        void_mfunc_SharedItem_draw_SharedItemPtr_GamePtr(ct_stacktrace, 207, 178, item, game);
}
    for (i = 0; i < self->ability_handles.size; i += 1) {
        if (i < 0 || i > self->ability_handles.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->ability_handles.size);
                ct_stacktrace_push(ct_stacktrace, 207, 180);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            ability_handle = self->ability_handles.arr[i];
        if (ability_handle < 0 || ability_handle > game->world.abilities.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", ability_handle, game->world.abilities.size);
                ct_stacktrace_push(ct_stacktrace, 207, 181);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            ability = &game->world.abilities.arr[ability_handle];
        void_mfunc_SharedAbility_draw_SharedAbilityPtr_GamePtr(ct_stacktrace, 207, 182, ability, game);
}
    for (i = 0; i < self->damage_text_handles.size; i += 1) {
        if (i < 0 || i > self->damage_text_handles.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->damage_text_handles.size);
                ct_stacktrace_push(ct_stacktrace, 207, 184);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            damage_text_handle = self->damage_text_handles.arr[i];
        if (damage_text_handle < 0 || damage_text_handle > game->world.damage_texts.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", damage_text_handle, game->world.damage_texts.size);
                ct_stacktrace_push(ct_stacktrace, 207, 185);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            damage_text = &game->world.damage_texts.arr[damage_text_handle];
        void_text_draw_TextSMPtr_GamePtr(ct_stacktrace, 207, 186, damage_text, game);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

