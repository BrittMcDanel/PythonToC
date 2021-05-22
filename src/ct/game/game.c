#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "ct_stacktrace.h"
#include "game.h"
#include "engine.h"
#include "world.h"
#include "scene_map.h"
#include "ct_array.h"
#include "constants.h"
#include "map.h"
#include "utils.h"
#include "shared_sprite.h"
#include "shared_item.h"
#include "unit_sprite.h"
#include "item.h"
#include "ability.h"
#include "inventory.h"
#include "shared_ability.h"
#include "shared_unit.h"
#include "ui.h"

void void_mfunc_Game_start_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Game* self) {
    long unsigned int tile_size = 0;
    long unsigned int ability_size = 0;
    long unsigned int map_size = 0;
    long unsigned int pathfinder_size = 0;
    long unsigned int unit_size = 0;
    long unsigned int world_size = 0;
    long unsigned int game_size = 0;
    long unsigned int inventory_size = 0;
    long unsigned int ui_size = 0;
    long unsigned int unit_sprite_size = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    game_size = sizeof(Game);
    world_size = sizeof(World);
    pathfinder_size = sizeof(PathFinder);
    map_size = sizeof(Map);
    tile_size = sizeof(Tile);
    unit_size = sizeof(Unit);
    unit_sprite_size = sizeof(UnitSprite);
    ability_size = sizeof(Ability);
    inventory_size = sizeof(Inventory);
    ui_size = sizeof(UI);
    printf("%s %lu\n", "game size:", game_size);
    printf("%s %lu\n", "world size:", world_size);
    printf("%s %lu\n", "pathfinder size:", pathfinder_size);
    printf("%s %lu\n", "map size:", map_size);
    printf("%s %lu\n", "tile size:", tile_size);
    printf("%s %lu\n", "unit size:", unit_size);
    printf("%s %lu\n", "unit sprite size:", unit_sprite_size);
    printf("%s %lu\n", "ability size:", ability_size);
    printf("%s %lu\n", "inventory size:", inventory_size);
    printf("%s %lu\n", "ui size:", ui_size);
    self->tile_size = SDL_Point_create_point_int_int(ct_stacktrace, 73, 59, 20, 20);
    self->max_map_size = SDL_Point_create_point_int_int(ct_stacktrace, 73, 60, 80, 80);
    self->move_grid_tile_size = SDL_Point_create_point_int_int(ct_stacktrace, 73, 61, 2, 2);
    self->move_grid_ratio = (self->tile_size.x / self->move_grid_tile_size.x);
    void_mfunc_PathFinder_check_lookup_table_size_PathFinderPtr_GamePtr(ct_stacktrace, 73, 65, &self->world.path_finder, self);
    void_mfunc_Engine_init_EnginePtr(ct_stacktrace, 73, 66, &self->engine);
    engine_start(&self->engine);
    void_mfunc_SpriteDB_init_SpriteDBPtr_GamePtr(ct_stacktrace, 73, 70, &self->sprite_db, self);
    void_mfunc_ItemDB_init_ItemDBPtr_GamePtr(ct_stacktrace, 73, 71, &self->item_db, self);
    void_mfunc_AbilityDB_init_AbilityDBPtr_GamePtr(ct_stacktrace, 73, 72, &self->ability_db, self);
    void_mfunc_UnitDB_init_UnitDBPtr_GamePtr(ct_stacktrace, 73, 73, &self->unit_db, self);
    void_mfunc_World_init_WorldPtr_GamePtr(ct_stacktrace, 73, 74, &self->world, self);
    ct_stacktrace_pop(ct_stacktrace);
}

int int_mfunc_Game_get_current_frame_GamePtr_int_Uint32_Uint32(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Game* self, int srcs_size, Uint32 anim_speed, Uint32 spawn_time) {
    int alive_time = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (anim_speed == 0) {
        printf("%s\n", "Game.get_current_frame - anim_speed is 0.");
        ct_stacktrace_push(ct_stacktrace, 149, 85);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    if (srcs_size == 0) {
        printf("%s\n", "Game.get_current_frame. srcs size is 0.");
        ct_stacktrace_push(ct_stacktrace, 149, 88);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    alive_time = (self->engine.current_time - spawn_time);
        ct_stacktrace_pop(ct_stacktrace);
return (alive_time / anim_speed) % srcs_size;
}

void void_mfunc_Game_update_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Game* self) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    void_mfunc_World_update_WorldPtr_GamePtr(ct_stacktrace, 195, 77, &self->world, self);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Game_draw_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Game* self) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    void_mfunc_World_draw_WorldPtr_GamePtr(ct_stacktrace, 213, 80, &self->world, self);
    ct_stacktrace_pop(ct_stacktrace);
}

