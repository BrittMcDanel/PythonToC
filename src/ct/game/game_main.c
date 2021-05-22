#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "ct_stacktrace.h"
#include "engine.h"
#include "ct_array.h"
#include "constants.h"
#include "game.h"

int main() {
    CT_StackTrace* ct_stacktrace = (CT_StackTrace*) malloc(sizeof(CT_StackTrace));
    ct_stacktrace_init(ct_stacktrace);
    ct_stacktrace_add_function(ct_stacktrace, "utils", "create_point");
    ct_stacktrace_add_function(ct_stacktrace, "path_finder", "PathFinder.check_lookup_table_size");
    ct_stacktrace_add_function(ct_stacktrace, "ct_array", "push_value");
    ct_stacktrace_add_function(ct_stacktrace, "engine", "Engine.init");
    ct_stacktrace_add_function(ct_stacktrace, "engine", "Engine.get_image");
    ct_stacktrace_add_function(ct_stacktrace, "ct_array", "next");
    ct_stacktrace_add_function(ct_stacktrace, "utils", "create_rect");
    ct_stacktrace_add_function(ct_stacktrace, "ct_array", "push");
    ct_stacktrace_add_function(ct_stacktrace, "shared_sprite", "SpriteDB.init");
    ct_stacktrace_add_function(ct_stacktrace, "ct_array", "clear");
    ct_stacktrace_add_function(ct_stacktrace, "item", "Item.set_to");
    ct_stacktrace_add_function(ct_stacktrace, "shared_item", "ItemDB.init");
    ct_stacktrace_add_function(ct_stacktrace, "ability", "Ability.set_to");
    ct_stacktrace_add_function(ct_stacktrace, "shared_ability", "AbilityDB.init");
    ct_stacktrace_add_function(ct_stacktrace, "inventory", "Inventory.init");
    ct_stacktrace_add_function(ct_stacktrace, "ai", "AIAbility.clear");
    ct_stacktrace_add_function(ct_stacktrace, "utils", "create_color");
    ct_stacktrace_add_function(ct_stacktrace, "ct_array", "string_set_literal");
    ct_stacktrace_add_function(ct_stacktrace, "text", "text_set");
    ct_stacktrace_add_function(ct_stacktrace, "utils", "rects_are_equal");
    ct_stacktrace_add_function(ct_stacktrace, "shared_sprite", "SpriteDB.find");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.init");
    ct_stacktrace_add_function(ct_stacktrace, "unit_sprite", "UnitSprite.set_to");
    ct_stacktrace_add_function(ct_stacktrace, "utils", "get_move_grid_size_dims");
    ct_stacktrace_add_function(ct_stacktrace, "utils", "Range.set");
    ct_stacktrace_add_function(ct_stacktrace, "utils", "Range.set_with_max_to_upper_bound");
    ct_stacktrace_add_function(ct_stacktrace, "shared_ability", "SharedAbility.set_to");
    ct_stacktrace_add_function(ct_stacktrace, "ai", "AIAbility.set");
    ct_stacktrace_add_function(ct_stacktrace, "shared_item", "SharedItem.set_to");
    ct_stacktrace_add_function(ct_stacktrace, "utils", "get_faction_color");
    ct_stacktrace_add_function(ct_stacktrace, "text", "text_set_color");
    ct_stacktrace_add_function(ct_stacktrace, "ct_array", "string_set");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.set_to");
    ct_stacktrace_add_function(ct_stacktrace, "shared_unit", "UnitDB.init");
    ct_stacktrace_add_function(ct_stacktrace, "ui_containers", "TopNav.init");
    ct_stacktrace_add_function(ct_stacktrace, "ui_containers", "RecruitNoviceModal.init");
    ct_stacktrace_add_function(ct_stacktrace, "ui_containers", "GuildWindow.init");
    ct_stacktrace_add_function(ct_stacktrace, "ui_containers", "UnitsWindow.init");
    ct_stacktrace_add_function(ct_stacktrace, "ui_containers", "MerchantsWindow.init");
    ct_stacktrace_add_function(ct_stacktrace, "ui", "UI.init");
    ct_stacktrace_add_function(ct_stacktrace, "map", "Map.init");
    ct_stacktrace_add_function(ct_stacktrace, "ct_array", "pool_init");
    ct_stacktrace_add_function(ct_stacktrace, "building", "Building.init");
    ct_stacktrace_add_function(ct_stacktrace, "guild", "Guild.init");
    ct_stacktrace_add_function(ct_stacktrace, "shared_item", "SharedItem.init");
    ct_stacktrace_add_function(ct_stacktrace, "shared_ability", "SharedAbility.init");
    ct_stacktrace_add_function(ct_stacktrace, "text", "text_init");
    ct_stacktrace_add_function(ct_stacktrace, "ct_array", "pool_of_text_init");
    ct_stacktrace_add_function(ct_stacktrace, "tween", "TweenXY.init");
    ct_stacktrace_add_function(ct_stacktrace, "ct_array", "pool_get_handle");
    ct_stacktrace_add_function(ct_stacktrace, "world", "World.get_handle");
    ct_stacktrace_add_function(ct_stacktrace, "utils", "tile_point_to_world_point");
    ct_stacktrace_add_function(ct_stacktrace, "warp_point", "WarpPoint.set");
    ct_stacktrace_add_function(ct_stacktrace, "map", "Map.create_initial_overworld");
    ct_stacktrace_add_function(ct_stacktrace, "engine", "Engine.get_rand_int");
    ct_stacktrace_add_function(ct_stacktrace, "ct_array", "remove_at");
    ct_stacktrace_add_function(ct_stacktrace, "ct_array", "find_and_remove_handle");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.join_map");
    ct_stacktrace_add_function(ct_stacktrace, "utils", "rect_contains_rect");
    ct_stacktrace_add_function(ct_stacktrace, "map", "Map.unit_occupies_tile_point_move_grid");
    ct_stacktrace_add_function(ct_stacktrace, "map", "Map.get_random_unoccupied_move_grid_tile_point");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.set_random_spawn_point");
    ct_stacktrace_add_function(ct_stacktrace, "map", "Map.create_initial");
    ct_stacktrace_add_function(ct_stacktrace, "building", "Building.set_to");
    ct_stacktrace_add_function(ct_stacktrace, "world", "World.create_initial_maps");
    ct_stacktrace_add_function(ct_stacktrace, "guild", "Guild.set_to");
    ct_stacktrace_add_function(ct_stacktrace, "world", "World.create_guilds");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.is_merchant");
    ct_stacktrace_add_function(ct_stacktrace, "ct_array", "string_cat");
    ct_stacktrace_add_function(ct_stacktrace, "ct_array", "string_cat_literal");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.join_guild");
    ct_stacktrace_add_function(ct_stacktrace, "world", "World.create_initial_units");
    ct_stacktrace_add_function(ct_stacktrace, "world", "World.init");
    ct_stacktrace_add_function(ct_stacktrace, "game", "Game.start");
    ct_stacktrace_add_function(ct_stacktrace, "engine", "Engine.update");
    ct_stacktrace_add_function(ct_stacktrace, "utils", "world_point_to_tile_point");
    ct_stacktrace_add_function(ct_stacktrace, "utils", "world_point_to_index_with_camera");
    ct_stacktrace_add_function(ct_stacktrace, "utils", "get_stat_points_for_level");
    ct_stacktrace_add_function(ct_stacktrace, "utils", "get_stat_cost");
    ct_stacktrace_add_function(ct_stacktrace, "utils", "Range.inc");
    ct_stacktrace_add_function(ct_stacktrace, "utils", "points_are_equal");
    ct_stacktrace_add_function(ct_stacktrace, "ui", "UI.clear");
    ct_stacktrace_add_function(ct_stacktrace, "tween", "TweenXY.update");
    ct_stacktrace_add_function(ct_stacktrace, "ct_array", "pool_get_last_in_use_handle");
    ct_stacktrace_add_function(ct_stacktrace, "ct_array", "pool_release_handle");
    ct_stacktrace_add_function(ct_stacktrace, "world", "World.release_handle");
    ct_stacktrace_add_function(ct_stacktrace, "world", "World.remove_all_tweens");
    ct_stacktrace_add_function(ct_stacktrace, "world", "World.handle_tween_on_start");
    ct_stacktrace_add_function(ct_stacktrace, "utils", "DoublePoint.init");
    ct_stacktrace_add_function(ct_stacktrace, "tween", "TweenXY.set");
    ct_stacktrace_add_function(ct_stacktrace, "inventory", "Inventory.clear_slot");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.sell_items");
    ct_stacktrace_add_function(ct_stacktrace, "map", "Map.in_bounds_move_grid");
    ct_stacktrace_add_function(ct_stacktrace, "world", "World.remove_all_tweens_with_higher_level_type");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.clear_move_tweens");
    ct_stacktrace_add_function(ct_stacktrace, "path_finder", "PathFinder.clear_prev_path_data");
    ct_stacktrace_add_function(ct_stacktrace, "utils", "manhattan_distance");
    ct_stacktrace_add_function(ct_stacktrace, "utils", "get_1d_from_2d_idx");
    ct_stacktrace_add_function(ct_stacktrace, "path_finder", "insert_point");
    ct_stacktrace_add_function(ct_stacktrace, "path_finder", "arr_contains_key");
    ct_stacktrace_add_function(ct_stacktrace, "ct_array", "reverse");
    ct_stacktrace_add_function(ct_stacktrace, "path_finder", "pq_insertion_sort");
    ct_stacktrace_add_function(ct_stacktrace, "path_finder", "PathFinder.set_path");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.move_to");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.try_find_and_move_to_merchant_shop");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.move_to_overworld_warp_point");
    ct_stacktrace_add_function(ct_stacktrace, "inventory", "Inventory.next_empty_slot_handle");
    ct_stacktrace_add_function(ct_stacktrace, "inventory", "Inventory.add_item");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.merchant_get_sellable_items_from_guild");
    ct_stacktrace_add_function(ct_stacktrace, "map", "Map.get_random_merchant_shop_point");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.move_to_setup_merchant_shop");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.give_items_to_guild");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.move_to_shop");
    ct_stacktrace_add_function(ct_stacktrace, "unit_sprite", "UnitSprite.play_animation");
    ct_stacktrace_add_function(ct_stacktrace, "map", "Map.get_random_town_point");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.move_to_random_town_point");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.set_spawn_point");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.move_to_town_warp_point");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.move_to_guild_building");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.move_to_battle_warp_point");
    ct_stacktrace_add_function(ct_stacktrace, "inventory", "Inventory.inventory_is_empty");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.merchant_sell_to_unit");
    ct_stacktrace_add_function(ct_stacktrace, "utils", "Range.value_is_at_min");
    ct_stacktrace_add_function(ct_stacktrace, "utils", "Range.dec");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.on_hit");
    ct_stacktrace_add_function(ct_stacktrace, "utils", "Range.value_is_at_max");
    ct_stacktrace_add_function(ct_stacktrace, "utils", "Range.set_to_min");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.do_item_drops");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.on_dead");
    ct_stacktrace_add_function(ct_stacktrace, "text", "text_set_without_str");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.change_to_sell_item_ai_state");
    ct_stacktrace_add_function(ct_stacktrace, "world", "World.handle_tween_on_complete");
    ct_stacktrace_add_function(ct_stacktrace, "world", "World.update_tween_arr");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.update_towns_person_ai");
    ct_stacktrace_add_function(ct_stacktrace, "inventory", "Inventory.has_merchant_sellable_items");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.update_merchant_ai");
    ct_stacktrace_add_function(ct_stacktrace, "utils", "Range.set_to_max");
    ct_stacktrace_add_function(ct_stacktrace, "utils", "Range.value_pct_of_max");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.is_ally_or_guild_faction");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.move_towards_tile_point");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.closest_opposite_unit_handle");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.get_ai_ability");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.perform_ability");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.update_ai");
    ct_stacktrace_add_function(ct_stacktrace, "unit_sprite", "UnitSprite.set_current_src");
    ct_stacktrace_add_function(ct_stacktrace, "utils", "set_scaled_rect_with_camera");
    ct_stacktrace_add_function(ct_stacktrace, "utils", "set_scaled_rect");
    ct_stacktrace_add_function(ct_stacktrace, "utils", "RenderDst.update");
    ct_stacktrace_add_function(ct_stacktrace, "unit_sprite", "UnitSprite.update");
    ct_stacktrace_add_function(ct_stacktrace, "game", "Game.get_current_frame");
    ct_stacktrace_add_function(ct_stacktrace, "utils", "rect_contains_point");
    ct_stacktrace_add_function(ct_stacktrace, "input_events", "InputEvents.update");
    ct_stacktrace_add_function(ct_stacktrace, "ui_sprite", "UISprite.update");
    ct_stacktrace_add_function(ct_stacktrace, "text", "text_update");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.update");
    ct_stacktrace_add_function(ct_stacktrace, "shared_item", "SharedItem.update");
    ct_stacktrace_add_function(ct_stacktrace, "shared_ability", "SharedAbility.update");
    ct_stacktrace_add_function(ct_stacktrace, "map", "Map.update");
    ct_stacktrace_add_function(ct_stacktrace, "shared_sprite", "SharedSprite.update");
    ct_stacktrace_add_function(ct_stacktrace, "tile", "Tile.update");
    ct_stacktrace_add_function(ct_stacktrace, "sprite", "Sprite.update");
    ct_stacktrace_add_function(ct_stacktrace, "input_events", "InputEvents.clear");
    ct_stacktrace_add_function(ct_stacktrace, "ui_containers", "RecruitNoviceModal.set_visible");
    ct_stacktrace_add_function(ct_stacktrace, "building", "Building.on_click");
    ct_stacktrace_add_function(ct_stacktrace, "building", "Building.update");
    ct_stacktrace_add_function(ct_stacktrace, "map", "Map.update_visible_map");
    ct_stacktrace_add_function(ct_stacktrace, "ui_containers", "UIRenderable.clear");
    ct_stacktrace_add_function(ct_stacktrace, "ui_containers", "UIRenderable.set_sprite");
    ct_stacktrace_add_function(ct_stacktrace, "ui_containers", "UIRenderable.set_text_lg");
    ct_stacktrace_add_function(ct_stacktrace, "ui_containers", "TopNav.update");
    ct_stacktrace_add_function(ct_stacktrace, "ui_containers", "UIRenderable.set_regular_sprite");
    ct_stacktrace_add_function(ct_stacktrace, "ui_containers", "GuildWindow.update_inventory_tab");
    ct_stacktrace_add_function(ct_stacktrace, "ui_containers", "GuildWindow.update");
    ct_stacktrace_add_function(ct_stacktrace, "ui_containers", "UIRenderable.set_unit");
    ct_stacktrace_add_function(ct_stacktrace, "ui_containers", "UnitsWindow.update_status_tab");
    ct_stacktrace_add_function(ct_stacktrace, "ui_containers", "UnitsWindow.update_inventory_tab");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.get_ability_skill_points");
    ct_stacktrace_add_function(ct_stacktrace, "ui_containers", "UnitsWindow.update_ability_tab");
    ct_stacktrace_add_function(ct_stacktrace, "utils", "get_unit_name_job_tier");
    ct_stacktrace_add_function(ct_stacktrace, "utils", "unit_can_job_change");
    ct_stacktrace_add_function(ct_stacktrace, "shared_unit", "UnitDB.get_unit");
    ct_stacktrace_add_function(ct_stacktrace, "ui_containers", "UIRenderable.set_unit_sprite");
    ct_stacktrace_add_function(ct_stacktrace, "ui_containers", "UnitsWindow.update_job_change_tab");
    ct_stacktrace_add_function(ct_stacktrace, "ui_containers", "UnitsWindow.update_ai_tab");
    ct_stacktrace_add_function(ct_stacktrace, "ui_containers", "UnitsWindow.update");
    ct_stacktrace_add_function(ct_stacktrace, "ui_containers", "MerchantsWindow.update");
    ct_stacktrace_add_function(ct_stacktrace, "ui_containers", "RecruitNoviceModal.update");
    ct_stacktrace_add_function(ct_stacktrace, "ui_containers", "UnitsWindow.set_visible");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.get_ability");
    ct_stacktrace_add_function(ct_stacktrace, "ui_containers", "MerchantsWindow.set_visible");
    ct_stacktrace_add_function(ct_stacktrace, "ui_containers", "GuildWindow.set_visible");
    ct_stacktrace_add_function(ct_stacktrace, "ui", "UI.on_click");
    ct_stacktrace_add_function(ct_stacktrace, "ui", "UI.after_on_click");
    ct_stacktrace_add_function(ct_stacktrace, "ui", "UI.update");
    ct_stacktrace_add_function(ct_stacktrace, "world", "World.update");
    ct_stacktrace_add_function(ct_stacktrace, "game", "Game.update");
    ct_stacktrace_add_function(ct_stacktrace, "shared_sprite", "SharedSprite.draw");
    ct_stacktrace_add_function(ct_stacktrace, "tile", "Tile.draw");
    ct_stacktrace_add_function(ct_stacktrace, "sprite", "Sprite.draw");
    ct_stacktrace_add_function(ct_stacktrace, "building", "Building.draw");
    ct_stacktrace_add_function(ct_stacktrace, "map", "Map.units_insertion_sort");
    ct_stacktrace_add_function(ct_stacktrace, "unit_sprite", "UnitSprite.draw");
    ct_stacktrace_add_function(ct_stacktrace, "text", "text_draw");
    ct_stacktrace_add_function(ct_stacktrace, "ui_sprite", "UISprite.draw");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.draw");
    ct_stacktrace_add_function(ct_stacktrace, "shared_item", "SharedItem.draw");
    ct_stacktrace_add_function(ct_stacktrace, "shared_ability", "SharedAbility.draw");
    ct_stacktrace_add_function(ct_stacktrace, "map", "Map.draw");
    ct_stacktrace_add_function(ct_stacktrace, "sprite", "Sprite.draw_at");
    ct_stacktrace_add_function(ct_stacktrace, "unit_sprite", "UnitSprite.draw_idle_at");
    ct_stacktrace_add_function(ct_stacktrace, "unit", "Unit.draw_idle_at");
    ct_stacktrace_add_function(ct_stacktrace, "ui", "UI.draw");
    ct_stacktrace_add_function(ct_stacktrace, "world", "World.draw");
    ct_stacktrace_add_function(ct_stacktrace, "game", "Game.draw");
    ct_stacktrace_add_function(ct_stacktrace, "game_main", "main");
    Game* game = NULL;

        game = (Game*)malloc(sizeof(Game) * 1);
    memset(game, 0, sizeof(Game) * 1);
    void_mfunc_Game_start_GamePtr(ct_stacktrace, 214, 11, game);
    while (!(game->engine.quit)) {
        engine_clear(&game->engine);
        void_mfunc_Engine_update_EnginePtr(ct_stacktrace, 214, 14, &game->engine);
        void_mfunc_Game_update_GamePtr(ct_stacktrace, 214, 15, game);
        void_mfunc_Game_draw_GamePtr(ct_stacktrace, 214, 16, game);
        engine_present(&game->engine);
}
    engine_free(&game->engine);
    free(game);
    free(ct_stacktrace);
    return 0;
}

