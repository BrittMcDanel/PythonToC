#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "ct_stacktrace.h"
#include "world.h"
#include "ct_array.h"
#include "image.h"
#include "utils.h"
#include "image.h"
#include "unit.h"
#include "map.h"
#include "utils.h"
#include "constants.h"
#include "guild.h"
#include "building.h"
#include "tween.h"
#include "path_finder.h"
#include "ability.h"
#include "shared_ability.h"
#include "shared_item.h"
#include "text.h"
#include "ui.h"
#include "game_data.h"
#include "game.h"

int int_mfunc_World_get_handle_WorldPtr_HandleType(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, World* self, HandleType handle_type) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (handle_type == HandleType_NA) {
        printf("%s\n", "World.get_handle. handle_type is NA.");
        ct_stacktrace_push(ct_stacktrace, 50, 438);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
                ct_stacktrace_pop(ct_stacktrace);
return -1;
}
    else if (handle_type == HandleType_Map) {
                ct_stacktrace_pop(ct_stacktrace);
return int_pool_get_handle_Array_Map_100Ptr_intPtr_charPtr(ct_stacktrace, 50, 441, &self->maps, &self->maps_last_in_use_handle, "Maps");
}
    else if (handle_type == HandleType_Building) {
                ct_stacktrace_pop(ct_stacktrace);
return int_pool_get_handle_Array_Building_2000Ptr_intPtr_charPtr(ct_stacktrace, 50, 443, &self->buildings, &self->buildings_last_in_use_handle, "Buildings");
}
    else if (handle_type == HandleType_Unit) {
                ct_stacktrace_pop(ct_stacktrace);
return int_pool_get_handle_Array_Unit_3000Ptr_intPtr_charPtr(ct_stacktrace, 50, 445, &self->units, &self->units_last_in_use_handle, "Units");
}
    else if (handle_type == HandleType_Guild) {
                ct_stacktrace_pop(ct_stacktrace);
return int_pool_get_handle_Array_Guild_100Ptr_intPtr_charPtr(ct_stacktrace, 50, 447, &self->guilds, &self->guilds_last_in_use_handle, "Guilds");
}
    else if (handle_type == HandleType_Item) {
                ct_stacktrace_pop(ct_stacktrace);
return int_pool_get_handle_Array_SharedItem_5000Ptr_intPtr_charPtr(ct_stacktrace, 50, 449, &self->items, &self->items_last_in_use_handle, "Items");
}
    else if (handle_type == HandleType_Ability) {
                ct_stacktrace_pop(ct_stacktrace);
return int_pool_get_handle_Array_SharedAbility_5000Ptr_intPtr_charPtr(ct_stacktrace, 50, 451, &self->abilities, &self->abilities_last_in_use_handle, "Abilities");
}
    else if (handle_type == HandleType_TweenXY) {
                ct_stacktrace_pop(ct_stacktrace);
return int_pool_get_handle_Array_TweenXY_20000Ptr_intPtr_charPtr(ct_stacktrace, 50, 453, &self->tween_xys, &self->tween_xys_last_in_use_handle, "TweenXYs");
}
    else if (handle_type == HandleType_DamageText) {
                ct_stacktrace_pop(ct_stacktrace);
return int_pool_get_handle_Array_TextSM_5000Ptr_intPtr_charPtr(ct_stacktrace, 50, 455, &self->damage_texts, &self->damage_texts_last_in_use_handle, "DamgeTexts");
}
    printf("%s\n", "World.get_handle. Unexpected point reached.");
    ct_stacktrace_push(ct_stacktrace, 50, 458);
    ct_stacktrace_print(ct_stacktrace);
    exit(1);
        ct_stacktrace_pop(ct_stacktrace);
return 0;
}

void void_mfunc_World_create_initial_maps_WorldPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, World* self, Game* game) {
    int map_handle = 0;
    Map* map = NULL;
    Building* building = NULL;
    int building_handle = 0;
    SDL_Point building_move_grid_tile_point = {0};

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    map_handle = int_mfunc_World_get_handle_WorldPtr_HandleType(ct_stacktrace, 64, 499, self, HandleType_Map);
    if (map_handle < 0 || map_handle > self->maps.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", map_handle, self->maps.size);
            ct_stacktrace_push(ct_stacktrace, 64, 500);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        map = &self->maps.arr[map_handle];
    void_mfunc_Map_create_initial_overworld_MapPtr_GamePtr_int_int(ct_stacktrace, 64, 501, map, game, 80, 80);
    map_handle = int_mfunc_World_get_handle_WorldPtr_HandleType(ct_stacktrace, 64, 503, self, HandleType_Map);
    if (map_handle < 0 || map_handle > self->maps.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", map_handle, self->maps.size);
            ct_stacktrace_push(ct_stacktrace, 64, 504);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        map = &self->maps.arr[map_handle];
    void_mfunc_Map_create_initial_MapPtr_GamePtr_int_int_bool(ct_stacktrace, 64, 505, map, game, 40, 40, false);
    map_handle = int_mfunc_World_get_handle_WorldPtr_HandleType(ct_stacktrace, 64, 507, self, HandleType_Map);
    if (map_handle < 0 || map_handle > self->maps.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", map_handle, self->maps.size);
            ct_stacktrace_push(ct_stacktrace, 64, 508);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        map = &self->maps.arr[map_handle];
    void_mfunc_Map_create_initial_MapPtr_GamePtr_int_int_bool(ct_stacktrace, 64, 509, map, game, 60, 60, true);
    building_handle = int_mfunc_World_get_handle_WorldPtr_HandleType(ct_stacktrace, 64, 511, self, HandleType_Building);
    if (building_handle < 0 || building_handle > self->buildings.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", building_handle, self->buildings.size);
            ct_stacktrace_push(ct_stacktrace, 64, 512);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        building = &self->buildings.arr[building_handle];
    building_move_grid_tile_point = SDL_Point_create_point_int_int(ct_stacktrace, 64, 513, 200, 200);
    void_mfunc_Building_set_to_BuildingPtr_GamePtr_BuildingName_SDL_PointPtr(ct_stacktrace, 64, 514, building, game, BuildingName_TeleportationStone, &building_move_grid_tile_point);
    void_push_value_Array_int_100Ptr_int(ct_stacktrace, 64, 515, &map->building_handles, building_handle);
    building_handle = int_mfunc_World_get_handle_WorldPtr_HandleType(ct_stacktrace, 64, 517, self, HandleType_Building);
    if (building_handle < 0 || building_handle > self->buildings.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", building_handle, self->buildings.size);
            ct_stacktrace_push(ct_stacktrace, 64, 518);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        building = &self->buildings.arr[building_handle];
    building_move_grid_tile_point = SDL_Point_create_point_int_int(ct_stacktrace, 64, 519, 0, 0);
    void_mfunc_Building_set_to_BuildingPtr_GamePtr_BuildingName_SDL_PointPtr(ct_stacktrace, 64, 520, building, game, BuildingName_PlayerLeague, &building_move_grid_tile_point);
    void_push_value_Array_int_100Ptr_int(ct_stacktrace, 64, 521, &map->building_handles, building_handle);
    building_handle = int_mfunc_World_get_handle_WorldPtr_HandleType(ct_stacktrace, 64, 523, self, HandleType_Building);
    if (building_handle < 0 || building_handle > self->buildings.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", building_handle, self->buildings.size);
            ct_stacktrace_push(ct_stacktrace, 64, 524);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        building = &self->buildings.arr[building_handle];
    building_move_grid_tile_point = SDL_Point_create_point_int_int(ct_stacktrace, 64, 525, 70, 0);
    void_mfunc_Building_set_to_BuildingPtr_GamePtr_BuildingName_SDL_PointPtr(ct_stacktrace, 64, 526, building, game, BuildingName_Shop0, &building_move_grid_tile_point);
    void_push_value_Array_int_100Ptr_int(ct_stacktrace, 64, 527, &map->building_handles, building_handle);
    building_handle = int_mfunc_World_get_handle_WorldPtr_HandleType(ct_stacktrace, 64, 529, self, HandleType_Building);
    if (building_handle < 0 || building_handle > self->buildings.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", building_handle, self->buildings.size);
            ct_stacktrace_push(ct_stacktrace, 64, 530);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        building = &self->buildings.arr[building_handle];
    building_move_grid_tile_point = SDL_Point_create_point_int_int(ct_stacktrace, 64, 531, 140, 0);
    void_mfunc_Building_set_to_BuildingPtr_GamePtr_BuildingName_SDL_PointPtr(ct_stacktrace, 64, 532, building, game, BuildingName_RecruitmentCenter0, &building_move_grid_tile_point);
    void_push_value_Array_int_100Ptr_int(ct_stacktrace, 64, 533, &map->building_handles, building_handle);
    map_handle = int_mfunc_World_get_handle_WorldPtr_HandleType(ct_stacktrace, 64, 535, self, HandleType_Map);
    if (map_handle < 0 || map_handle > self->maps.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", map_handle, self->maps.size);
            ct_stacktrace_push(ct_stacktrace, 64, 536);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        map = &self->maps.arr[map_handle];
    void_mfunc_Map_create_initial_MapPtr_GamePtr_int_int_bool(ct_stacktrace, 64, 537, map, game, 40, 40, false);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_World_create_guilds_WorldPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, World* self, Game* game) {
    Guild* guild = NULL;
    int i = 0;
    int guild_handle = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    for (i = 0; i < 8; i += 1) {
        guild_handle = int_mfunc_World_get_handle_WorldPtr_HandleType(ct_stacktrace, 66, 572, self, HandleType_Guild);
        if (guild_handle < 0 || guild_handle > self->guilds.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", guild_handle, self->guilds.size);
                ct_stacktrace_push(ct_stacktrace, 66, 573);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            guild = &self->guilds.arr[guild_handle];
        if (i == 0) {
            void_mfunc_Guild_set_to_GuildPtr_charPtr(ct_stacktrace, 66, 575, guild, "Oceanside");
}
        else if (i == 1) {
            void_mfunc_Guild_set_to_GuildPtr_charPtr(ct_stacktrace, 66, 577, guild, "Apparition");
}
        else if (i == 2) {
            void_mfunc_Guild_set_to_GuildPtr_charPtr(ct_stacktrace, 66, 579, guild, "Lions");
}
        else if (i == 3) {
            void_mfunc_Guild_set_to_GuildPtr_charPtr(ct_stacktrace, 66, 581, guild, "Thieves");
}
        else if (i == 4) {
            void_mfunc_Guild_set_to_GuildPtr_charPtr(ct_stacktrace, 66, 583, guild, "Pisces Group");
}
        else if (i == 5) {
            void_mfunc_Guild_set_to_GuildPtr_charPtr(ct_stacktrace, 66, 585, guild, "Telekinetics");
}
        else if (i == 6) {
            void_mfunc_Guild_set_to_GuildPtr_charPtr(ct_stacktrace, 66, 587, guild, "Iron Sands");
}
        else if (i == 7) {
            void_mfunc_Guild_set_to_GuildPtr_charPtr(ct_stacktrace, 66, 589, guild, "Psychic Allegiance");
    }
}
    for (i = 0; i < 10; i += 1) {
        guild_handle = int_mfunc_World_get_handle_WorldPtr_HandleType(ct_stacktrace, 66, 592, self, HandleType_Guild);
        if (guild_handle < 0 || guild_handle > self->guilds.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", guild_handle, self->guilds.size);
                ct_stacktrace_push(ct_stacktrace, 66, 593);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            guild = &self->guilds.arr[guild_handle];
        guild->is_anonymous = true;
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_World_create_initial_units_WorldPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, World* self, Game* game) {
    Unit* unit = NULL;
    int unit_handle = 0;
    int i = 0;
    Guild* guild = NULL;
    Faction faction = (Faction) 0;
    Map* map = NULL;
    int rand_map_handle = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    for (i = 0; i < self->guilds.size; i += 1) {
        if (i < 0 || i > self->guilds.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->guilds.size);
                ct_stacktrace_push(ct_stacktrace, 71, 541);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            guild = &self->guilds.arr[i];
        if (!(guild->in_use_in_pool)) {
            continue;
}
        faction = Faction_Ally;
        if (i != 0) {
            faction = Faction_Guild;
}
        rand_map_handle = int_mfunc_Engine_get_rand_int_EnginePtr_int_int(ct_stacktrace, 71, 548, &game->engine, 0, 1);
        if (rand_map_handle == 0) {
            if (1 < 0 || 1 > self->maps.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", 1, self->maps.size);
                    ct_stacktrace_push(ct_stacktrace, 71, 550);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                map = &self->maps.arr[1];
}
        else if (rand_map_handle == 1) {
            if (3 < 0 || 3 > self->maps.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", 3, self->maps.size);
                    ct_stacktrace_push(ct_stacktrace, 71, 552);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                map = &self->maps.arr[3];
}
        unit_handle = int_mfunc_World_get_handle_WorldPtr_HandleType(ct_stacktrace, 71, 553, self, HandleType_Unit);
        if (unit_handle < 0 || unit_handle > self->units.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", unit_handle, self->units.size);
                ct_stacktrace_push(ct_stacktrace, 71, 554);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit = &self->units.arr[unit_handle];
        void_mfunc_Unit_set_to_UnitPtr_GamePtr_UnitName_Faction(ct_stacktrace, 71, 555, unit, game, UnitName_Explorer, faction);
        void_mfunc_Unit_join_guild_UnitPtr_GamePtr_GuildPtr(ct_stacktrace, 71, 556, unit, game, guild);
        void_mfunc_Unit_join_map_UnitPtr_GamePtr_MapPtr(ct_stacktrace, 71, 557, unit, game, map);
        void_mfunc_Unit_set_random_spawn_point_UnitPtr_GamePtr(ct_stacktrace, 71, 558, unit, game);
        if (2 < 0 || 2 > self->maps.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", 2, self->maps.size);
                ct_stacktrace_push(ct_stacktrace, 71, 561);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            map = &self->maps.arr[2];
        unit_handle = int_mfunc_World_get_handle_WorldPtr_HandleType(ct_stacktrace, 71, 562, self, HandleType_Unit);
        if (unit_handle < 0 || unit_handle > self->units.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", unit_handle, self->units.size);
                ct_stacktrace_push(ct_stacktrace, 71, 563);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit = &self->units.arr[unit_handle];
        void_mfunc_Unit_set_to_UnitPtr_GamePtr_UnitName_Faction(ct_stacktrace, 71, 564, unit, game, UnitName_Merchant, faction);
        void_mfunc_Unit_join_guild_UnitPtr_GamePtr_GuildPtr(ct_stacktrace, 71, 565, unit, game, guild);
        void_mfunc_Unit_join_map_UnitPtr_GamePtr_MapPtr(ct_stacktrace, 71, 566, unit, game, map);
        void_mfunc_Unit_set_random_spawn_point_UnitPtr_GamePtr(ct_stacktrace, 71, 567, unit, game);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_World_init_WorldPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, World* self, Game* game) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    void_mfunc_UI_init_UIPtr_GamePtr(ct_stacktrace, 72, 45, &self->ui, game);
    void_pool_init_GamePtr_Array_Map_100Ptr_intPtr(ct_stacktrace, 72, 46, game, &self->maps, &self->maps_last_in_use_handle);
    void_pool_init_GamePtr_Array_Building_2000Ptr_intPtr(ct_stacktrace, 72, 47, game, &self->buildings, &self->buildings_last_in_use_handle);
    void_pool_init_GamePtr_Array_Unit_3000Ptr_intPtr(ct_stacktrace, 72, 48, game, &self->units, &self->units_last_in_use_handle);
    void_pool_init_GamePtr_Array_Guild_100Ptr_intPtr(ct_stacktrace, 72, 49, game, &self->guilds, &self->guilds_last_in_use_handle);
    void_pool_init_GamePtr_Array_SharedItem_5000Ptr_intPtr(ct_stacktrace, 72, 50, game, &self->items, &self->items_last_in_use_handle);
    void_pool_init_GamePtr_Array_SharedAbility_5000Ptr_intPtr(ct_stacktrace, 72, 51, game, &self->abilities, &self->abilities_last_in_use_handle);
    void_pool_of_text_init_GamePtr_Array_TextSM_5000Ptr_intPtr(ct_stacktrace, 72, 52, game, &self->damage_texts, &self->damage_texts_last_in_use_handle);
    void_pool_init_GamePtr_Array_TweenXY_20000Ptr_intPtr(ct_stacktrace, 72, 53, game, &self->tween_xys, &self->tween_xys_last_in_use_handle);
    self->visible_map_handle = 1;
    void_mfunc_World_create_initial_maps_WorldPtr_GamePtr(ct_stacktrace, 72, 61, self, game);
    void_mfunc_World_create_guilds_WorldPtr_GamePtr(ct_stacktrace, 72, 62, self, game);
    void_mfunc_World_create_initial_units_WorldPtr_GamePtr(ct_stacktrace, 72, 63, self, game);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_World_release_handle_WorldPtr_HandleType_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, World* self, HandleType handle_type, int handle) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (handle_type == HandleType_NA) {
        printf("%s\n", "World.release_handle. handle_type is NA.");
        ct_stacktrace_push(ct_stacktrace, 85, 467);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
                ct_stacktrace_pop(ct_stacktrace);
return;
}
    else if (handle_type == HandleType_Map) {
        void_pool_release_handle_Array_Map_100Ptr_int_intPtr(ct_stacktrace, 85, 470, &self->maps, handle, &self->maps_last_in_use_handle);
                ct_stacktrace_pop(ct_stacktrace);
return;
}
    else if (handle_type == HandleType_Building) {
        void_pool_release_handle_Array_Building_2000Ptr_int_intPtr(ct_stacktrace, 85, 473, &self->buildings, handle, &self->buildings_last_in_use_handle);
                ct_stacktrace_pop(ct_stacktrace);
return;
}
    else if (handle_type == HandleType_Unit) {
        void_pool_release_handle_Array_Unit_3000Ptr_int_intPtr(ct_stacktrace, 85, 476, &self->units, handle, &self->units_last_in_use_handle);
                ct_stacktrace_pop(ct_stacktrace);
return;
}
    else if (handle_type == HandleType_Guild) {
        void_pool_release_handle_Array_Guild_100Ptr_int_intPtr(ct_stacktrace, 85, 479, &self->guilds, handle, &self->guilds_last_in_use_handle);
                ct_stacktrace_pop(ct_stacktrace);
return;
}
    else if (handle_type == HandleType_Item) {
        void_pool_release_handle_Array_SharedItem_5000Ptr_int_intPtr(ct_stacktrace, 85, 482, &self->items, handle, &self->items_last_in_use_handle);
                ct_stacktrace_pop(ct_stacktrace);
return;
}
    else if (handle_type == HandleType_Ability) {
        void_pool_release_handle_Array_SharedAbility_5000Ptr_int_intPtr(ct_stacktrace, 85, 485, &self->abilities, handle, &self->abilities_last_in_use_handle);
                ct_stacktrace_pop(ct_stacktrace);
return;
}
    else if (handle_type == HandleType_TweenXY) {
        void_pool_release_handle_Array_TweenXY_20000Ptr_int_intPtr(ct_stacktrace, 85, 488, &self->tween_xys, handle, &self->tween_xys_last_in_use_handle);
                ct_stacktrace_pop(ct_stacktrace);
return;
}
    else if (handle_type == HandleType_DamageText) {
        void_pool_release_handle_Array_TextSM_5000Ptr_int_intPtr(ct_stacktrace, 85, 491, &self->damage_texts, handle, &self->damage_texts_last_in_use_handle);
                ct_stacktrace_pop(ct_stacktrace);
return;
}
    printf("%s\n", "World.release_handle. Unexpected point reached.");
    ct_stacktrace_push(ct_stacktrace, 85, 495);
    ct_stacktrace_print(ct_stacktrace);
    exit(1);
        ct_stacktrace_pop(ct_stacktrace);
return;
}

void void_mfunc_World_remove_all_tweens_WorldPtr_TweenType_HandleType_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, World* self, TweenType tween_type, HandleType handle_type, int handle) {
    TweenXY* tween = NULL;
    int i = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    for (i = 0; i < (self->tween_xys_last_in_use_handle + 1); i += 1) {
        if (i < 0 || i > self->tween_xys.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->tween_xys.size);
                ct_stacktrace_push(ct_stacktrace, 86, 200);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            tween = &self->tween_xys.arr[i];
        if (!(tween->in_use_in_pool)) {
            continue;
}
        if (((tween->callback.tween_type == tween_type && tween->callback.handle_type == handle_type) && tween->callback.handle == handle)) {
            void_mfunc_World_release_handle_WorldPtr_HandleType_int(ct_stacktrace, 86, 207, self, HandleType_TweenXY, i);
        }
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_World_handle_tween_on_start_WorldPtr_GamePtr_TweenCallbackPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, World* self, Game* game, TweenCallback* tween_callback) {
    int unit_handle = 0;
    Unit* unit = NULL;
    Map* map = NULL;
    SDL_Rect unit_tile_point_hit_box_cpy = {0};

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (tween_callback->tween_type == TweenType_NA) {
        printf("%s\n", "World - handle_tween_on_start. tween_type is NA.");
        ct_stacktrace_push(ct_stacktrace, 87, 212);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    else if (tween_callback->tween_higher_level_type == TweenHigherLevelType_Move) {
        if (tween_callback->tween_type == TweenType_UnitMove) {
            unit_handle = tween_callback->handle;
            if (unit_handle < 0 || unit_handle > self->units.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", unit_handle, self->units.size);
                    ct_stacktrace_push(ct_stacktrace, 87, 216);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                unit = &self->units.arr[unit_handle];
            if (unit->map_handle < 0 || unit->map_handle > self->maps.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", unit->map_handle, self->maps.size);
                    ct_stacktrace_push(ct_stacktrace, 87, 217);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                map = &self->maps.arr[unit->map_handle];
            unit_tile_point_hit_box_cpy = unit->tile_point_hit_box;
            unit_tile_point_hit_box_cpy.x = tween_callback->tile_point.x;
            unit_tile_point_hit_box_cpy.y = tween_callback->tile_point.y;
            if (bool_mfunc_Map_unit_occupies_tile_point_move_grid_MapPtr_GamePtr_SDL_RectPtr_int(ct_stacktrace, 87, 223, map, game, &unit_tile_point_hit_box_cpy, unit_handle)) {
                void_mfunc_World_remove_all_tweens_WorldPtr_TweenType_HandleType_int(ct_stacktrace, 87, 224, self, tween_callback->tween_type, tween_callback->handle_type, tween_callback->handle);
}
            else {
                unit->tile_point_hit_box.x = tween_callback->tile_point.x;
                unit->tile_point_hit_box.y = tween_callback->tile_point.y;
    }
}
        else {
            unit_handle = tween_callback->handle;
            if (unit_handle < 0 || unit_handle > self->units.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", unit_handle, self->units.size);
                    ct_stacktrace_push(ct_stacktrace, 87, 231);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                unit = &self->units.arr[unit_handle];
            unit->tile_point_hit_box.x = tween_callback->tile_point.x;
            unit->tile_point_hit_box.y = tween_callback->tile_point.y;
        }
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_World_remove_all_tweens_with_higher_level_type_WorldPtr_TweenHigherLevelType_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, World* self, TweenHigherLevelType tween_higher_level_type, int handle) {
    TweenXY* tween = NULL;
    int i = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    for (i = 0; i < (self->tween_xys_last_in_use_handle + 1); i += 1) {
        if (i < 0 || i > self->tween_xys.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->tween_xys.size);
                ct_stacktrace_push(ct_stacktrace, 93, 190);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            tween = &self->tween_xys.arr[i];
        if (!(tween->in_use_in_pool)) {
            continue;
}
        if ((tween->callback.tween_higher_level_type == tween_higher_level_type && tween->callback.handle == handle)) {
            void_mfunc_World_release_handle_WorldPtr_HandleType_int(ct_stacktrace, 93, 194, self, HandleType_TweenXY, i);
        }
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_World_handle_tween_on_complete_WorldPtr_GamePtr_TweenCallbackPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, World* self, Game* game, TweenCallback* tween_callback) {
    int receiving_unit_handle = 0;
    int item_handle = 0;
    int text_tween_handle = 0;
    SDL_Color text_outline_color = {0};
    SDL_Point damage_text_dst = {0};
    int damage_text_handle = 0;
    TextSM* damage_text = NULL;
    Uint64 job_exp_as_uint64 = 0;
    int job_exp = 0;
    Map* battle_map = NULL;
    SharedAbility* ability = NULL;
    Uint64 exp_as_uint64 = 0;
    SDL_Rect start_rect = {0};
    TweenCallback callback = {0};
    Uint32 delay = 0;
    TweenXY* tween = NULL;
    int tween_handle = 0;
    Unit* receiving_unit = NULL;
    Map* map = NULL;
    Uint32 duration = 0;
    int warping_to_map_handle = 0;
    int warp_point_handle = 0;
    WarpPoint* warp_point = NULL;
    Unit* unit = NULL;
    Map* warping_to_map = NULL;
    SDL_Rect target_rect = {0};
    TweenXY* text_tween = NULL;
    Unit* merchant_unit = NULL;
    int ability_handle = 0;
    int acting_unit_handle = 0;
    SharedItem* item = NULL;
    Unit* acting_unit = NULL;
    int exp = 0;
    bool success = false;
    SDL_Color text_color = {0};

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (tween_callback->tween_type == TweenType_NA) {
        printf("%s\n", "World - handle_tween_on_complete. tween_type is NA.");
        ct_stacktrace_push(ct_stacktrace, 131, 239);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    else if (tween_callback->tween_type == TweenType_UnitMoveToShop) {
        if (tween_callback->is_final_point_in_path) {
            if (tween_callback->handle < 0 || tween_callback->handle > self->units.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", tween_callback->handle, self->units.size);
                    ct_stacktrace_push(ct_stacktrace, 131, 242);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                unit = &self->units.arr[tween_callback->handle];
            unit->inside_building = true;
            tween_handle = int_mfunc_World_get_handle_WorldPtr_HandleType(ct_stacktrace, 131, 245, &game->world, HandleType_TweenXY);
            if (tween_handle < 0 || tween_handle > game->world.tween_xys.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", tween_handle, game->world.tween_xys.size);
                    ct_stacktrace_push(ct_stacktrace, 131, 246);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                tween = &game->world.tween_xys.arr[tween_handle];
            callback.tween_type = TweenType_UnitInShop;
            callback.handle = unit->handle;
            duration = (Uint32)(2000);
            delay = (Uint32)(0);
            void_mfunc_TweenXY_set_TweenXYPtr_GamePtr_SDL_RectPtr_SDL_RectPtr_SDL_RectPtr_bool_double_Uint32_Uint32_TweenCallbackPtr(ct_stacktrace, 131, 251, tween, game, &unit->sprite.render_dst.dst, &unit->sprite.render_dst.dst, &unit->sprite.render_dst.dst, false, 0.0, duration, delay, &callback);
    }
}
    else if (tween_callback->tween_type == TweenType_UnitInShop) {
        if (tween_callback->handle < 0 || tween_callback->handle > self->units.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", tween_callback->handle, self->units.size);
                ct_stacktrace_push(ct_stacktrace, 131, 253);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit = &self->units.arr[tween_callback->handle];
        void_mfunc_Unit_sell_items_UnitPtr_GamePtr(ct_stacktrace, 131, 255, unit, game);
        unit->inside_building = false;
        success = bool_mfunc_Unit_try_find_and_move_to_merchant_shop_UnitPtr_GamePtr(ct_stacktrace, 131, 257, unit, game);
        if (!(success)) {
            unit->ai_state = UnitAIState_Battle;
            void_mfunc_Unit_move_to_overworld_warp_point_UnitPtr_GamePtr(ct_stacktrace, 131, 260, unit, game);
    }
}
    else if (tween_callback->tween_type == TweenType_UnitMoveToTeleporter) {
        if (tween_callback->is_final_point_in_path) {
            if (tween_callback->handle < 0 || tween_callback->handle > self->units.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", tween_callback->handle, self->units.size);
                    ct_stacktrace_push(ct_stacktrace, 131, 263);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                unit = &self->units.arr[tween_callback->handle];
            if (unit->battle_map_handle < 0 || unit->battle_map_handle > self->maps.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", unit->battle_map_handle, self->maps.size);
                    ct_stacktrace_push(ct_stacktrace, 131, 264);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                battle_map = &self->maps.arr[unit->battle_map_handle];
            void_mfunc_Unit_join_map_UnitPtr_GamePtr_MapPtr(ct_stacktrace, 131, 265, unit, game, battle_map);
            void_mfunc_Unit_set_random_spawn_point_UnitPtr_GamePtr(ct_stacktrace, 131, 266, unit, game);
    }
}
    else if (tween_callback->tween_type == TweenType_UnitMoveToGuildBuilding) {
        if (tween_callback->is_final_point_in_path) {
            if (tween_callback->handle < 0 || tween_callback->handle > self->units.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", tween_callback->handle, self->units.size);
                    ct_stacktrace_push(ct_stacktrace, 131, 269);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                unit = &self->units.arr[tween_callback->handle];
            unit->inside_building = true;
            tween_handle = int_mfunc_World_get_handle_WorldPtr_HandleType(ct_stacktrace, 131, 272, &game->world, HandleType_TweenXY);
            if (tween_handle < 0 || tween_handle > game->world.tween_xys.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", tween_handle, game->world.tween_xys.size);
                    ct_stacktrace_push(ct_stacktrace, 131, 273);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                tween = &game->world.tween_xys.arr[tween_handle];
            callback.tween_type = TweenType_UnitInGuildBuilding;
            callback.handle = unit->handle;
            duration = (Uint32)(2000);
            delay = (Uint32)(0);
            void_mfunc_TweenXY_set_TweenXYPtr_GamePtr_SDL_RectPtr_SDL_RectPtr_SDL_RectPtr_bool_double_Uint32_Uint32_TweenCallbackPtr(ct_stacktrace, 131, 278, tween, game, &unit->sprite.render_dst.dst, &unit->sprite.render_dst.dst, &unit->sprite.render_dst.dst, false, 0.0, duration, delay, &callback);
    }
}
    else if (tween_callback->tween_type == TweenType_UnitInGuildBuilding) {
        if (tween_callback->handle < 0 || tween_callback->handle > self->units.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", tween_callback->handle, self->units.size);
                ct_stacktrace_push(ct_stacktrace, 131, 280);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit = &self->units.arr[tween_callback->handle];
        unit->inside_building = false;
        if (bool_mfunc_Unit_is_merchant_UnitPtr(ct_stacktrace, 131, 283, unit)) {
            void_mfunc_Unit_merchant_get_sellable_items_from_guild_UnitPtr_GamePtr(ct_stacktrace, 131, 284, unit, game);
            void_mfunc_Unit_move_to_setup_merchant_shop_UnitPtr_GamePtr(ct_stacktrace, 131, 285, unit, game);
}
        else {
            void_mfunc_Unit_give_items_to_guild_UnitPtr_GamePtr(ct_stacktrace, 131, 287, unit, game);
            void_mfunc_Unit_move_to_shop_UnitPtr_GamePtr(ct_stacktrace, 131, 288, unit, game);
    }
}
    else if (tween_callback->tween_type == TweenType_UnitMoveToSetupMerchantShop) {
        if (tween_callback->is_final_point_in_path) {
            if (tween_callback->handle < 0 || tween_callback->handle > self->units.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", tween_callback->handle, self->units.size);
                    ct_stacktrace_push(ct_stacktrace, 131, 291);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                unit = &self->units.arr[tween_callback->handle];
            unit->ai_state = UnitAIState_MerchantSelling;
            void_mfunc_UnitSprite_play_animation_UnitSpritePtr_GamePtr_UnitAnimState(ct_stacktrace, 131, 293, &unit->sprite, game, UnitAnimState_Sit);
    }
}
    else if (tween_callback->tween_type == TweenType_UnitRandomTownMove) {
        if (tween_callback->is_final_point_in_path) {
            if (tween_callback->handle < 0 || tween_callback->handle > self->units.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", tween_callback->handle, self->units.size);
                    ct_stacktrace_push(ct_stacktrace, 131, 296);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                unit = &self->units.arr[tween_callback->handle];
            void_mfunc_Unit_move_to_random_town_point_UnitPtr_GamePtr(ct_stacktrace, 131, 298, unit, game);
    }
}
    else if (tween_callback->tween_type == TweenType_UnitMoveToWarpPoint) {
        if (tween_callback->is_final_point_in_path) {
            if (tween_callback->handle < 0 || tween_callback->handle > self->units.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", tween_callback->handle, self->units.size);
                    ct_stacktrace_push(ct_stacktrace, 131, 301);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                unit = &self->units.arr[tween_callback->handle];
            if (unit->map_handle < 0 || unit->map_handle > self->maps.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", unit->map_handle, self->maps.size);
                    ct_stacktrace_push(ct_stacktrace, 131, 302);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                map = &self->maps.arr[unit->map_handle];
            warp_point_handle = tween_callback->warp_point_handle;
            if (warp_point_handle < 0 || warp_point_handle > map->warp_points.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", warp_point_handle, map->warp_points.size);
                    ct_stacktrace_push(ct_stacktrace, 131, 304);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                warp_point = &map->warp_points.arr[warp_point_handle];
            warping_to_map_handle = warp_point->warp_to_map_handle;
            if (warping_to_map_handle < 0 || warping_to_map_handle > self->maps.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", warping_to_map_handle, self->maps.size);
                    ct_stacktrace_push(ct_stacktrace, 131, 306);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                warping_to_map = &self->maps.arr[warping_to_map_handle];
            void_mfunc_Unit_join_map_UnitPtr_GamePtr_MapPtr(ct_stacktrace, 131, 307, unit, game, warping_to_map);
            if ((warping_to_map->is_town_map || warping_to_map_handle == 0)) {
                void_mfunc_Unit_set_spawn_point_UnitPtr_GamePtr_SDL_PointPtr(ct_stacktrace, 131, 311, unit, game, &warp_point->warp_to_tile_point_move_grid);
}
            else {
                void_mfunc_Unit_set_random_spawn_point_UnitPtr_GamePtr(ct_stacktrace, 131, 316, unit, game);
}
            if (unit->ai_state == UnitAIState_Selling) {
                if (warping_to_map->handle == 0) {
                    void_mfunc_Unit_move_to_town_warp_point_UnitPtr_GamePtr(ct_stacktrace, 131, 320, unit, game);
}
                else if (warping_to_map->is_town_map) {
                    void_mfunc_Unit_move_to_guild_building_UnitPtr_GamePtr(ct_stacktrace, 131, 322, unit, game);
    }
}
            else if (unit->ai_state == UnitAIState_Battle) {
                if (warping_to_map->handle == 0) {
                    void_mfunc_Unit_move_to_battle_warp_point_UnitPtr_GamePtr(ct_stacktrace, 131, 325, unit, game);
            }
        }
    }
}
    else if (tween_callback->tween_type == TweenType_UnitMoveToBuyAtMerchantShop) {
        if (tween_callback->is_final_point_in_path) {
            if (tween_callback->handle < 0 || tween_callback->handle > self->units.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", tween_callback->handle, self->units.size);
                    ct_stacktrace_push(ct_stacktrace, 131, 328);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                unit = &self->units.arr[tween_callback->handle];
            if (unit->map_handle < 0 || unit->map_handle > self->maps.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", unit->map_handle, self->maps.size);
                    ct_stacktrace_push(ct_stacktrace, 131, 329);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                map = &self->maps.arr[unit->map_handle];
            tween_handle = int_mfunc_World_get_handle_WorldPtr_HandleType(ct_stacktrace, 131, 331, &game->world, HandleType_TweenXY);
            if (tween_handle < 0 || tween_handle > game->world.tween_xys.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", tween_handle, game->world.tween_xys.size);
                    ct_stacktrace_push(ct_stacktrace, 131, 332);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                tween = &game->world.tween_xys.arr[tween_handle];
            callback.tween_type = TweenType_UnitBuyingAtMerchantShop;
            callback.handle = unit->handle;
            callback.merchant_unit_handle = tween_callback->merchant_unit_handle;
            duration = (Uint32)(2000);
            delay = (Uint32)(0);
            void_mfunc_TweenXY_set_TweenXYPtr_GamePtr_SDL_RectPtr_SDL_RectPtr_SDL_RectPtr_bool_double_Uint32_Uint32_TweenCallbackPtr(ct_stacktrace, 131, 338, tween, game, &unit->sprite.render_dst.dst, &unit->sprite.render_dst.dst, &unit->sprite.render_dst.dst, false, 0.0, duration, delay, &callback);
    }
}
    else if (tween_callback->tween_type == TweenType_UnitBuyingAtMerchantShop) {
        if (tween_callback->handle < 0 || tween_callback->handle > self->units.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", tween_callback->handle, self->units.size);
                ct_stacktrace_push(ct_stacktrace, 131, 340);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit = &self->units.arr[tween_callback->handle];
        if (tween_callback->merchant_unit_handle < 0 || tween_callback->merchant_unit_handle > self->units.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", tween_callback->merchant_unit_handle, self->units.size);
                ct_stacktrace_push(ct_stacktrace, 131, 341);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            merchant_unit = &self->units.arr[tween_callback->merchant_unit_handle];
        if (!(bool_mfunc_Unit_is_merchant_UnitPtr(ct_stacktrace, 131, 342, merchant_unit))) {
            printf("%s\n", "TweenType.UnitBuyingAtMerchantShop. Merchant handle unit is not a merchant.");
            ct_stacktrace_push(ct_stacktrace, 131, 344);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
}
        merchant_unit->unit_handle_buying_from_merchant = -1;
        void_mfunc_Unit_merchant_sell_to_unit_UnitPtr_GamePtr(ct_stacktrace, 131, 348, merchant_unit, game);
        unit->ai_state = UnitAIState_Battle;
        void_mfunc_Unit_move_to_overworld_warp_point_UnitPtr_GamePtr(ct_stacktrace, 131, 351, unit, game);
}
    else if (tween_callback->tween_type == TweenType_PerformAbility) {
        if (tween_callback->map_handle < 0 || tween_callback->map_handle > self->maps.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", tween_callback->map_handle, self->maps.size);
                ct_stacktrace_push(ct_stacktrace, 131, 353);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            map = &self->maps.arr[tween_callback->map_handle];
        ability_handle = tween_callback->handle;
        if (ability_handle < 0 || ability_handle > self->abilities.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", ability_handle, self->abilities.size);
                ct_stacktrace_push(ct_stacktrace, 131, 355);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            ability = &self->abilities.arr[ability_handle];
        acting_unit_handle = tween_callback->acting_unit_handle;
        if (acting_unit_handle < 0 || acting_unit_handle > self->units.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", acting_unit_handle, self->units.size);
                ct_stacktrace_push(ct_stacktrace, 131, 357);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            acting_unit = &self->units.arr[acting_unit_handle];
        if (tween_callback->receiving_unit_handle < 0 || tween_callback->receiving_unit_handle > self->units.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", tween_callback->receiving_unit_handle, self->units.size);
                ct_stacktrace_push(ct_stacktrace, 131, 358);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            receiving_unit = &self->units.arr[tween_callback->receiving_unit_handle];
        void_find_and_remove_handle_Array_int_300Ptr_int(ct_stacktrace, 131, 360, &map->ability_handles, ability_handle);
        void_mfunc_World_release_handle_WorldPtr_HandleType_int(ct_stacktrace, 131, 361, self, HandleType_Ability, ability_handle);
        receiving_unit->attacked_by_guild_handle = acting_unit->guild_handle;
        if (!(bool_mfunc_Range_value_is_at_min_RangePtr(ct_stacktrace, 131, 366, &receiving_unit->stats.hp))) {
            void_mfunc_Range_dec_RangePtr_Uint64(ct_stacktrace, 131, 367, &receiving_unit->stats.hp, ability->ability->stats.damage);
            void_mfunc_Unit_on_hit_UnitPtr_GamePtr_int(ct_stacktrace, 131, 368, receiving_unit, game, acting_unit_handle);
            if (bool_mfunc_Range_value_is_at_min_RangePtr(ct_stacktrace, 131, 369, &receiving_unit->stats.hp)) {
                exp = (receiving_unit->stats.experience_drop * receiving_unit->stats.level);
                exp_as_uint64 = (Uint64)(exp);
                void_mfunc_Range_inc_RangePtr_Uint64(ct_stacktrace, 131, 373, &acting_unit->stats.experience, exp_as_uint64);
                if (bool_mfunc_Range_value_is_at_max_RangePtr(ct_stacktrace, 131, 374, &acting_unit->stats.experience)) {
                    if (acting_unit->stats.level < 99) {
                        acting_unit->available_stat_points += int_get_stat_points_for_level_int(ct_stacktrace, 131, 378, acting_unit->stats.level);
                        acting_unit->stats.level += 1;
                        void_mfunc_Range_set_to_min_RangePtr(ct_stacktrace, 131, 380, &acting_unit->stats.experience);
                        acting_unit->stats.experience.max *= 2;
    }
}
                job_exp = (receiving_unit->stats.job_experience_drop * receiving_unit->stats.level);
                job_exp_as_uint64 = (Uint64)(job_exp);
                void_mfunc_Range_inc_RangePtr_Uint64(ct_stacktrace, 131, 386, &acting_unit->stats.job_experience, job_exp_as_uint64);
                if (bool_mfunc_Range_value_is_at_max_RangePtr(ct_stacktrace, 131, 387, &acting_unit->stats.job_experience)) {
                    if (acting_unit->stats.job_level < 10) {
                        acting_unit->available_skill_points += 1;
                        acting_unit->stats.job_level += 1;
                        void_mfunc_Range_set_to_min_RangePtr(ct_stacktrace, 131, 391, &acting_unit->stats.job_experience);
                        acting_unit->stats.job_experience.max *= 2;
    }
}
                void_mfunc_Unit_on_dead_UnitPtr_GamePtr_int(ct_stacktrace, 131, 393, receiving_unit, game, acting_unit_handle);
}
            damage_text_handle = int_mfunc_World_get_handle_WorldPtr_HandleType(ct_stacktrace, 131, 395, self, HandleType_DamageText);
            if (damage_text_handle < 0 || damage_text_handle > self->damage_texts.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", damage_text_handle, self->damage_texts.size);
                    ct_stacktrace_push(ct_stacktrace, 131, 396);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                damage_text = &self->damage_texts.arr[damage_text_handle];
            snprintf(damage_text->str.arr, (size_t) 21, "%lu", ability->ability->stats.damage);
            damage_text->str.size = strlen(damage_text->str.arr);
            damage_text_dst = SDL_Point_create_point_int_int(ct_stacktrace, 131, 398, receiving_unit->sprite.render_dst.dst.x, receiving_unit->sprite.render_dst.dst.y);
            text_color = SDL_Color_create_color_int_int_int_int(ct_stacktrace, 131, 399, 255, 255, 255, 255);
            text_outline_color = SDL_Color_create_color_int_int_int_int(ct_stacktrace, 131, 400, 0, 0, 0, 255);
            void_text_set_without_str_TextSMPtr_GamePtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 131, 401, damage_text, game, &damage_text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 16, &text_color, 1, &text_outline_color, false);
            damage_text->render_dst.is_camera_rendered = true;
            void_push_value_Array_int_300Ptr_int(ct_stacktrace, 131, 403, &map->damage_text_handles, damage_text_handle);
            text_tween_handle = int_mfunc_World_get_handle_WorldPtr_HandleType(ct_stacktrace, 131, 405, self, HandleType_TweenXY);
            if (text_tween_handle < 0 || text_tween_handle > self->tween_xys.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", text_tween_handle, self->tween_xys.size);
                    ct_stacktrace_push(ct_stacktrace, 131, 406);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                text_tween = &self->tween_xys.arr[text_tween_handle];
            start_rect = receiving_unit->sprite.render_dst.dst;
            target_rect = start_rect;
            target_rect.y -= 30;
            duration = (Uint32)(2000);
            delay = (Uint32)(0);
            callback.tween_type = TweenType_DamageText;
            callback.handle = damage_text_handle;
            callback.receiving_unit_handle = tween_callback->receiving_unit_handle;
            callback.map_handle = tween_callback->map_handle;
            void_mfunc_TweenXY_set_TweenXYPtr_GamePtr_SDL_RectPtr_SDL_RectPtr_SDL_RectPtr_bool_double_Uint32_Uint32_TweenCallbackPtr(ct_stacktrace, 131, 416, text_tween, game, &start_rect, &damage_text->render_dst.dst, &target_rect, false, 0.0, duration, delay, &callback);
    }
}
    else if (tween_callback->tween_type == TweenType_ItemDrop) {
        if (tween_callback->map_handle < 0 || tween_callback->map_handle > self->maps.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", tween_callback->map_handle, self->maps.size);
                ct_stacktrace_push(ct_stacktrace, 131, 418);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            map = &self->maps.arr[tween_callback->map_handle];
        item_handle = tween_callback->handle;
        if (item_handle < 0 || item_handle > self->items.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", item_handle, self->items.size);
                ct_stacktrace_push(ct_stacktrace, 131, 420);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            item = &self->items.arr[item_handle];
        receiving_unit_handle = tween_callback->receiving_unit_handle;
        if (receiving_unit_handle < 0 || receiving_unit_handle > self->units.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", receiving_unit_handle, self->units.size);
                ct_stacktrace_push(ct_stacktrace, 131, 422);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            receiving_unit = &self->units.arr[receiving_unit_handle];
        void_mfunc_Inventory_add_item_InventoryPtr_GamePtr_ItemName_int(ct_stacktrace, 131, 423, &receiving_unit->inventory, game, item->item->item_name, item->quantity);
        void_find_and_remove_handle_Array_int_300Ptr_int(ct_stacktrace, 131, 424, &map->item_handles, item_handle);
        void_mfunc_World_release_handle_WorldPtr_HandleType_int(ct_stacktrace, 131, 425, self, HandleType_Item, item_handle);
        if (receiving_unit->ai_state != UnitAIState_Selling) {
            void_mfunc_Unit_change_to_sell_item_ai_state_UnitPtr_GamePtr(ct_stacktrace, 131, 427, receiving_unit, game);
    }
}
    else if (tween_callback->tween_type == TweenType_DamageText) {
        damage_text_handle = tween_callback->handle;
        if (tween_callback->map_handle < 0 || tween_callback->map_handle > self->maps.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", tween_callback->map_handle, self->maps.size);
                ct_stacktrace_push(ct_stacktrace, 131, 431);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            map = &self->maps.arr[tween_callback->map_handle];
        void_find_and_remove_handle_Array_int_300Ptr_int(ct_stacktrace, 131, 432, &map->damage_text_handles, damage_text_handle);
        void_mfunc_World_release_handle_WorldPtr_HandleType_int(ct_stacktrace, 131, 433, self, HandleType_DamageText, damage_text_handle);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_World_update_tween_arr_WorldPtr_GamePtr_Array_TweenXY_20000Ptr_int_HandleType(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, World* self, Game* game, Array_TweenXY_20000* arr, int last_in_use_handle, HandleType tween_handle_type) {
    TweenXY* tween = NULL;
    int i = 0;
    TweenCompletion tween_completed = {0};

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    for (i = 0; i < (last_in_use_handle + 1); i += 1) {
        if (i < 0 || i > arr->size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, arr->size);
                ct_stacktrace_push(ct_stacktrace, 132, 175);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            tween = &arr->arr[i];
        if (!(tween->in_use_in_pool)) {
            continue;
}
        tween_completed = TweenCompletion_mfunc_TweenXY_update_TweenXYPtr_GamePtr(ct_stacktrace, 132, 178, tween, game);
        if (tween_completed.initial_has_started) {
            void_mfunc_World_handle_tween_on_start_WorldPtr_GamePtr_TweenCallbackPtr(ct_stacktrace, 132, 180, self, game, &tween->callback);
}
        if (tween_completed.completed) {
            void_mfunc_World_handle_tween_on_complete_WorldPtr_GamePtr_TweenCallbackPtr(ct_stacktrace, 132, 182, self, game, &tween->callback);
            if (tween->in_use_in_pool) {
                void_mfunc_World_release_handle_WorldPtr_HandleType_int(ct_stacktrace, 132, 186, self, tween_handle_type, i);
            }
        }
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_World_update_WorldPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, World* self, Game* game) {
    Map* visible_map = NULL;
    Map* map = NULL;
    bool z_down = false;
    bool e_down = false;
    bool d_down = false;
    bool s_down = false;
    bool a_down = false;
    bool w_down = false;
    int q_int = 0;
    bool q_down = false;
    int a_int = 0;
    int z_int = 0;
    int unit_handle = 0;
    int d_int = 0;
    Map* overworld = NULL;
    Unit* unit = NULL;
    int e_int = 0;
    SharedItem* item = NULL;
    Guild* player_guild = NULL;
    int camera_move_dist = 0;
    SDL_Point mouse_tile_point = {0};
    SDL_Point mouse_move_grid_tile_point = {0};
    int w_int = 0;
    SharedAbility* ability = NULL;
    int s_int = 0;
    int stat_points = 0;
    Uint64 uint64_1 = 0;
    TextSM* damage_text = NULL;
    int stat_point_cost = 0;
    WarpPoint* warp_point = NULL;
    int i = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    mouse_tile_point = SDL_Point_world_point_to_index_with_camera_SDL_PointPtr_SDL_PointPtr_SDL_PointPtr(ct_stacktrace, 194, 66, &game->engine.mouse_point_scaled, &game->engine.camera.dst, &game->tile_size);
    mouse_move_grid_tile_point = SDL_Point_world_point_to_index_with_camera_SDL_PointPtr_SDL_PointPtr_SDL_PointPtr(ct_stacktrace, 194, 67, &game->engine.mouse_point_scaled, &game->engine.camera.dst, &game->move_grid_tile_size);
    w_int = (int)(SDLK_w);
    a_int = (int)(SDLK_a);
    s_int = (int)(SDLK_s);
    d_int = (int)(SDLK_d);
    q_int = (int)(SDLK_q);
    e_int = (int)(SDLK_e);
    z_int = (int)(SDLK_z);
    if (w_int < 0 || w_int > game->engine.keys_held_down.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", w_int, game->engine.keys_held_down.size);
            ct_stacktrace_push(ct_stacktrace, 194, 75);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        w_down = game->engine.keys_held_down.arr[w_int];
    if (a_int < 0 || a_int > game->engine.keys_held_down.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", a_int, game->engine.keys_held_down.size);
            ct_stacktrace_push(ct_stacktrace, 194, 76);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        a_down = game->engine.keys_held_down.arr[a_int];
    if (s_int < 0 || s_int > game->engine.keys_held_down.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", s_int, game->engine.keys_held_down.size);
            ct_stacktrace_push(ct_stacktrace, 194, 77);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        s_down = game->engine.keys_held_down.arr[s_int];
    if (d_int < 0 || d_int > game->engine.keys_held_down.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", d_int, game->engine.keys_held_down.size);
            ct_stacktrace_push(ct_stacktrace, 194, 78);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        d_down = game->engine.keys_held_down.arr[d_int];
    if (q_int < 0 || q_int > game->engine.keys_down.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", q_int, game->engine.keys_down.size);
            ct_stacktrace_push(ct_stacktrace, 194, 79);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        q_down = game->engine.keys_down.arr[q_int];
    if (e_int < 0 || e_int > game->engine.keys_down.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", e_int, game->engine.keys_down.size);
            ct_stacktrace_push(ct_stacktrace, 194, 80);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        e_down = game->engine.keys_down.arr[e_int];
    if (z_int < 0 || z_int > game->engine.keys_down.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", z_int, game->engine.keys_down.size);
            ct_stacktrace_push(ct_stacktrace, 194, 81);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        z_down = game->engine.keys_down.arr[z_int];
    camera_move_dist = 4;
    if (e_down) {
        if (0 < 0 || 0 > self->guilds.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", 0, self->guilds.size);
                ct_stacktrace_push(ct_stacktrace, 194, 85);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            player_guild = &self->guilds.arr[0];
        if (0 < 0 || 0 > player_guild->unit_handles.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", 0, player_guild->unit_handles.size);
                ct_stacktrace_push(ct_stacktrace, 194, 86);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit_handle = player_guild->unit_handles.arr[0];
        if (unit_handle < 0 || unit_handle > self->units.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", unit_handle, self->units.size);
                ct_stacktrace_push(ct_stacktrace, 194, 87);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit = &self->units.arr[unit_handle];
        if (unit->unit_name == UnitName_Explorer) {
            unit->stats.job_level = 10;
}
        else if (unit->unit_name == UnitName_Mage) {
            unit->stats.job_level = 40;
    }
}
    if (z_down) {
        if (0 < 0 || 0 > self->guilds.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", 0, self->guilds.size);
                ct_stacktrace_push(ct_stacktrace, 194, 93);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            player_guild = &self->guilds.arr[0];
        if (0 < 0 || 0 > player_guild->unit_handles.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", 0, player_guild->unit_handles.size);
                ct_stacktrace_push(ct_stacktrace, 194, 94);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit_handle = player_guild->unit_handles.arr[0];
        if (unit_handle < 0 || unit_handle > self->units.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", unit_handle, self->units.size);
                ct_stacktrace_push(ct_stacktrace, 194, 95);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit = &self->units.arr[unit_handle];
        stat_points = int_get_stat_points_for_level_int(ct_stacktrace, 194, 96, unit->stats.level);
        stat_point_cost = int_get_stat_cost_Uint64(ct_stacktrace, 194, 97, unit->stats.strength.value);
        printf("%d %d %s %u %d\n", unit->stats.level, stat_points, "-", unit->stats.strength.value, stat_point_cost);
        unit->available_stat_points += int_get_stat_points_for_level_int(ct_stacktrace, 194, 99, unit->stats.level);
        unit->stats.level += 1;
        uint64_1 = (Uint64)(1);
        void_mfunc_Range_inc_RangePtr_Uint64(ct_stacktrace, 194, 102, &unit->stats.strength, uint64_1);
}
    if (w_down) {
        game->engine.camera.dst.y -= camera_move_dist;
}
    if (a_down) {
        game->engine.camera.dst.x -= camera_move_dist;
}
    if (s_down) {
        game->engine.camera.dst.y += camera_move_dist;
}
    if (d_down) {
        game->engine.camera.dst.x += camera_move_dist;
}
    if (game->engine.is_mouse_down) {
        self->mouse_down_tile_point = mouse_tile_point;
}
    if (game->engine.is_mouse_up) {
        if (bool_points_are_equal_SDL_PointPtr_SDL_PointPtr(ct_stacktrace, 194, 116, &self->mouse_down_tile_point, &mouse_tile_point)) {
            if (self->visible_map_handle == 0) {
                if (0 < 0 || 0 > self->maps.size - 1) {
                        printf("Out of bounds error: idx: %d size: %d.\n", 0, self->maps.size);
                        ct_stacktrace_push(ct_stacktrace, 194, 119);
                        ct_stacktrace_print(ct_stacktrace);
                        exit(1);
                    }
                    overworld = &self->maps.arr[0];
                for (i = 0; i < overworld->warp_points.size; i++) {
                    warp_point = &overworld->warp_points.arr[i];
                    if (bool_points_are_equal_SDL_PointPtr_SDL_PointPtr(ct_stacktrace, 194, 121, &mouse_tile_point, &warp_point->tile_point)) {
                        self->visible_map_handle = warp_point->warp_to_map_handle;
                        break;
                }
            }
        }
    }
}
    if (game->engine.is_right_mouse_down) {
        if (self->visible_map_handle != 0) {
            self->visible_map_handle = 0;
    }
}
    void_mfunc_UI_clear_UIPtr(ct_stacktrace, 194, 129, &self->ui);
    void_mfunc_World_update_tween_arr_WorldPtr_GamePtr_Array_TweenXY_20000Ptr_int_HandleType(ct_stacktrace, 194, 132, self, game, &self->tween_xys, self->tween_xys_last_in_use_handle, HandleType_TweenXY);
    for (i = 0; i < (self->units_last_in_use_handle + 1); i += 1) {
        if (i < 0 || i > self->units.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->units.size);
                ct_stacktrace_push(ct_stacktrace, 194, 136);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit = &self->units.arr[i];
        if (!(unit->in_use_in_pool)) {
            continue;
}
        void_mfunc_Unit_update_UnitPtr_GamePtr(ct_stacktrace, 194, 139, unit, game);
}
    for (i = 0; i < (self->items_last_in_use_handle + 1); i += 1) {
        if (i < 0 || i > self->items.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->items.size);
                ct_stacktrace_push(ct_stacktrace, 194, 141);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            item = &self->items.arr[i];
        if (!(item->in_use_in_pool)) {
            continue;
}
        void_mfunc_SharedItem_update_SharedItemPtr_GamePtr(ct_stacktrace, 194, 144, item, game);
}
    for (i = 0; i < (self->abilities_last_in_use_handle + 1); i += 1) {
        if (i < 0 || i > self->abilities.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->abilities.size);
                ct_stacktrace_push(ct_stacktrace, 194, 146);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            ability = &self->abilities.arr[i];
        if (!(ability->in_use_in_pool)) {
            continue;
}
        void_mfunc_SharedAbility_update_SharedAbilityPtr_GamePtr(ct_stacktrace, 194, 149, ability, game);
}
    for (i = 0; i < (self->damage_texts_last_in_use_handle + 1); i += 1) {
        if (i < 0 || i > self->damage_texts.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->damage_texts.size);
                ct_stacktrace_push(ct_stacktrace, 194, 151);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            damage_text = &self->damage_texts.arr[i];
        if (!(damage_text->in_use_in_pool)) {
            continue;
}
        void_text_update_TextSMPtr_GamePtr(ct_stacktrace, 194, 154, damage_text, game);
}
    for (i = 0; i < self->maps.size; i++) {
        map = &self->maps.arr[i];
        int_mfunc_Map_update_MapPtr_GamePtr(ct_stacktrace, 194, 156, map, game);
}
    if (self->visible_map_handle < 0 || self->visible_map_handle > self->maps.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->visible_map_handle, self->maps.size);
            ct_stacktrace_push(ct_stacktrace, 194, 159);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        visible_map = &self->maps.arr[self->visible_map_handle];
    void_mfunc_Map_update_visible_map_MapPtr_GamePtr(ct_stacktrace, 194, 160, visible_map, game);
    void_mfunc_UI_update_UIPtr_GamePtr(ct_stacktrace, 194, 164, &self->ui, game);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_World_draw_WorldPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, World* self, Game* game) {
    Map* visible_map = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->visible_map_handle < 0 || self->visible_map_handle > self->maps.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->visible_map_handle, self->maps.size);
            ct_stacktrace_push(ct_stacktrace, 212, 167);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        visible_map = &self->maps.arr[self->visible_map_handle];
    void_mfunc_Map_draw_MapPtr_GamePtr(ct_stacktrace, 212, 168, visible_map, game);
    void_mfunc_UI_draw_UIPtr_GamePtr(ct_stacktrace, 212, 170, &self->ui, game);
    ct_stacktrace_pop(ct_stacktrace);
}

