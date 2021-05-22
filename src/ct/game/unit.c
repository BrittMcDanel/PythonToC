#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "ct_stacktrace.h"
#include "unit.h"
#include "engine.h"
#include "guild.h"
#include "image.h"
#include "constants.h"
#include "utils.h"
#include "image.h"
#include "ct_array.h"
#include "unit_sprite.h"
#include "tween.h"
#include "text.h"
#include "ability.h"
#include "stats.h"
#include "shared_item.h"
#include "inventory.h"
#include "shared_ability.h"
#include "ai.h"
#include "ui_sprite.h"
#include "game.h"
#include "map.h"

void void_mfunc_Unit_init_UnitPtr_GamePtr_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game, int handle) {
    AIAbility* ai_ability = NULL;
    SDL_Color text_color = {0};
    SDL_Point text_dst = {0};
    SDL_Color text_outline_color = {0};
    int i = 0;
    SDL_Rect src = {0};

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->handle = handle;
    self->in_use_in_pool = false;
    void_mfunc_Inventory_init_InventoryPtr(ct_stacktrace, 21, 73, &self->inventory);
    self->map_handle = -1;
    self->aggro_towards_unit_handle = -1;
    self->attacked_by_guild_handle = -1;
    self->unit_handle_buying_from_merchant = -1;
    self->ai_state = UnitAIState_Battle;
    self->ai_abilities.size = 30;
    for (i = 0; i < self->ai_abilities.size; i++) {
        ai_ability = &self->ai_abilities.arr[i];
        void_mfunc_AIAbility_clear_AIAbilityPtr(ct_stacktrace, 21, 81, ai_ability);
}
    text_dst = SDL_Point_create_point_int_int(ct_stacktrace, 21, 84, 0, 0);
    text_color = SDL_Color_create_color_int_int_int_int(ct_stacktrace, 21, 85, 255, 255, 255, 255);
    text_outline_color = SDL_Color_create_color_int_int_int_int(ct_stacktrace, 21, 86, 0, 0, 0, 255);
    void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 21, 87, &self->display_name_text, game, self->display_name.arr, &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 16, &text_color, 1, &text_outline_color, false);
    self->display_name_text.render_dst.is_camera_rendered = true;
    void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 21, 89, &self->guild_display_name_text, game, self->guild_display_name.arr, &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 16, &text_color, 1, &text_outline_color, false);
    self->guild_display_name_text.render_dst.is_camera_rendered = true;
    self->merchant_shop_background.render_dst.is_camera_rendered = true;
    self->merchant_shop_background.anim_speed = 100;
    src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 21, 93, 0, 512, 80, 20);
    self->merchant_shop_background.shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 21, 94, &game->sprite_db, game, ImageName_UI, &src);
    text_color = SDL_Color_create_color_int_int_int_int(ct_stacktrace, 21, 95, 0, 0, 0, 255);
    void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 21, 96, &self->merchant_shop_text, game, "Slyme cards", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 10, &text_color, 0, &text_outline_color, false);
    self->merchant_shop_text.render_dst.is_camera_rendered = true;
    self->guild_icon.render_dst.is_camera_rendered = true;
    self->guild_icon.anim_speed = 100;
    src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 21, 101, 0, 60, 16, 16);
    self->guild_icon.shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 21, 102, &game->sprite_db, game, ImageName_Items, &src);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Unit_set_to_UnitPtr_GamePtr_UnitName_Faction(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game, UnitName unit_name, Faction faction) {
    SDL_Color text_color = {0};
    AIAbility* unit_ai_ability = NULL;
    SharedAbility* ability = NULL;
    SharedAbility* job_abilitiy = NULL;
    Uint64 attack_speed_max_value = 0;
    int unit_name_as_int = 0;
    Uint64 stats_max = 0;
    SDL_Point move_grid_hit_box_size_dims = {0};
    Uint64 stats_min = 0;
    Uint64 experience_max_value = 0;
    Uint64 stats_current = 0;
    Uint64 hp_max_value = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    void_clear_Array_SharedAbility_10Ptr(ct_stacktrace, 32, 832, &self->job_abilities);
    void_clear_Array_SharedAbility_30Ptr(ct_stacktrace, 32, 833, &self->abilities);
    void_clear_Array_SharedItem_5Ptr(ct_stacktrace, 32, 834, &self->item_drops);
    self->unit_name = unit_name;
    self->faction = faction;
    void_mfunc_UnitSprite_set_to_UnitSpritePtr_GamePtr_UnitName(ct_stacktrace, 32, 838, &self->sprite, game, unit_name);
    if (self->sprite.hit_box_size.x % game->move_grid_tile_size.x != 0) {
        printf("%s %s %d %s %d\n", "Unit.set_to - sprite's hit_box's width mod grid tile size != 0.", "width:", self->sprite.hit_box_size.x, "grid tile size:", game->move_grid_tile_size.x);
        ct_stacktrace_push(ct_stacktrace, 32, 847);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    if (self->sprite.hit_box_size.y % game->move_grid_tile_size.y != 0) {
        printf("%s %s %d %s %d\n", "Unit.set_to - sprite's hit_box's height mod grid tile size != 0.", "height:", self->sprite.hit_box_size.y, "grid tile size:", game->move_grid_tile_size.y);
        ct_stacktrace_push(ct_stacktrace, 32, 850);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    move_grid_hit_box_size_dims = SDL_Point_get_move_grid_size_dims_int_int_SDL_PointPtr(ct_stacktrace, 32, 851, self->sprite.hit_box_size.x, self->sprite.hit_box_size.y, &game->move_grid_tile_size);
    self->tile_point_hit_box.w = move_grid_hit_box_size_dims.x;
    self->tile_point_hit_box.h = move_grid_hit_box_size_dims.y;
    self->respawn_time = 10000;
    stats_min = (Uint64)(0);
    stats_current = (Uint64)(10);
    stats_max = (Uint64)(99);
    hp_max_value = (Uint64)(9999999);
    experience_max_value = (Uint64)(9999999);
    attack_speed_max_value = (Uint64)(10000);
    self->stats.level = 1;
    self->stats.job_level = 1;
    self->stats.experience_drop = 5;
    self->stats.job_experience_drop = 2;
    void_mfunc_Range_set_RangePtr_Uint64_Uint64_Uint64(ct_stacktrace, 32, 866, &self->stats.experience, stats_min, stats_min, experience_max_value);
    void_mfunc_Range_set_RangePtr_Uint64_Uint64_Uint64(ct_stacktrace, 32, 867, &self->stats.job_experience, stats_min, stats_min, experience_max_value);
    self->stats.experience.max = (Uint64)(100);
    self->stats.job_experience.max = (Uint64)(30);
    void_mfunc_Range_set_with_max_to_upper_bound_RangePtr_Uint64_Uint64_Uint64(ct_stacktrace, 32, 870, &self->stats.strength, stats_min, stats_current, stats_max);
    void_mfunc_Range_set_with_max_to_upper_bound_RangePtr_Uint64_Uint64_Uint64(ct_stacktrace, 32, 871, &self->stats.intelligence, stats_min, stats_current, stats_max);
    void_mfunc_Range_set_with_max_to_upper_bound_RangePtr_Uint64_Uint64_Uint64(ct_stacktrace, 32, 872, &self->stats.dexterity, stats_min, stats_current, stats_max);
    void_mfunc_Range_set_with_max_to_upper_bound_RangePtr_Uint64_Uint64_Uint64(ct_stacktrace, 32, 873, &self->stats.vitality, stats_min, stats_current, stats_max);
    void_mfunc_Range_set_with_max_to_upper_bound_RangePtr_Uint64_Uint64_Uint64(ct_stacktrace, 32, 874, &self->stats.agility, stats_min, stats_current, stats_max);
    void_mfunc_Range_set_with_max_to_upper_bound_RangePtr_Uint64_Uint64_Uint64(ct_stacktrace, 32, 875, &self->stats.luck, stats_min, stats_current, stats_max);
    void_mfunc_SharedAbility_set_to_SharedAbilityPtr_GamePtr_AbilityName(ct_stacktrace, 32, 876, &self->default_attack_ability, game, AbilityName_MeleeAttack);
    if (unit_name == UnitName_RandomTownsPerson0) {
        self->faction = Faction_Neutral;
        self->unit_type = UnitType_TownsPerson;
        void_string_set_literal_Array_char_100Ptr_charPtr(ct_stacktrace, 32, 881, &self->display_name, "Villager");
        void_mfunc_Range_set_RangePtr_Uint64_Uint64_Uint64(ct_stacktrace, 32, 884, &self->stats.hp, (Uint64)(0), (Uint64)(10), hp_max_value);
}
    else if (unit_name == UnitName_Merchant) {
        void_string_set_literal_Array_char_100Ptr_charPtr(ct_stacktrace, 32, 886, &self->display_name, "Merchant");
        void_mfunc_Range_set_RangePtr_Uint64_Uint64_Uint64(ct_stacktrace, 32, 887, &self->stats.hp, (Uint64)(0), (Uint64)(500), hp_max_value);
        void_mfunc_Range_set_RangePtr_Uint64_Uint64_Uint64(ct_stacktrace, 32, 888, &self->stats.attack_speed, (Uint64)(0), (Uint64)(2000), attack_speed_max_value);
}
    else if (unit_name == UnitName_Explorer) {
        void_string_set_literal_Array_char_100Ptr_charPtr(ct_stacktrace, 32, 890, &self->display_name, "Explorer");
        void_mfunc_Range_set_RangePtr_Uint64_Uint64_Uint64(ct_stacktrace, 32, 891, &self->stats.hp, (Uint64)(0), (Uint64)(500), hp_max_value);
        void_mfunc_Range_set_RangePtr_Uint64_Uint64_Uint64(ct_stacktrace, 32, 892, &self->stats.attack_speed, (Uint64)(0), (Uint64)(2000), attack_speed_max_value);
}
    else if (unit_name == UnitName_Mage) {
        void_string_set_literal_Array_char_100Ptr_charPtr(ct_stacktrace, 32, 894, &self->display_name, "Mage");
        job_abilitiy = SharedAbilityPtr_next_Array_SharedAbility_10Ptr(ct_stacktrace, 32, 895, &self->job_abilities);
        void_mfunc_SharedAbility_set_to_SharedAbilityPtr_GamePtr_AbilityName(ct_stacktrace, 32, 896, job_abilitiy, game, AbilityName_Fire);
        void_mfunc_Ability_set_to_AbilityPtr_GamePtr_AbilityName(ct_stacktrace, 32, 897, &game->temp_ability, game, AbilityName_Fire);
        ability = SharedAbilityPtr_next_Array_SharedAbility_30Ptr(ct_stacktrace, 32, 898, &self->abilities);
        void_mfunc_SharedAbility_set_to_SharedAbilityPtr_GamePtr_AbilityName(ct_stacktrace, 32, 899, ability, game, AbilityName_Fire);
        printf("%d\n", self->ai_abilities.size);
        if (0 < 0 || 0 > self->ai_abilities.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", 0, self->ai_abilities.size);
                ct_stacktrace_push(ct_stacktrace, 32, 901);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit_ai_ability = &self->ai_abilities.arr[0];
        void_mfunc_AIAbility_set_AIAbilityPtr_int_AIAbilityCondition(ct_stacktrace, 32, 902, unit_ai_ability, 0, AIAbilityCondition_Always);
        void_mfunc_Range_set_RangePtr_Uint64_Uint64_Uint64(ct_stacktrace, 32, 903, &self->stats.hp, (Uint64)(0), (Uint64)(500), hp_max_value);
        void_mfunc_Range_set_RangePtr_Uint64_Uint64_Uint64(ct_stacktrace, 32, 904, &self->stats.attack_speed, (Uint64)(0), (Uint64)(4000), attack_speed_max_value);
}
    else if (unit_name == UnitName_Wizard) {
        void_string_set_literal_Array_char_100Ptr_charPtr(ct_stacktrace, 32, 906, &self->display_name, "Wizard");
        job_abilitiy = SharedAbilityPtr_next_Array_SharedAbility_10Ptr(ct_stacktrace, 32, 907, &self->job_abilities);
        void_mfunc_SharedAbility_set_to_SharedAbilityPtr_GamePtr_AbilityName(ct_stacktrace, 32, 908, job_abilitiy, game, AbilityName_Fire);
        ability = SharedAbilityPtr_next_Array_SharedAbility_30Ptr(ct_stacktrace, 32, 909, &self->abilities);
        void_mfunc_SharedAbility_set_to_SharedAbilityPtr_GamePtr_AbilityName(ct_stacktrace, 32, 910, ability, game, AbilityName_Fire);
        if (0 < 0 || 0 > self->ai_abilities.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", 0, self->ai_abilities.size);
                ct_stacktrace_push(ct_stacktrace, 32, 911);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit_ai_ability = &self->ai_abilities.arr[0];
        void_mfunc_AIAbility_set_AIAbilityPtr_int_AIAbilityCondition(ct_stacktrace, 32, 912, unit_ai_ability, 0, AIAbilityCondition_Always);
        void_mfunc_Range_set_RangePtr_Uint64_Uint64_Uint64(ct_stacktrace, 32, 913, &self->stats.hp, (Uint64)(0), (Uint64)(500), hp_max_value);
        void_mfunc_Range_set_RangePtr_Uint64_Uint64_Uint64(ct_stacktrace, 32, 914, &self->stats.attack_speed, (Uint64)(0), (Uint64)(4000), attack_speed_max_value);
}
    else if (unit_name == UnitName_Scholar) {
        void_string_set_literal_Array_char_100Ptr_charPtr(ct_stacktrace, 32, 916, &self->display_name, "Scholar");
        job_abilitiy = SharedAbilityPtr_next_Array_SharedAbility_10Ptr(ct_stacktrace, 32, 917, &self->job_abilities);
        void_mfunc_SharedAbility_set_to_SharedAbilityPtr_GamePtr_AbilityName(ct_stacktrace, 32, 918, job_abilitiy, game, AbilityName_Fire);
        ability = SharedAbilityPtr_next_Array_SharedAbility_30Ptr(ct_stacktrace, 32, 919, &self->abilities);
        void_mfunc_SharedAbility_set_to_SharedAbilityPtr_GamePtr_AbilityName(ct_stacktrace, 32, 920, ability, game, AbilityName_Fire);
        if (0 < 0 || 0 > self->ai_abilities.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", 0, self->ai_abilities.size);
                ct_stacktrace_push(ct_stacktrace, 32, 921);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit_ai_ability = &self->ai_abilities.arr[0];
        void_mfunc_AIAbility_set_AIAbilityPtr_int_AIAbilityCondition(ct_stacktrace, 32, 922, unit_ai_ability, 0, AIAbilityCondition_Always);
        void_mfunc_Range_set_RangePtr_Uint64_Uint64_Uint64(ct_stacktrace, 32, 923, &self->stats.hp, (Uint64)(0), (Uint64)(500), hp_max_value);
        void_mfunc_Range_set_RangePtr_Uint64_Uint64_Uint64(ct_stacktrace, 32, 924, &self->stats.attack_speed, (Uint64)(0), (Uint64)(4000), attack_speed_max_value);
}
    else if (unit_name == UnitName_Slime) {
        void_string_set_literal_Array_char_100Ptr_charPtr(ct_stacktrace, 32, 926, &self->display_name, "Slyme");
        ability = SharedAbilityPtr_next_Array_SharedAbility_30Ptr(ct_stacktrace, 32, 927, &self->abilities);
        void_mfunc_SharedAbility_set_to_SharedAbilityPtr_GamePtr_AbilityName(ct_stacktrace, 32, 928, ability, game, AbilityName_MeleeAttack);
        void_mfunc_SharedItem_set_to_SharedItemPtr_GamePtr_ItemName_int_int(ct_stacktrace, 32, 929, &game->temp_shared_item, game, ItemName_Jelly, 1, 75);
        void_push_Array_SharedItem_5Ptr_SharedItemPtr(ct_stacktrace, 32, 930, &self->item_drops, &game->temp_shared_item);
        void_mfunc_SharedItem_set_to_SharedItemPtr_GamePtr_ItemName_int_int(ct_stacktrace, 32, 931, &game->temp_shared_item, game, ItemName_Apple, 1, 100);
        void_push_Array_SharedItem_5Ptr_SharedItemPtr(ct_stacktrace, 32, 932, &self->item_drops, &game->temp_shared_item);
        self->stats.experience_drop = 3;
        self->stats.job_experience_drop = 1;
        void_mfunc_Range_set_RangePtr_Uint64_Uint64_Uint64(ct_stacktrace, 32, 935, &self->stats.hp, (Uint64)(0), (Uint64)(40), hp_max_value);
        void_mfunc_Range_set_RangePtr_Uint64_Uint64_Uint64(ct_stacktrace, 32, 936, &self->stats.attack_speed, (Uint64)(0), (Uint64)(2000), attack_speed_max_value);
}
    else if (unit_name == UnitName_Bunny) {
        void_string_set_literal_Array_char_100Ptr_charPtr(ct_stacktrace, 32, 938, &self->display_name, "Rabyt");
        ability = SharedAbilityPtr_next_Array_SharedAbility_30Ptr(ct_stacktrace, 32, 939, &self->abilities);
        void_mfunc_SharedAbility_set_to_SharedAbilityPtr_GamePtr_AbilityName(ct_stacktrace, 32, 940, ability, game, AbilityName_MeleeAttack);
        void_mfunc_SharedItem_set_to_SharedItemPtr_GamePtr_ItemName_int_int(ct_stacktrace, 32, 941, &game->temp_shared_item, game, ItemName_FurPelt, 1, 75);
        void_push_Array_SharedItem_5Ptr_SharedItemPtr(ct_stacktrace, 32, 942, &self->item_drops, &game->temp_shared_item);
        void_mfunc_SharedItem_set_to_SharedItemPtr_GamePtr_ItemName_int_int(ct_stacktrace, 32, 943, &game->temp_shared_item, game, ItemName_Apple, 1, 100);
        void_push_Array_SharedItem_5Ptr_SharedItemPtr(ct_stacktrace, 32, 944, &self->item_drops, &game->temp_shared_item);
        self->stats.experience_drop = 5;
        self->stats.job_experience_drop = 2;
        void_mfunc_Range_set_RangePtr_Uint64_Uint64_Uint64(ct_stacktrace, 32, 947, &self->stats.hp, (Uint64)(0), (Uint64)(40), hp_max_value);
        void_mfunc_Range_set_RangePtr_Uint64_Uint64_Uint64(ct_stacktrace, 32, 948, &self->stats.attack_speed, (Uint64)(0), (Uint64)(2000), attack_speed_max_value);
}
    else if (unit_name == UnitName_Bat) {
        void_string_set_literal_Array_char_100Ptr_charPtr(ct_stacktrace, 32, 950, &self->display_name, "Bat");
        ability = SharedAbilityPtr_next_Array_SharedAbility_30Ptr(ct_stacktrace, 32, 951, &self->abilities);
        void_mfunc_SharedAbility_set_to_SharedAbilityPtr_GamePtr_AbilityName(ct_stacktrace, 32, 952, ability, game, AbilityName_MeleeAttack);
        void_mfunc_SharedItem_set_to_SharedItemPtr_GamePtr_ItemName_int_int(ct_stacktrace, 32, 953, &game->temp_shared_item, game, ItemName_BatWing, 1, 75);
        void_push_Array_SharedItem_5Ptr_SharedItemPtr(ct_stacktrace, 32, 954, &self->item_drops, &game->temp_shared_item);
        self->stats.experience_drop = 4;
        self->stats.job_experience_drop = 2;
        void_mfunc_Range_set_RangePtr_Uint64_Uint64_Uint64(ct_stacktrace, 32, 957, &self->stats.hp, (Uint64)(0), (Uint64)(40), hp_max_value);
        void_mfunc_Range_set_RangePtr_Uint64_Uint64_Uint64(ct_stacktrace, 32, 958, &self->stats.attack_speed, (Uint64)(0), (Uint64)(2000), attack_speed_max_value);
}
    else if (unit_name == UnitName_Stump) {
        void_string_set_literal_Array_char_100Ptr_charPtr(ct_stacktrace, 32, 960, &self->display_name, "Stump");
        ability = SharedAbilityPtr_next_Array_SharedAbility_30Ptr(ct_stacktrace, 32, 961, &self->abilities);
        void_mfunc_SharedAbility_set_to_SharedAbilityPtr_GamePtr_AbilityName(ct_stacktrace, 32, 962, ability, game, AbilityName_MeleeAttack);
        void_mfunc_SharedItem_set_to_SharedItemPtr_GamePtr_ItemName_int_int(ct_stacktrace, 32, 963, &game->temp_shared_item, game, ItemName_Branch, 1, 75);
        void_push_Array_SharedItem_5Ptr_SharedItemPtr(ct_stacktrace, 32, 964, &self->item_drops, &game->temp_shared_item);
        void_mfunc_SharedItem_set_to_SharedItemPtr_GamePtr_ItemName_int_int(ct_stacktrace, 32, 965, &game->temp_shared_item, game, ItemName_Apple, 1, 100);
        void_push_Array_SharedItem_5Ptr_SharedItemPtr(ct_stacktrace, 32, 966, &self->item_drops, &game->temp_shared_item);
        self->stats.experience_drop = 12;
        self->stats.job_experience_drop = 5;
        void_mfunc_Range_set_RangePtr_Uint64_Uint64_Uint64(ct_stacktrace, 32, 969, &self->stats.hp, (Uint64)(0), (Uint64)(40), hp_max_value);
        void_mfunc_Range_set_RangePtr_Uint64_Uint64_Uint64(ct_stacktrace, 32, 970, &self->stats.attack_speed, (Uint64)(0), (Uint64)(2000), attack_speed_max_value);
}
    else if (unit_name == UnitName_Shroomed) {
        void_string_set_literal_Array_char_100Ptr_charPtr(ct_stacktrace, 32, 972, &self->display_name, "Shroomed");
        ability = SharedAbilityPtr_next_Array_SharedAbility_30Ptr(ct_stacktrace, 32, 973, &self->abilities);
        void_mfunc_SharedAbility_set_to_SharedAbilityPtr_GamePtr_AbilityName(ct_stacktrace, 32, 974, ability, game, AbilityName_MeleeAttack);
        void_mfunc_SharedItem_set_to_SharedItemPtr_GamePtr_ItemName_int_int(ct_stacktrace, 32, 975, &game->temp_shared_item, game, ItemName_Mushroom, 1, 75);
        void_push_Array_SharedItem_5Ptr_SharedItemPtr(ct_stacktrace, 32, 976, &self->item_drops, &game->temp_shared_item);
        void_mfunc_SharedItem_set_to_SharedItemPtr_GamePtr_ItemName_int_int(ct_stacktrace, 32, 977, &game->temp_shared_item, game, ItemName_Apple, 1, 100);
        void_push_Array_SharedItem_5Ptr_SharedItemPtr(ct_stacktrace, 32, 978, &self->item_drops, &game->temp_shared_item);
        self->stats.experience_drop = 9;
        self->stats.job_experience_drop = 4;
        void_mfunc_Range_set_RangePtr_Uint64_Uint64_Uint64(ct_stacktrace, 32, 981, &self->stats.hp, (Uint64)(0), (Uint64)(40), hp_max_value);
        void_mfunc_Range_set_RangePtr_Uint64_Uint64_Uint64(ct_stacktrace, 32, 982, &self->stats.attack_speed, (Uint64)(0), (Uint64)(2000), attack_speed_max_value);
}
    else {
        unit_name_as_int = (int)(unit_name);
        printf("%s %d\n", "Unit.set_to. Unit name not handled. UnitName:", unit_name_as_int);
        ct_stacktrace_push(ct_stacktrace, 32, 986);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    text_color = SDL_Color_get_faction_color_Faction(ct_stacktrace, 32, 989, faction);
    void_text_set_color_TextLGPtr_GamePtr_SDL_ColorPtr(ct_stacktrace, 32, 990, &self->display_name_text, game, &text_color);
    void_text_set_color_TextLGPtr_GamePtr_SDL_ColorPtr(ct_stacktrace, 32, 991, &self->guild_display_name_text, game, &text_color);
    void_string_set_Array_char_200Ptr_Array_char_100Ptr(ct_stacktrace, 32, 992, &self->display_name_text.str, &self->display_name);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Unit_join_map_UnitPtr_GamePtr_MapPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game, Map* map) {
    Unit* unit = NULL;
    int unit_handle = 0;
    Map* current_map = NULL;
    int i = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->aggro_towards_unit_handle = -1;
    if (self->map_handle != -1) {
        if (self->map_handle < 0 || self->map_handle > game->world.maps.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", self->map_handle, game->world.maps.size);
                ct_stacktrace_push(ct_stacktrace, 57, 199);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            current_map = &game->world.maps.arr[self->map_handle];
        void_find_and_remove_handle_Array_int_300Ptr_int(ct_stacktrace, 57, 200, &current_map->unit_handles, self->handle);
        for (i = 0; i < current_map->unit_handles.size; i += 1) {
            if (i < 0 || i > current_map->unit_handles.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", i, current_map->unit_handles.size);
                    ct_stacktrace_push(ct_stacktrace, 57, 203);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                unit_handle = current_map->unit_handles.arr[i];
            if (unit_handle < 0 || unit_handle > game->world.units.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", unit_handle, game->world.units.size);
                    ct_stacktrace_push(ct_stacktrace, 57, 204);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                unit = &game->world.units.arr[unit_handle];
            if (unit->aggro_towards_unit_handle == self->handle) {
                unit->aggro_towards_unit_handle = -1;
    }
}
        if ((current_map->handle != 0 && !(current_map->is_town_map))) {
            self->battle_map_handle = current_map->handle;
    }
}
    self->map_handle = map->handle;
    void_push_value_Array_int_300Ptr_int(ct_stacktrace, 57, 215, &map->unit_handles, self->handle);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Unit_set_random_spawn_point_UnitPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game) {
    Map* map = NULL;
    SDL_Point world_point = {0};
    SDL_Point spawn_tile_point = {0};

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->map_handle < 0 || self->map_handle > game->world.maps.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->map_handle, game->world.maps.size);
            ct_stacktrace_push(ct_stacktrace, 61, 375);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        map = &game->world.maps.arr[self->map_handle];
    spawn_tile_point = SDL_Point_mfunc_Map_get_random_unoccupied_move_grid_tile_point_MapPtr_GamePtr_SDL_RectPtr(ct_stacktrace, 61, 376, map, game, &self->tile_point_hit_box);
    world_point = SDL_Point_tile_point_to_world_point_SDL_PointPtr_SDL_PointPtr(ct_stacktrace, 61, 377, &spawn_tile_point, &game->move_grid_tile_size);
    self->tile_point_hit_box.x = spawn_tile_point.x;
    self->tile_point_hit_box.y = spawn_tile_point.y;
    self->sprite.render_dst.dst.x = world_point.x;
    self->sprite.render_dst.dst.y = world_point.y;
    ct_stacktrace_pop(ct_stacktrace);
}

bool bool_mfunc_Unit_is_merchant_UnitPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
        ct_stacktrace_pop(ct_stacktrace);
return self->unit_name == UnitName_Merchant;
}

void void_mfunc_Unit_join_guild_UnitPtr_GamePtr_GuildPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game, Guild* guild) {
    int icon_w = 0;
    SDL_Rect src = {0};

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (guild->handle < 0 || guild->handle > game->world.guilds.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", guild->handle, game->world.guilds.size);
            ct_stacktrace_push(ct_stacktrace, 70, 175);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        guild = &game->world.guilds.arr[guild->handle];
    if (bool_mfunc_Unit_is_merchant_UnitPtr(ct_stacktrace, 70, 176, self)) {
        void_push_value_Array_int_30Ptr_int(ct_stacktrace, 70, 177, &guild->merchant_handles, self->handle);
}
    else {
        void_push_value_Array_int_30Ptr_int(ct_stacktrace, 70, 179, &guild->unit_handles, self->handle);
}
    self->guild_handle = guild->handle;
    void_string_set_literal_Array_char_100Ptr_charPtr(ct_stacktrace, 70, 183, &self->guild_display_name, "<");
    void_string_cat_Array_char_100Ptr_Array_char_100Ptr(ct_stacktrace, 70, 184, &self->guild_display_name, &guild->display_name);
    void_string_cat_literal_Array_char_100Ptr_charPtr(ct_stacktrace, 70, 185, &self->guild_display_name, ">");
    void_string_set_Array_char_200Ptr_Array_char_100Ptr(ct_stacktrace, 70, 187, &self->guild_display_name_text.str, &self->guild_display_name);
    self->guild_icon.render_dst.is_camera_rendered = true;
    self->guild_icon.anim_speed = 100;
    icon_w = 16;
    src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 70, 192, (icon_w * self->guild_handle), 60, 16, 16);
    self->guild_icon.shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 70, 193, &game->sprite_db, game, ImageName_Items, &src);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Unit_sell_items_UnitPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game) {
    Guild* guild = NULL;
    Uint64 cost = 0;
    int i = 0;
    InventorySlot* slot = NULL;
    int quantity = 0;
    int total_cost = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->guild_handle < 0 || self->guild_handle > game->world.guilds.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->guild_handle, game->world.guilds.size);
            ct_stacktrace_push(ct_stacktrace, 91, 466);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        guild = &game->world.guilds.arr[self->guild_handle];
    for (i = 0; i < self->inventory.slots.size; i++) {
        slot = &self->inventory.slots.arr[i];
        if (slot->slot_is_empty) {
            continue;
}
        if (slot->shared_item.item->item_type != ItemType_Misc) {
            continue;
}
        cost = slot->shared_item.item->cost;
        quantity = slot->shared_item.quantity;
        total_cost = (cost * quantity);
        guild->current_money += total_cost;
        guild->total_money_earned += total_cost;
        void_mfunc_Inventory_clear_slot_InventoryPtr_int(ct_stacktrace, 91, 482, &self->inventory, i);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Unit_clear_move_tweens_UnitPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    void_mfunc_World_remove_all_tweens_with_higher_level_type_WorldPtr_TweenHigherLevelType_int(ct_stacktrace, 94, 751, &game->world, TweenHigherLevelType_Move, self->handle);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Unit_move_to_UnitPtr_GamePtr_SDL_PointPtr_TweenType_MoveOptionsPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game, SDL_Point* target_point, TweenType move_tween_type, MoveOptions* move_options) {
    TweenXY* tween = NULL;
    SDL_Rect world_point_rect = {0};
    SDL_Point world_point = {0};
    int walk_speed = 0;
    int tween_handle = 0;
    Map* map = NULL;
    SDL_Rect prev_world_point_rect = {0};
    int unit_name_as_int = 0;
    SDL_Point path_tile_point = {0};
    SDL_Point unit_tile_point = {0};
    SDL_Point prev_point = {0};
    int faction_as_int = 0;
    SDL_Point* p = NULL;
    Uint32 delay = 0;
    Uint32 duration = 0;
    TweenCallback callback = {0};
    int i = 0;
    SDL_Point prev_world_point = {0};

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    void_mfunc_Unit_clear_move_tweens_UnitPtr_GamePtr(ct_stacktrace, 103, 755, self, game);
    unit_tile_point = SDL_Point_create_point_int_int(ct_stacktrace, 103, 756, self->tile_point_hit_box.x, self->tile_point_hit_box.y);
    if (self->map_handle < 0 || self->map_handle > game->world.maps.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->map_handle, game->world.maps.size);
            ct_stacktrace_push(ct_stacktrace, 103, 757);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        map = &game->world.maps.arr[self->map_handle];
    void_mfunc_PathFinder_set_path_PathFinderPtr_GamePtr_MapPtr_UnitPtr_SDL_PointPtr_SDL_PointPtr_bool(ct_stacktrace, 103, 758, &game->world.path_finder, game, map, self, &unit_tile_point, target_point, move_options->check_unit_collissions);
    if (game->world.path_finder.path.size == 0) {
        self->last_failed_path_time = game->engine.current_time;
        self->path_could_not_be_found = true;
        unit_name_as_int = (int)(self->unit_name);
        faction_as_int = (int)(self->faction);
        printf("%s %d %s %d %s %d %s %d %s %d %s %d %s %d %s %d\n", "Path size is 0.\nunit handle:", self->handle, "\nmap handle:", self->map_handle, "\nunit name:", unit_name_as_int, "\nfaction", faction_as_int, "\np.x", self->tile_point_hit_box.x, "\np.y", self->tile_point_hit_box.y, "\nt.x", target_point->x, "\nt.y", target_point->y);
                ct_stacktrace_pop(ct_stacktrace);
return;
}
    else {
        self->path_could_not_be_found = false;
}
    self->sprite.anim_state = UnitAnimState_Idle;
    walk_speed = 30;
    if (map->handle == 0) {
        walk_speed = 45;
}
    prev_point = SDL_Point_create_point_int_int(ct_stacktrace, 103, 777, self->tile_point_hit_box.x, self->tile_point_hit_box.y);
    for (i = 0; i < game->world.path_finder.path.size; i++) {
        p = &game->world.path_finder.path.arr[i];
        path_tile_point = *p;
        duration = (Uint32)(walk_speed);
        delay = (Uint32)((i * walk_speed));
        prev_world_point = SDL_Point_tile_point_to_world_point_SDL_PointPtr_SDL_PointPtr(ct_stacktrace, 103, 782, &prev_point, &game->move_grid_tile_size);
        world_point = SDL_Point_tile_point_to_world_point_SDL_PointPtr_SDL_PointPtr(ct_stacktrace, 103, 783, p, &game->move_grid_tile_size);
        prev_world_point_rect = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 103, 784, prev_world_point.x, prev_world_point.y, 0, 0);
        world_point_rect = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 103, 785, world_point.x, world_point.y, 0, 0);
        tween_handle = int_mfunc_World_get_handle_WorldPtr_HandleType(ct_stacktrace, 103, 786, &game->world, HandleType_TweenXY);
        if (tween_handle < 0 || tween_handle > game->world.tween_xys.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", tween_handle, game->world.tween_xys.size);
                ct_stacktrace_push(ct_stacktrace, 103, 787);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            tween = &game->world.tween_xys.arr[tween_handle];
        callback.tween_higher_level_type = TweenHigherLevelType_Move;
        callback.tween_type = move_tween_type;
        callback.handle = self->handle;
        callback.handle_type = HandleType_Unit;
        callback.tile_point = path_tile_point;
        callback.warp_point_handle = move_options->warp_point_handle;
        callback.merchant_unit_handle = move_options->merchant_unit_handle;
        callback.is_final_point_in_path = i == (game->world.path_finder.path.size - 1);
        void_mfunc_TweenXY_set_TweenXYPtr_GamePtr_SDL_RectPtr_SDL_RectPtr_SDL_RectPtr_bool_double_Uint32_Uint32_TweenCallbackPtr(ct_stacktrace, 103, 797, tween, game, &prev_world_point_rect, &self->sprite.render_dst.dst, &world_point_rect, false, 0.0, duration, delay, &callback);
        prev_point = path_tile_point;
    }
    ct_stacktrace_pop(ct_stacktrace);
}

bool bool_mfunc_Unit_try_find_and_move_to_merchant_shop_UnitPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game) {
    SDL_Point unit_tile_point = {0};
    Map* map = NULL;
    Unit* unit = NULL;
    MoveOptions move_options = {0};
    int unit_handle = 0;
    int merchant_y_diff = 0;
    int i = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->map_handle < 0 || self->map_handle > game->world.maps.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->map_handle, game->world.maps.size);
            ct_stacktrace_push(ct_stacktrace, 104, 515);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        map = &game->world.maps.arr[self->map_handle];
    for (i = 0; i < map->unit_handles.size; i += 1) {
        if (i < 0 || i > map->unit_handles.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, map->unit_handles.size);
                ct_stacktrace_push(ct_stacktrace, 104, 518);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit_handle = map->unit_handles.arr[i];
        if (unit_handle < 0 || unit_handle > game->world.units.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", unit_handle, game->world.units.size);
                ct_stacktrace_push(ct_stacktrace, 104, 519);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit = &game->world.units.arr[unit_handle];
        if ((((bool_mfunc_Unit_is_merchant_UnitPtr(ct_stacktrace, 104, 520, unit) && unit->guild_handle != self->guild_handle) && unit->unit_handle_buying_from_merchant == -1) && unit->ai_state == UnitAIState_MerchantSelling)) {
            self->ai_state = UnitAIState_MovingToBuyAtMerchant;
            unit->unit_handle_buying_from_merchant = self->handle;
            merchant_y_diff = 10;
            unit_tile_point = SDL_Point_create_point_int_int(ct_stacktrace, 104, 526, unit->tile_point_hit_box.x, (unit->tile_point_hit_box.y + merchant_y_diff));
            if (!(bool_mfunc_Map_in_bounds_move_grid_MapPtr_SDL_PointPtr(ct_stacktrace, 104, 527, map, &unit_tile_point))) {
                unit_tile_point.y -= merchant_y_diff;
}
            move_options.check_unit_collissions = false;
            move_options.warp_point_handle = 0;
            move_options.merchant_unit_handle = unit_handle;
            void_mfunc_Unit_move_to_UnitPtr_GamePtr_SDL_PointPtr_TweenType_MoveOptionsPtr(ct_stacktrace, 104, 532, self, game, &unit_tile_point, TweenType_UnitMoveToBuyAtMerchantShop, &move_options);
                        ct_stacktrace_pop(ct_stacktrace);
return true;
    }
}
        ct_stacktrace_pop(ct_stacktrace);
return false;
}

void void_mfunc_Unit_move_to_overworld_warp_point_UnitPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game) {
    WarpPoint* warp_point = NULL;
    int i = 0;
    MoveOptions move_options = {0};
    Map* map = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->map_handle < 0 || self->map_handle > game->world.maps.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->map_handle, game->world.maps.size);
            ct_stacktrace_push(ct_stacktrace, 105, 616);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        map = &game->world.maps.arr[self->map_handle];
    for (i = 0; i < map->warp_points.size; i++) {
        warp_point = &map->warp_points.arr[i];
        if (warp_point->warp_to_map_handle == 0) {
            move_options.check_unit_collissions = false;
            move_options.warp_point_handle = i;
            void_mfunc_Unit_move_to_UnitPtr_GamePtr_SDL_PointPtr_TweenType_MoveOptionsPtr(ct_stacktrace, 105, 623, self, game, &warp_point->tile_point_move_grid, TweenType_UnitMoveToWarpPoint, &move_options);
                        ct_stacktrace_pop(ct_stacktrace);
return;
    }
}
    printf("%s\n", "Unit.move_to_overworld_warp_point. No overworld warp point found.");
    ct_stacktrace_push(ct_stacktrace, 105, 626);
    ct_stacktrace_print(ct_stacktrace);
    exit(1);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Unit_merchant_get_sellable_items_from_guild_UnitPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game) {
    InventorySlot* slot = NULL;
    int i = 0;
    Guild* guild = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->guild_handle < 0 || self->guild_handle > game->world.guilds.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->guild_handle, game->world.guilds.size);
            ct_stacktrace_push(ct_stacktrace, 108, 449);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        guild = &game->world.guilds.arr[self->guild_handle];
    for (i = 0; i < guild->inventory.slots.size; i++) {
        slot = &guild->inventory.slots.arr[i];
        if (slot->slot_is_empty) {
            continue;
}
        if (slot->shared_item.item->item_type != ItemType_Useable) {
            continue;
}
        void_mfunc_Inventory_add_item_InventoryPtr_GamePtr_ItemName_int(ct_stacktrace, 108, 460, &self->inventory, game, slot->shared_item.item->item_name, slot->shared_item.quantity);
        void_mfunc_Inventory_clear_slot_InventoryPtr_int(ct_stacktrace, 108, 463, &guild->inventory, i);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Unit_move_to_setup_merchant_shop_UnitPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game) {
    MoveOptions move_options = {0};
    SDL_Point random_merchant_shop_point = {0};
    Map* map = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->map_handle < 0 || self->map_handle > game->world.maps.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->map_handle, game->world.maps.size);
            ct_stacktrace_push(ct_stacktrace, 110, 587);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        map = &game->world.maps.arr[self->map_handle];
    if (!(map->is_town_map)) {
        printf("%s\n", "Unit.move_to_setup_merchant_shop Not in a town map.");
        ct_stacktrace_push(ct_stacktrace, 110, 590);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    random_merchant_shop_point = SDL_Point_mfunc_Map_get_random_merchant_shop_point_MapPtr_GamePtr_SDL_RectPtr(ct_stacktrace, 110, 591, map, game, &self->tile_point_hit_box);
    move_options.check_unit_collissions = false;
    move_options.warp_point_handle = 0;
    void_mfunc_Unit_move_to_UnitPtr_GamePtr_SDL_PointPtr_TweenType_MoveOptionsPtr(ct_stacktrace, 110, 595, self, game, &random_merchant_shop_point, TweenType_UnitMoveToSetupMerchantShop, &move_options);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Unit_give_items_to_guild_UnitPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game) {
    InventorySlot* slot = NULL;
    int i = 0;
    Guild* guild = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->guild_handle < 0 || self->guild_handle > game->world.guilds.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->guild_handle, game->world.guilds.size);
            ct_stacktrace_push(ct_stacktrace, 111, 433);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        guild = &game->world.guilds.arr[self->guild_handle];
    for (i = 0; i < self->inventory.slots.size; i++) {
        slot = &self->inventory.slots.arr[i];
        if (slot->slot_is_empty) {
            continue;
}
        if (slot->shared_item.item->item_type == ItemType_Misc) {
            continue;
}
        void_mfunc_Inventory_add_item_InventoryPtr_GamePtr_ItemName_int(ct_stacktrace, 111, 443, &guild->inventory, game, slot->shared_item.item->item_name, slot->shared_item.quantity);
        void_mfunc_Inventory_clear_slot_InventoryPtr_int(ct_stacktrace, 111, 446, &self->inventory, i);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Unit_move_to_shop_UnitPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game) {
    Map* map = NULL;
    Building* building = NULL;
    MoveOptions move_options = {0};
    int i = 0;
    int building_handle = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->map_handle < 0 || self->map_handle > game->world.maps.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->map_handle, game->world.maps.size);
            ct_stacktrace_push(ct_stacktrace, 112, 570);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        map = &game->world.maps.arr[self->map_handle];
    if (!(map->is_town_map)) {
        printf("%s\n", "Unit.move_to_shop. Not in a town map.");
        ct_stacktrace_push(ct_stacktrace, 112, 574);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    for (i = 0; i < map->building_handles.size; i += 1) {
        if (i < 0 || i > map->building_handles.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, map->building_handles.size);
                ct_stacktrace_push(ct_stacktrace, 112, 576);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            building_handle = map->building_handles.arr[i];
        if (building_handle < 0 || building_handle > game->world.buildings.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", building_handle, game->world.buildings.size);
                ct_stacktrace_push(ct_stacktrace, 112, 577);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            building = &game->world.buildings.arr[building_handle];
        if (building->is_shop) {
            move_options.check_unit_collissions = false;
            move_options.warp_point_handle = 0;
            void_mfunc_Unit_move_to_UnitPtr_GamePtr_SDL_PointPtr_TweenType_MoveOptionsPtr(ct_stacktrace, 112, 581, self, game, &building->door_tile_point, TweenType_UnitMoveToShop, &move_options);
                        ct_stacktrace_pop(ct_stacktrace);
return;
    }
}
    printf("%s\n", "Unit.move_to_shop No shop found.");
    ct_stacktrace_push(ct_stacktrace, 112, 584);
    ct_stacktrace_print(ct_stacktrace);
    exit(1);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Unit_move_to_random_town_point_UnitPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game) {
    MoveOptions move_options = {0};
    Map* map = NULL;
    int unit_name_as_int = 0;
    int faction_as_int = 0;
    SDL_Point rand_tile_point = {0};

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->map_handle < 0 || self->map_handle > game->world.maps.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->map_handle, game->world.maps.size);
            ct_stacktrace_push(ct_stacktrace, 115, 537);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        map = &game->world.maps.arr[self->map_handle];
    if (!(map->is_town_map)) {
        unit_name_as_int = (int)(self->unit_name);
        faction_as_int = (int)(self->faction);
        printf("%s %d %s %d %s %d %s %d\n", "Unit.move_to_random_town_point. Not in a town map. handle:", self->handle, "\nmap handle:", self->map_handle, "\nunit_name:", unit_name_as_int, "\nfaction:", faction_as_int);
        ct_stacktrace_push(ct_stacktrace, 115, 542);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    self->sprite.anim_state = UnitAnimState_Idle;
    self->ai_state = UnitAIState_RandomTownMove;
    rand_tile_point = SDL_Point_mfunc_Map_get_random_town_point_MapPtr_GamePtr_SDL_RectPtr(ct_stacktrace, 115, 546, map, game, &self->tile_point_hit_box);
    move_options.check_unit_collissions = false;
    move_options.warp_point_handle = 0;
    void_mfunc_Unit_move_to_UnitPtr_GamePtr_SDL_PointPtr_TweenType_MoveOptionsPtr(ct_stacktrace, 115, 550, self, game, &rand_tile_point, TweenType_UnitRandomTownMove, &move_options);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Unit_set_spawn_point_UnitPtr_GamePtr_SDL_PointPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game, SDL_Point* spawn_move_tile_point) {
    SDL_Point world_point = {0};

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    world_point = SDL_Point_tile_point_to_world_point_SDL_PointPtr_SDL_PointPtr(ct_stacktrace, 116, 384, spawn_move_tile_point, &game->move_grid_tile_size);
    self->tile_point_hit_box.x = spawn_move_tile_point->x;
    self->tile_point_hit_box.y = spawn_move_tile_point->y;
    self->sprite.render_dst.dst.x = world_point.x;
    self->sprite.render_dst.dst.y = world_point.y;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Unit_move_to_town_warp_point_UnitPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game) {
    WarpPoint* warp_point = NULL;
    int i = 0;
    MoveOptions move_options = {0};
    Map* map = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->map_handle < 0 || self->map_handle > game->world.maps.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->map_handle, game->world.maps.size);
            ct_stacktrace_push(ct_stacktrace, 117, 629);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        map = &game->world.maps.arr[self->map_handle];
    for (i = 0; i < map->warp_points.size; i++) {
        warp_point = &map->warp_points.arr[i];
        if (warp_point->warp_to_map_handle == 2) {
            move_options.check_unit_collissions = false;
            move_options.warp_point_handle = i;
            void_mfunc_Unit_move_to_UnitPtr_GamePtr_SDL_PointPtr_TweenType_MoveOptionsPtr(ct_stacktrace, 117, 636, self, game, &warp_point->tile_point_move_grid, TweenType_UnitMoveToWarpPoint, &move_options);
                        ct_stacktrace_pop(ct_stacktrace);
return;
    }
}
    printf("%s\n", "Unit.move_to_town_warp_point. No town warp point found.");
    ct_stacktrace_push(ct_stacktrace, 117, 639);
    ct_stacktrace_print(ct_stacktrace);
    exit(1);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Unit_move_to_guild_building_UnitPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game) {
    Map* map = NULL;
    Building* building = NULL;
    MoveOptions move_options = {0};
    int i = 0;
    int building_handle = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->map_handle < 0 || self->map_handle > game->world.maps.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->map_handle, game->world.maps.size);
            ct_stacktrace_push(ct_stacktrace, 118, 553);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        map = &game->world.maps.arr[self->map_handle];
    if (!(map->is_town_map)) {
        printf("%s\n", "Unit.move_to_shopt. Not in a town map.");
        ct_stacktrace_push(ct_stacktrace, 118, 557);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    for (i = 0; i < map->building_handles.size; i += 1) {
        if (i < 0 || i > map->building_handles.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, map->building_handles.size);
                ct_stacktrace_push(ct_stacktrace, 118, 559);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            building_handle = map->building_handles.arr[i];
        if (building_handle < 0 || building_handle > game->world.buildings.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", building_handle, game->world.buildings.size);
                ct_stacktrace_push(ct_stacktrace, 118, 560);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            building = &game->world.buildings.arr[building_handle];
        if (building->building_type == BuildingType_League) {
            move_options.check_unit_collissions = false;
            move_options.warp_point_handle = 0;
            void_mfunc_Unit_move_to_UnitPtr_GamePtr_SDL_PointPtr_TweenType_MoveOptionsPtr(ct_stacktrace, 118, 564, self, game, &building->door_tile_point, TweenType_UnitMoveToGuildBuilding, &move_options);
                        ct_stacktrace_pop(ct_stacktrace);
return;
    }
}
    printf("%s\n", "Unit.move_to_guild_building. No guild building found.");
    ct_stacktrace_push(ct_stacktrace, 118, 567);
    ct_stacktrace_print(ct_stacktrace);
    exit(1);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Unit_move_to_battle_warp_point_UnitPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game) {
    WarpPoint* warp_point = NULL;
    int i = 0;
    Map* map = NULL;
    MoveOptions move_options = {0};

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->battle_map_handle == -1) {
        printf("%s\n", "Unit.move_to_battle_warp_piont. battle_map_handle is -1.");
        ct_stacktrace_push(ct_stacktrace, 119, 644);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    if (self->map_handle < 0 || self->map_handle > game->world.maps.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->map_handle, game->world.maps.size);
            ct_stacktrace_push(ct_stacktrace, 119, 645);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        map = &game->world.maps.arr[self->map_handle];
    for (i = 0; i < map->warp_points.size; i++) {
        warp_point = &map->warp_points.arr[i];
        if (warp_point->warp_to_map_handle == self->battle_map_handle) {
            move_options.check_unit_collissions = false;
            move_options.warp_point_handle = i;
            void_mfunc_Unit_move_to_UnitPtr_GamePtr_SDL_PointPtr_TweenType_MoveOptionsPtr(ct_stacktrace, 119, 652, self, game, &warp_point->tile_point_move_grid, TweenType_UnitMoveToWarpPoint, &move_options);
                        ct_stacktrace_pop(ct_stacktrace);
return;
    }
}
    printf("%s %d\n", "Unit.move_to_battle_warp_point. No battle warp point found. Battle map handle:", self->battle_map_handle);
    ct_stacktrace_push(ct_stacktrace, 119, 655);
    ct_stacktrace_print(ct_stacktrace);
    exit(1);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Unit_merchant_sell_to_unit_UnitPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game) {
    Guild* guild = NULL;
    Uint64 cost = 0;
    int i = 0;
    InventorySlot* slot = NULL;
    int quantity = 0;
    int total_cost = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->guild_handle < 0 || self->guild_handle > game->world.guilds.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->guild_handle, game->world.guilds.size);
            ct_stacktrace_push(ct_stacktrace, 121, 485);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        guild = &game->world.guilds.arr[self->guild_handle];
    for (i = 0; i < self->inventory.slots.size; i++) {
        slot = &self->inventory.slots.arr[i];
        if (slot->slot_is_empty) {
            continue;
}
        if (slot->shared_item.item->item_type != ItemType_Useable) {
            continue;
}
        cost = slot->shared_item.item->cost;
        quantity = slot->shared_item.quantity;
        total_cost = (cost * quantity);
        guild->current_money += total_cost;
        guild->total_money_earned += total_cost;
        void_mfunc_Inventory_clear_slot_InventoryPtr_int(ct_stacktrace, 121, 501, &self->inventory, i);
        break;
}
    if (bool_mfunc_Inventory_inventory_is_empty_InventoryPtr(ct_stacktrace, 121, 506, &self->inventory)) {
        void_mfunc_Unit_move_to_random_town_point_UnitPtr_GamePtr(ct_stacktrace, 121, 507, self, game);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Unit_on_hit_UnitPtr_GamePtr_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game, int hit_by_unit_handle) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if ((self->faction == Faction_Enemy && self->aggro_towards_unit_handle == -1)) {
        self->aggro_towards_unit_handle = hit_by_unit_handle;
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Unit_do_item_drops_UnitPtr_GamePtr_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game, int target_unit_handle) {
    Uint32 duration = 0;
    Uint32 delay = 0;
    Map* map = NULL;
    int tween_handle = 0;
    int i = 0;
    SharedItem* item_drop = NULL;
    TweenCallback callback = {0};
    int item_handle = 0;
    SharedItem* item = NULL;
    int rand_int = 0;
    Unit* target_unit = NULL;
    SDL_Rect start_rect = {0};
    TweenXY* tween = NULL;
    SDL_Rect* target_rect_ptr = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (target_unit_handle < 0 || target_unit_handle > game->world.units.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", target_unit_handle, game->world.units.size);
            ct_stacktrace_push(ct_stacktrace, 127, 714);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        target_unit = &game->world.units.arr[target_unit_handle];
    for (i = 0; i < self->item_drops.size; i++) {
        item_drop = &self->item_drops.arr[i];
        rand_int = int_mfunc_Engine_get_rand_int_EnginePtr_int_int(ct_stacktrace, 127, 716, &game->engine, 0, 100);
        if (rand_int < item_drop->drop_chance) {
            if (self->map_handle < 0 || self->map_handle > game->world.maps.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", self->map_handle, game->world.maps.size);
                    ct_stacktrace_push(ct_stacktrace, 127, 718);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                map = &game->world.maps.arr[self->map_handle];
            item_handle = int_mfunc_World_get_handle_WorldPtr_HandleType(ct_stacktrace, 127, 719, &game->world, HandleType_Item);
            if (item_handle < 0 || item_handle > game->world.items.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", item_handle, game->world.items.size);
                    ct_stacktrace_push(ct_stacktrace, 127, 720);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                item = &game->world.items.arr[item_handle];
            void_mfunc_SharedItem_set_to_SharedItemPtr_GamePtr_ItemName_int_int(ct_stacktrace, 127, 723, item, game, item_drop->item->item_name, item_drop->quantity, item_drop->drop_chance);
            void_push_value_Array_int_300Ptr_int(ct_stacktrace, 127, 724, &map->item_handles, item_handle);
            tween_handle = int_mfunc_World_get_handle_WorldPtr_HandleType(ct_stacktrace, 127, 725, &game->world, HandleType_TweenXY);
            if (tween_handle < 0 || tween_handle > game->world.tween_xys.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", tween_handle, game->world.tween_xys.size);
                    ct_stacktrace_push(ct_stacktrace, 127, 726);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                tween = &game->world.tween_xys.arr[tween_handle];
            callback.tween_type = TweenType_ItemDrop;
            callback.handle = item_handle;
            callback.receiving_unit_handle = target_unit_handle;
            callback.map_handle = self->map_handle;
            delay = (Uint32)(0);
            duration = (Uint32)(0);
            start_rect = self->sprite.render_dst.dst;
            target_rect_ptr = &target_unit->sprite.render_dst.dst;
            item->render_dst.dst = start_rect;
            void_mfunc_TweenXY_set_TweenXYPtr_GamePtr_SDL_RectPtr_SDL_RectPtr_SDL_RectPtr_bool_double_Uint32_Uint32_TweenCallbackPtr(ct_stacktrace, 127, 737, tween, game, &start_rect, &item->render_dst.dst, target_rect_ptr, true, 1.5, duration, delay, &callback);
        }
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Unit_on_dead_UnitPtr_GamePtr_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game, int hit_by_unit_handle) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->aggro_towards_unit_handle = -1;
    self->attacked_by_guild_handle = -1;
    self->next_random_move_time = game->engine.current_time;
    self->death_time = game->engine.current_time;
    void_mfunc_Unit_clear_move_tweens_UnitPtr_GamePtr(ct_stacktrace, 128, 367, self, game);
    void_mfunc_Unit_do_item_drops_UnitPtr_GamePtr_int(ct_stacktrace, 128, 370, self, game, hit_by_unit_handle);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Unit_change_to_sell_item_ai_state_UnitPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->ai_state = UnitAIState_Selling;
    self->aggro_towards_unit_handle = -1;
    void_mfunc_Unit_move_to_overworld_warp_point_UnitPtr_GamePtr(ct_stacktrace, 130, 512, self, game);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Unit_update_towns_person_ai_UnitPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game) {
    int a = 0;
    int diff = 0;
    bool success = false;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->unit_type != UnitType_TownsPerson) {
        printf("%s\n", "Unit.update_towns_person_ai. Unit is not a towns person.");
        ct_stacktrace_push(ct_stacktrace, 133, 337);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    if (self->ai_state == UnitAIState_RandomTownMove) {
        if (game->engine.current_time > self->neutral_can_try_buy_again_time) {
            diff = (game->engine.current_time - self->last_try_merchant_buy_time);
            success = false;
            if (diff > 2000) {
                self->last_try_merchant_buy_time = game->engine.current_time;
                success = bool_mfunc_Unit_try_find_and_move_to_merchant_shop_UnitPtr_GamePtr(ct_stacktrace, 133, 344, self, game);
}
            if ((!(success) && self->path_could_not_be_found)) {
                diff = (game->engine.current_time - self->last_failed_path_time);
                if (diff > 200) {
                    void_mfunc_Unit_move_to_random_town_point_UnitPtr_GamePtr(ct_stacktrace, 133, 349, self, game);
            }
        }
    }
}
    else if (self->ai_state == UnitAIState_MovingToBuyAtMerchant) {
        a = 0;
}
    else {
        void_mfunc_Unit_move_to_random_town_point_UnitPtr_GamePtr(ct_stacktrace, 133, 356, self, game);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Unit_update_merchant_ai_UnitPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game) {
    int diff = 0;
    Guild* guild = NULL;
    int a = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (!(bool_mfunc_Unit_is_merchant_UnitPtr(ct_stacktrace, 135, 311, self))) {
        printf("%s\n", "Unit.update_merchant_ai. Unit is not a merchant.");
        ct_stacktrace_push(ct_stacktrace, 135, 313);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    if (self->ai_state == UnitAIState_MerchantRestocking) {
        a = 0;
}
    else if (self->ai_state == UnitAIState_MerchantSelling) {
        a = 0;
}
    else if (self->ai_state == UnitAIState_RandomTownMove) {
        if (self->guild_handle < 0 || self->guild_handle > game->world.guilds.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", self->guild_handle, game->world.guilds.size);
                ct_stacktrace_push(ct_stacktrace, 135, 319);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            guild = &game->world.guilds.arr[self->guild_handle];
        if (bool_mfunc_Inventory_has_merchant_sellable_items_InventoryPtr(ct_stacktrace, 135, 320, &guild->inventory)) {
            self->ai_state = UnitAIState_MerchantRestocking;
            void_mfunc_Unit_move_to_guild_building_UnitPtr_GamePtr(ct_stacktrace, 135, 322, self, game);
}
        else if (self->path_could_not_be_found) {
            diff = (game->engine.current_time - self->last_failed_path_time);
            if (diff > 2000) {
                void_mfunc_Unit_move_to_random_town_point_UnitPtr_GamePtr(ct_stacktrace, 135, 327, self, game);
        }
    }
}
    else {
        void_mfunc_Unit_move_to_random_town_point_UnitPtr_GamePtr(ct_stacktrace, 135, 332, self, game);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

bool bool_mfunc_Unit_is_ally_or_guild_faction_UnitPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
        ct_stacktrace_pop(ct_stacktrace);
return (self->faction == Faction_Ally || self->faction == Faction_Guild);
}

void void_mfunc_Unit_move_towards_tile_point_UnitPtr_GamePtr_SDL_PointPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game, SDL_Point* target_point) {
    Map* map = NULL;
    MoveOptions move_options = {0};
    SDL_Point unit_tile_point = {0};

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->map_handle < 0 || self->map_handle > game->world.maps.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->map_handle, game->world.maps.size);
            ct_stacktrace_push(ct_stacktrace, 139, 740);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        map = &game->world.maps.arr[self->map_handle];
    unit_tile_point = SDL_Point_create_point_int_int(ct_stacktrace, 139, 741, self->tile_point_hit_box.x, self->tile_point_hit_box.y);
    void_mfunc_PathFinder_set_path_PathFinderPtr_GamePtr_MapPtr_UnitPtr_SDL_PointPtr_SDL_PointPtr_bool(ct_stacktrace, 139, 743, &game->world.path_finder, game, map, self, &unit_tile_point, target_point, true);
    move_options.check_unit_collissions = true;
    move_options.warp_point_handle = 0;
    void_mfunc_Unit_move_to_UnitPtr_GamePtr_SDL_PointPtr_TweenType_MoveOptionsPtr(ct_stacktrace, 139, 748, self, game, &game->world.path_finder.closest_point_to_target, TweenType_UnitMove, &move_options);
    ct_stacktrace_pop(ct_stacktrace);
}

int int_mfunc_Unit_closest_opposite_unit_handle_UnitPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game) {
    int dist = 0;
    SDL_Point unit_tile_point = {0};
    Unit* unit = NULL;
    Map* map = NULL;
    int unit_handle = 0;
    int min_dist = 0;
    SDL_Point tile_point = {0};
    int min_dist_unit_handle = 0;
    int i = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->map_handle < 0 || self->map_handle > game->world.maps.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->map_handle, game->world.maps.size);
            ct_stacktrace_push(ct_stacktrace, 140, 394);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        map = &game->world.maps.arr[self->map_handle];
    min_dist = 100000;
    min_dist_unit_handle = -1;
    tile_point = SDL_Point_create_point_int_int(ct_stacktrace, 140, 397, self->tile_point_hit_box.x, self->tile_point_hit_box.y);
    for (i = 0; i < map->unit_handles.size; i += 1) {
        if (i == self->handle) {
            continue;
}
        if (i < 0 || i > map->unit_handles.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, map->unit_handles.size);
                ct_stacktrace_push(ct_stacktrace, 140, 401);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit_handle = map->unit_handles.arr[i];
        if (unit_handle < 0 || unit_handle > game->world.units.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", unit_handle, game->world.units.size);
                ct_stacktrace_push(ct_stacktrace, 140, 402);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit = &game->world.units.arr[unit_handle];
        if (unit->faction == Faction_Neutral) {
            continue;
}
        if (bool_mfunc_Range_value_is_at_min_RangePtr(ct_stacktrace, 140, 406, &unit->stats.hp)) {
            continue;
}
        if ((bool_mfunc_Unit_is_ally_or_guild_faction_UnitPtr(ct_stacktrace, 140, 408, self) && bool_mfunc_Unit_is_ally_or_guild_faction_UnitPtr(ct_stacktrace, 140, 408, unit))) {
            continue;
}
        else if ((self->faction == Faction_Enemy && !(bool_mfunc_Unit_is_ally_or_guild_faction_UnitPtr(ct_stacktrace, 140, 410, unit)))) {
            continue;
}
        else if ((unit->attacked_by_guild_handle != -1 && unit->attacked_by_guild_handle != self->guild_handle)) {
            continue;
}
        unit_tile_point = SDL_Point_create_point_int_int(ct_stacktrace, 140, 415, unit->tile_point_hit_box.x, unit->tile_point_hit_box.y);
        dist = int_manhattan_distance_SDL_PointPtr_SDL_PointPtr(ct_stacktrace, 140, 416, &tile_point, &unit_tile_point);
        if (dist < min_dist) {
            min_dist = dist;
            min_dist_unit_handle = unit_handle;
    }
}
        ct_stacktrace_pop(ct_stacktrace);
return min_dist_unit_handle;
}

SharedAbility* SharedAbilityPtr_mfunc_Unit_get_ai_ability_UnitPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game) {
    int ability_handle = 0;
    AIAbility* ai_ability = NULL;
    int i = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    for (i = 0; i < self->ai_abilities.size; i++) {
        ai_ability = &self->ai_abilities.arr[i];
        if (ai_ability->is_empty) {
            continue;
}
        ability_handle = ai_ability->unit_ability_handle;
        if (ability_handle < 0 || ability_handle > self->abilities.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", ability_handle, self->abilities.size);
                ct_stacktrace_push(ct_stacktrace, 141, 826);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
                    ct_stacktrace_pop(ct_stacktrace);
return &self->abilities.arr[ability_handle];
}
        ct_stacktrace_pop(ct_stacktrace);
return &self->default_attack_ability;
}

void void_mfunc_Unit_perform_ability_UnitPtr_GamePtr_SharedAbilityPtr_Array_int_10Ptr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game, SharedAbility* ability_to_perform, Array_int_10* target_unit_handles) {
    Uint32 duration = 0;
    SDL_Rect start_rect = {0};
    int ability_duration = 0;
    Uint32 ability_anim_speed = 0;
    int ability_srcs_size = 0;
    TweenCallback callback = {0};
    int i = 0;
    Map* map = NULL;
    int tween_handle = 0;
    TweenXY* tween = NULL;
    int target_unit_handle = 0;
    Unit* target_unit = NULL;
    int ability_handle = 0;
    SharedAbility* ability = NULL;
    SDL_Rect* target_rect_ptr = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->map_handle < 0 || self->map_handle > game->world.maps.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->map_handle, game->world.maps.size);
            ct_stacktrace_push(ct_stacktrace, 142, 677);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        map = &game->world.maps.arr[self->map_handle];
    void_mfunc_UnitSprite_play_animation_UnitSpritePtr_GamePtr_UnitAnimState(ct_stacktrace, 142, 678, &self->sprite, game, UnitAnimState_Cast);
    for (i = 0; i < target_unit_handles->size; i += 1) {
        if (i < 0 || i > target_unit_handles->size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, target_unit_handles->size);
                ct_stacktrace_push(ct_stacktrace, 142, 680);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            target_unit_handle = target_unit_handles->arr[i];
        if (target_unit_handle < 0 || target_unit_handle > game->world.units.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", target_unit_handle, game->world.units.size);
                ct_stacktrace_push(ct_stacktrace, 142, 681);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            target_unit = &game->world.units.arr[target_unit_handle];
        ability_handle = int_mfunc_World_get_handle_WorldPtr_HandleType(ct_stacktrace, 142, 682, &game->world, HandleType_Ability);
        if (ability_handle < 0 || ability_handle > game->world.abilities.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", ability_handle, game->world.abilities.size);
                ct_stacktrace_push(ct_stacktrace, 142, 683);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            ability = &game->world.abilities.arr[ability_handle];
        void_mfunc_SharedAbility_set_to_SharedAbilityPtr_GamePtr_AbilityName(ct_stacktrace, 142, 684, ability, game, ability_to_perform->ability->ability_name);
        void_push_value_Array_int_300Ptr_int(ct_stacktrace, 142, 685, &map->ability_handles, ability_handle);
        tween_handle = int_mfunc_World_get_handle_WorldPtr_HandleType(ct_stacktrace, 142, 686, &game->world, HandleType_TweenXY);
        if (tween_handle < 0 || tween_handle > game->world.tween_xys.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", tween_handle, game->world.tween_xys.size);
                ct_stacktrace_push(ct_stacktrace, 142, 687);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            tween = &game->world.tween_xys.arr[tween_handle];
        callback.tween_type = TweenType_PerformAbility;
        callback.handle = ability_handle;
        callback.handle_type = HandleType_Ability;
        callback.acting_unit_handle = self->handle;
        callback.receiving_unit_handle = target_unit_handle;
        callback.map_handle = self->map_handle;
        ability_srcs_size = ability->ability->sprite.srcs.size;
        ability_anim_speed = ability->ability->sprite.anim_speed;
        ability_duration = (ability_srcs_size * ability_anim_speed);
        duration = (Uint32)(ability_duration);
        start_rect = self->sprite.render_dst.dst;
        target_rect_ptr = &target_unit->sprite.render_dst.dst;
        start_rect.x += ability->ability->start_offset.x;
        start_rect.y += ability->ability->start_offset.y;
        if (!(ability->ability->is_projectile)) {
            start_rect = *target_rect_ptr;
}
        ability->render_dst.dst = start_rect;
        void_mfunc_TweenXY_set_TweenXYPtr_GamePtr_SDL_RectPtr_SDL_RectPtr_SDL_RectPtr_bool_double_Uint32_Uint32_TweenCallbackPtr(ct_stacktrace, 142, 711, tween, game, &start_rect, &ability->render_dst.dst, target_rect_ptr, ability->ability->is_projectile, ability->ability->projectile_speed, duration, ability->ability->delay, &callback);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Unit_update_ai_UnitPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game) {
    Array_int_10 receiving_units = {0};
    SDL_Point aggro_unit_tile_point = {0};
    Unit* aggro_unit = NULL;
    int dist = 0;
    SDL_Point target_unit_tile_point = {0};
    Unit* target_unit = NULL;
    SharedAbility* ability = NULL;
    SDL_Point rand_tile_point = {0};
    int rand_y = 0;
    int rand_x = 0;
    Uint32 rand_move_delay = 0;
    Uint32 last_move_calc_diff = 0;
    double sit_pct = 0.0;
    Uint32 death_time_diff = 0;
    SDL_Point tile_point = {0};
    Uint32 rand_interval_u32 = 0;
    Uint32 last_attack_diff = 0;
    int rand_interval = 0;
    Map* map = NULL;
    int max_x = 0;
    Uint64 sit_heal_value = 0;
    int min_y = 0;
    int random_move_dist = 0;
    int min_x = 0;
    int max_y = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (bool_mfunc_Unit_is_merchant_UnitPtr(ct_stacktrace, 143, 221, self)) {
        printf("%s\n", "Unit.update_ai. Unit is a merchant. This ai is only for non-merchants.");
        ct_stacktrace_push(ct_stacktrace, 143, 223);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    if (self->ai_state == UnitAIState_Battle) {
        if (bool_mfunc_Range_value_is_at_min_RangePtr(ct_stacktrace, 143, 227, &self->stats.hp)) {
            death_time_diff = (Uint32)((game->engine.current_time - self->death_time));
            if (death_time_diff > self->respawn_time) {
                self->is_sitting = false;
                void_mfunc_Range_set_to_max_RangePtr(ct_stacktrace, 143, 232, &self->stats.hp);
                void_mfunc_UnitSprite_play_animation_UnitSpritePtr_GamePtr_UnitAnimState(ct_stacktrace, 143, 234, &self->sprite, game, UnitAnimState_Idle);
                rand_move_delay = (Uint32)(400);
                self->next_random_move_time = (game->engine.current_time + rand_move_delay);
                void_mfunc_Unit_set_random_spawn_point_UnitPtr_GamePtr(ct_stacktrace, 143, 239, self, game);
}
                        ct_stacktrace_pop(ct_stacktrace);
return;
}
        sit_pct = 0.4;
        if ((((!(self->is_sitting) && self->faction != Faction_Enemy) && double_mfunc_Range_value_pct_of_max_RangePtr(ct_stacktrace, 143, 243, &self->stats.hp) <= sit_pct) && self->aggro_towards_unit_handle == -1)) {
            self->is_sitting = true;
            void_mfunc_UnitSprite_play_animation_UnitSpritePtr_GamePtr_UnitAnimState(ct_stacktrace, 143, 245, &self->sprite, game, UnitAnimState_Sit);
                        ct_stacktrace_pop(ct_stacktrace);
return;
}
        else if (self->is_sitting) {
            if ((game->engine.current_time - self->last_sit_heal_time) > 2000) {
                self->last_sit_heal_time = game->engine.current_time;
                sit_heal_value = (Uint64)((0.1 * self->stats.hp.max));
                void_mfunc_Range_inc_RangePtr_Uint64(ct_stacktrace, 143, 251, &self->stats.hp, sit_heal_value);
                if (bool_mfunc_Range_value_is_at_max_RangePtr(ct_stacktrace, 143, 253, &self->stats.hp)) {
                    self->is_sitting = false;
                    void_mfunc_UnitSprite_play_animation_UnitSpritePtr_GamePtr_UnitAnimState(ct_stacktrace, 143, 255, &self->sprite, game, UnitAnimState_Idle);
    }
}
                        ct_stacktrace_pop(ct_stacktrace);
return;
}
        tile_point = SDL_Point_create_point_int_int(ct_stacktrace, 143, 258, self->tile_point_hit_box.x, self->tile_point_hit_box.y);
        last_move_calc_diff = (Uint32)((game->engine.current_time - self->last_move_calc_time));
        last_attack_diff = (Uint32)((game->engine.current_time - self->last_attack_time));
        if (((!(bool_mfunc_Unit_is_ally_or_guild_faction_UnitPtr(ct_stacktrace, 143, 262, self)) && self->aggro_towards_unit_handle == -1) && game->engine.current_time > self->next_random_move_time)) {
            rand_interval = int_mfunc_Engine_get_rand_int_EnginePtr_int_int(ct_stacktrace, 143, 263, &game->engine, 1000, 5000);
            rand_interval_u32 = (Uint32)(rand_interval);
            self->next_random_move_time = (game->engine.current_time + rand_interval_u32);
            if (self->map_handle < 0 || self->map_handle > game->world.maps.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", self->map_handle, game->world.maps.size);
                    ct_stacktrace_push(ct_stacktrace, 143, 266);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                map = &game->world.maps.arr[self->map_handle];
            random_move_dist = 20;
            min_x = (self->tile_point_hit_box.x - random_move_dist);
            max_x = (self->tile_point_hit_box.x + random_move_dist);
            min_y = (self->tile_point_hit_box.y - random_move_dist);
            max_y = (self->tile_point_hit_box.y + random_move_dist);
            if (min_x < 0) {
                min_x = 0;
}
            if (max_x > (map->move_grid_rows - 1)) {
                max_x = (map->move_grid_rows - 1);
}
            if (min_y < 0) {
                min_y = 0;
}
            if (max_y > (map->move_grid_cols - 1)) {
                max_y = (map->move_grid_cols - 1);
}
            rand_x = int_mfunc_Engine_get_rand_int_EnginePtr_int_int(ct_stacktrace, 143, 280, &game->engine, min_x, max_x);
            rand_y = int_mfunc_Engine_get_rand_int_EnginePtr_int_int(ct_stacktrace, 143, 281, &game->engine, min_y, max_y);
            rand_tile_point = SDL_Point_create_point_int_int(ct_stacktrace, 143, 282, rand_x, rand_y);
            void_mfunc_Unit_move_towards_tile_point_UnitPtr_GamePtr_SDL_PointPtr(ct_stacktrace, 143, 283, self, game, &rand_tile_point);
}
        else if (((bool_mfunc_Unit_is_ally_or_guild_faction_UnitPtr(ct_stacktrace, 143, 284, self) || self->aggro_nearest_unit) && self->aggro_towards_unit_handle == -1)) {
            self->aggro_towards_unit_handle = int_mfunc_Unit_closest_opposite_unit_handle_UnitPtr_GamePtr(ct_stacktrace, 143, 285, self, game);
}
        else if (self->aggro_towards_unit_handle != -1) {
            if (self->aggro_towards_unit_handle < 0 || self->aggro_towards_unit_handle > game->world.units.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", self->aggro_towards_unit_handle, game->world.units.size);
                    ct_stacktrace_push(ct_stacktrace, 143, 287);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                target_unit = &game->world.units.arr[self->aggro_towards_unit_handle];
            if (bool_mfunc_Range_value_is_at_min_RangePtr(ct_stacktrace, 143, 290, &target_unit->stats.hp)) {
                self->aggro_towards_unit_handle = -1;
                                ct_stacktrace_pop(ct_stacktrace);
return;
}
            target_unit_tile_point = SDL_Point_create_point_int_int(ct_stacktrace, 143, 293, target_unit->tile_point_hit_box.x, target_unit->tile_point_hit_box.y);
            dist = int_manhattan_distance_SDL_PointPtr_SDL_PointPtr(ct_stacktrace, 143, 294, &tile_point, &target_unit_tile_point);
            ability = SharedAbilityPtr_mfunc_Unit_get_ai_ability_UnitPtr_GamePtr(ct_stacktrace, 143, 296, self, game);
            if ((dist > ability->ability->stats.range && last_move_calc_diff > 1300)) {
                self->last_move_calc_time = game->engine.current_time;
                if (self->aggro_towards_unit_handle < 0 || self->aggro_towards_unit_handle > game->world.units.size - 1) {
                        printf("Out of bounds error: idx: %d size: %d.\n", self->aggro_towards_unit_handle, game->world.units.size);
                        ct_stacktrace_push(ct_stacktrace, 143, 299);
                        ct_stacktrace_print(ct_stacktrace);
                        exit(1);
                    }
                    aggro_unit = &game->world.units.arr[self->aggro_towards_unit_handle];
                aggro_unit_tile_point = SDL_Point_create_point_int_int(ct_stacktrace, 143, 300, aggro_unit->tile_point_hit_box.x, aggro_unit->tile_point_hit_box.y);
                void_mfunc_Unit_move_towards_tile_point_UnitPtr_GamePtr_SDL_PointPtr(ct_stacktrace, 143, 301, self, game, &aggro_unit_tile_point);
}
            else if ((dist <= ability->ability->stats.range && last_attack_diff > self->stats.attack_speed.value)) {
                void_mfunc_Unit_clear_move_tweens_UnitPtr_GamePtr(ct_stacktrace, 143, 304, self, game);
                self->last_attack_time = game->engine.current_time;
                void_push_value_Array_int_10Ptr_int(ct_stacktrace, 143, 307, &receiving_units, self->aggro_towards_unit_handle);
                void_mfunc_Unit_perform_ability_UnitPtr_GamePtr_SharedAbilityPtr_Array_int_10Ptr(ct_stacktrace, 143, 308, self, game, ability, &receiving_units);
            }
        }
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Unit_update_UnitPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game) {
    Guild* guild = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->unit_type == UnitType_TownsPerson) {
        void_mfunc_Unit_update_towns_person_ai_UnitPtr_GamePtr(ct_stacktrace, 154, 107, self, game);
}
    else if (bool_mfunc_Unit_is_merchant_UnitPtr(ct_stacktrace, 154, 108, self)) {
        void_mfunc_Unit_update_merchant_ai_UnitPtr_GamePtr(ct_stacktrace, 154, 109, self, game);
}
    else {
        void_mfunc_Unit_update_ai_UnitPtr_GamePtr(ct_stacktrace, 154, 111, self, game);
}
    void_mfunc_UnitSprite_update_UnitSpritePtr_GamePtr_bool(ct_stacktrace, 154, 114, &self->sprite, game, self->map_handle == 0);
    if (self->guild_handle < 0 || self->guild_handle > game->world.guilds.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->guild_handle, game->world.guilds.size);
            ct_stacktrace_push(ct_stacktrace, 154, 115);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        guild = &game->world.guilds.arr[self->guild_handle];
    self->guild_icon.render_dst.dst = self->sprite.render_dst.dst;
    self->guild_icon.render_dst.dst.x -= 14;
    if (self->ai_state == UnitAIState_MerchantSelling) {
        self->guild_icon.render_dst.dst.y += 42;
}
    else {
        self->guild_icon.render_dst.dst.y -= 18;
}
    void_mfunc_UISprite_update_UISpritePtr_GamePtr(ct_stacktrace, 154, 124, &self->guild_icon, game);
    if (guild->is_anonymous) {
        self->display_name_text.render_dst.dst = self->sprite.render_dst.dst;
        self->display_name_text.render_dst.dst.x -= 5;
        if (self->ai_state == UnitAIState_MerchantSelling) {
            self->display_name_text.render_dst.dst.y += 42;
}
        else {
            self->display_name_text.render_dst.dst.y -= 13;
    }
}
    else {
        self->display_name_text.render_dst.dst = self->guild_icon.render_dst.dst;
        self->display_name_text.render_dst.dst.x += 18;
        self->display_name_text.render_dst.dst.y -= 2;
}
    void_text_update_TextLGPtr_GamePtr(ct_stacktrace, 154, 136, &self->display_name_text, game);
    self->guild_display_name_text.render_dst.dst = self->display_name_text.render_dst.dst;
    self->guild_display_name_text.render_dst.dst.y += 10;
    void_text_update_TextLGPtr_GamePtr(ct_stacktrace, 154, 139, &self->guild_display_name_text, game);
    self->merchant_shop_background.render_dst.dst = self->sprite.render_dst.dst;
    self->merchant_shop_background.render_dst.dst.x -= 30;
    self->merchant_shop_background.render_dst.dst.y -= 20;
    self->merchant_shop_text.render_dst.dst = self->merchant_shop_background.render_dst.dst;
    self->merchant_shop_text.render_dst.dst.x += 19;
    self->merchant_shop_text.render_dst.dst.y += 5;
    void_mfunc_UISprite_update_UISpritePtr_GamePtr(ct_stacktrace, 154, 149, &self->merchant_shop_background, game);
    void_text_update_TextLGPtr_GamePtr(ct_stacktrace, 154, 150, &self->merchant_shop_text, game);
    ct_stacktrace_pop(ct_stacktrace);
}

int int_mfunc_Unit_get_ability_skill_points_UnitPtr_AbilityName(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, AbilityName ability_name) {
    SharedAbility* ability = NULL;
    int i = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    for (i = 0; i < self->abilities.size; i++) {
        ability = &self->abilities.arr[i];
        if (ability->ability->ability_name == ability_name) {
                        ct_stacktrace_pop(ct_stacktrace);
return ability->skill_points;
    }
}
        ct_stacktrace_pop(ct_stacktrace);
return 0;
}

SharedAbility* SharedAbilityPtr_mfunc_Unit_get_ability_UnitPtr_AbilityName(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, AbilityName ability_name) {
    int ability_name_as_int = 0;
    SharedAbility* ability = NULL;
    int i = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    for (i = 0; i < self->abilities.size; i++) {
        ability = &self->abilities.arr[i];
        if (ability->ability->ability_name == ability_name) {
                        ct_stacktrace_pop(ct_stacktrace);
return ability;
    }
}
    ability_name_as_int = (int)(ability_name);
    printf("%s %d\n", "Unit.get_ability. ability not found. AbilityName:", ability_name_as_int);
    ct_stacktrace_push(ct_stacktrace, 188, 807);
    ct_stacktrace_print(ct_stacktrace);
    exit(1);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Unit_draw_UnitPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game) {
    Guild* guild = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->inside_building) {
                ct_stacktrace_pop(ct_stacktrace);
return;
}
    void_mfunc_UnitSprite_draw_UnitSpritePtr_GamePtr(ct_stacktrace, 204, 155, &self->sprite, game);
    void_text_draw_TextLGPtr_GamePtr(ct_stacktrace, 204, 156, &self->display_name_text, game);
    if (self->guild_handle < 0 || self->guild_handle > game->world.guilds.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->guild_handle, game->world.guilds.size);
            ct_stacktrace_push(ct_stacktrace, 204, 157);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        guild = &game->world.guilds.arr[self->guild_handle];
    if (self->faction != Faction_Enemy) {
        if (!(guild->is_anonymous)) {
            void_mfunc_UISprite_draw_UISpritePtr_GamePtr(ct_stacktrace, 204, 160, &self->guild_icon, game);
            void_text_draw_TextLGPtr_GamePtr(ct_stacktrace, 204, 161, &self->guild_display_name_text, game);
    }
}
    if ((bool_mfunc_Unit_is_merchant_UnitPtr(ct_stacktrace, 204, 162, self) && self->ai_state == UnitAIState_MerchantSelling)) {
        void_mfunc_UISprite_draw_UISpritePtr_GamePtr(ct_stacktrace, 204, 163, &self->merchant_shop_background, game);
        void_text_draw_TextLGPtr_GamePtr(ct_stacktrace, 204, 164, &self->merchant_shop_text, game);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Unit_draw_idle_at_UnitPtr_GamePtr_SDL_RectPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, Game* game, SDL_Rect* unscaled_dst) {
    SDL_Rect* idle_src_0 = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (0 < 0 || 0 > self->sprite.idle_down.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", 0, self->sprite.idle_down.size);
            ct_stacktrace_push(ct_stacktrace, 210, 168);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        idle_src_0 = &self->sprite.idle_down.arr[0];
    unscaled_dst->w = idle_src_0->w;
    unscaled_dst->h = idle_src_0->h;
    void_set_scaled_rect_SDL_RectPtr_int(ct_stacktrace, 210, 171, unscaled_dst, game->engine.scale);
    SDL_RenderCopy(game->engine.renderer, self->sprite.image.texture, idle_src_0, unscaled_dst);
    ct_stacktrace_pop(ct_stacktrace);
}

