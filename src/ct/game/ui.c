#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "ct_stacktrace.h"
#include "ui.h"
#include "engine.h"
#include "image.h"
#include "input_events.h"
#include "utils.h"
#include "image.h"
#include "ct_array.h"
#include "constants.h"
#include "input_events.h"
#include "ui_sprite.h"
#include "text.h"
#include "ui_containers.h"
#include "game.h"
#include "unit.h"

void void_mfunc_UI_init_UIPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UI* self, Game* game) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    void_mfunc_TopNav_init_TopNavPtr_GamePtr(ct_stacktrace, 39, 27, &self->top_nav, game);
    void_mfunc_RecruitNoviceModal_init_RecruitNoviceModalPtr_GamePtr(ct_stacktrace, 39, 28, &self->recruit_novice_modal, game);
    void_mfunc_GuildWindow_init_GuildWindowPtr_GamePtr(ct_stacktrace, 39, 29, &self->guild_window, game);
    void_mfunc_UnitsWindow_init_UnitsWindowPtr_GamePtr(ct_stacktrace, 39, 30, &self->units_window, game);
    void_mfunc_MerchantsWindow_init_MerchantsWindowPtr_GamePtr(ct_stacktrace, 39, 31, &self->merchants_window, game);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_UI_clear_UIPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UI* self) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    void_clear_Array_UIRenderable_300Ptr(ct_stacktrace, 81, 34, &self->renderables);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_UI_on_click_UIPtr_GamePtr_UIEventPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UI* self, Game* game, UIEvent* ui_event) {
    Unit* unit = NULL;
    UnitName unit_name = (UnitName) 0;
    int handle = 0;
    int stat_cost = 0;
    Map* map = NULL;
    SharedAbility* job_ability = NULL;
    Guild* guild = NULL;
    bool opposite_visible_state = false;
    Guild* player_guild = NULL;
    int unit_handle = 0;
    int ability_handle = 0;
    int guild_unit_idx = 0;
    int guild_handle = 0;
    SharedAbility* ability = NULL;
    StatName stat_name = (StatName) 0;
    Uint64 inc_val = 0;
    int ai_ability_handle = 0;
    AIAbility* ai_ability = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->on_click_fired_this_frame = true;
    if (ui_event->event_name == UIEventName_BuyRecruitModal) {
                ct_stacktrace_pop(ct_stacktrace);
return;
}
    else if (ui_event->event_name == UIEventName_BuyRecruitBackdrop) {
        void_mfunc_RecruitNoviceModal_set_visible_RecruitNoviceModalPtr_bool(ct_stacktrace, 191, 100, &self->recruit_novice_modal, false);
}
    else if (ui_event->event_name == UIEventName_BuyRecruitClose) {
        void_mfunc_RecruitNoviceModal_set_visible_RecruitNoviceModalPtr_bool(ct_stacktrace, 191, 103, &self->recruit_novice_modal, false);
}
    else if (ui_event->event_name == UIEventName_BuyExplorer) {
        if (0 < 0 || 0 > game->world.guilds.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", 0, game->world.guilds.size);
                ct_stacktrace_push(ct_stacktrace, 191, 105);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            player_guild = &game->world.guilds.arr[0];
        void_mfunc_RecruitNoviceModal_set_visible_RecruitNoviceModalPtr_bool(ct_stacktrace, 191, 109, &self->recruit_novice_modal, false);
        unit_handle = int_mfunc_World_get_handle_WorldPtr_HandleType(ct_stacktrace, 191, 111, &game->world, HandleType_Unit);
        if (unit_handle < 0 || unit_handle > game->world.units.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", unit_handle, game->world.units.size);
                ct_stacktrace_push(ct_stacktrace, 191, 112);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit = &game->world.units.arr[unit_handle];
        void_mfunc_Unit_set_to_UnitPtr_GamePtr_UnitName_Faction(ct_stacktrace, 191, 113, unit, game, UnitName_Explorer, Faction_Ally);
        if (1 < 0 || 1 > game->world.maps.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", 1, game->world.maps.size);
                ct_stacktrace_push(ct_stacktrace, 191, 114);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            map = &game->world.maps.arr[1];
        void_mfunc_Unit_join_guild_UnitPtr_GamePtr_GuildPtr(ct_stacktrace, 191, 115, unit, game, player_guild);
        void_mfunc_Unit_join_map_UnitPtr_GamePtr_MapPtr(ct_stacktrace, 191, 116, unit, game, map);
        void_mfunc_Unit_set_random_spawn_point_UnitPtr_GamePtr(ct_stacktrace, 191, 117, unit, game);
}
    else if (ui_event->event_name == UIEventName_BuyMerchant) {
        if (0 < 0 || 0 > game->world.guilds.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", 0, game->world.guilds.size);
                ct_stacktrace_push(ct_stacktrace, 191, 119);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            player_guild = &game->world.guilds.arr[0];
        void_mfunc_RecruitNoviceModal_set_visible_RecruitNoviceModalPtr_bool(ct_stacktrace, 191, 123, &self->recruit_novice_modal, false);
        unit_handle = int_mfunc_World_get_handle_WorldPtr_HandleType(ct_stacktrace, 191, 125, &game->world, HandleType_Unit);
        if (unit_handle < 0 || unit_handle > game->world.units.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", unit_handle, game->world.units.size);
                ct_stacktrace_push(ct_stacktrace, 191, 126);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit = &game->world.units.arr[unit_handle];
        void_mfunc_Unit_set_to_UnitPtr_GamePtr_UnitName_Faction(ct_stacktrace, 191, 127, unit, game, UnitName_Merchant, Faction_Ally);
        if (2 < 0 || 2 > game->world.maps.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", 2, game->world.maps.size);
                ct_stacktrace_push(ct_stacktrace, 191, 128);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            map = &game->world.maps.arr[2];
        void_mfunc_Unit_join_guild_UnitPtr_GamePtr_GuildPtr(ct_stacktrace, 191, 129, unit, game, player_guild);
        void_mfunc_Unit_join_map_UnitPtr_GamePtr_MapPtr(ct_stacktrace, 191, 130, unit, game, map);
        void_mfunc_Unit_set_random_spawn_point_UnitPtr_GamePtr(ct_stacktrace, 191, 131, unit, game);
}
    else if (ui_event->event_name == UIEventName_UnitsWindowOpen) {
        opposite_visible_state = !(game->world.ui.units_window.visible);
        void_mfunc_UnitsWindow_set_visible_UnitsWindowPtr_bool(ct_stacktrace, 191, 135, &game->world.ui.units_window, opposite_visible_state);
}
    else if (ui_event->event_name == UIEventName_UnitsWindowClose) {
        void_mfunc_UnitsWindow_set_visible_UnitsWindowPtr_bool(ct_stacktrace, 191, 137, &game->world.ui.units_window, false);
}
    else if (ui_event->event_name == UIEventName_UnitsWindowBackground) {
                ct_stacktrace_pop(ct_stacktrace);
return;
}
    else if (ui_event->event_name == UIEventName_UnitsWindowSlot) {
        handle = ui_event->handle;
        guild_handle = ui_event->guild_handle;
        if (guild_handle < 0 || guild_handle > game->world.guilds.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", guild_handle, game->world.guilds.size);
                ct_stacktrace_push(ct_stacktrace, 191, 144);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            guild = &game->world.guilds.arr[guild_handle];
        if (handle <= (guild->unit_handles.size - 1)) {
            game->world.ui.units_window.active_slot_idx = handle;
    }
}
    else if (ui_event->event_name == UIEventName_UnitsWindowStatusTab) {
        game->world.ui.units_window.active_tab = UnitsWindowTabName_Status;
}
    else if (ui_event->event_name == UIEventName_UnitsWindowInventoryTab) {
        game->world.ui.units_window.active_tab = UnitsWindowTabName_Inventory;
}
    else if (ui_event->event_name == UIEventName_UnitsWindowAbilityTab) {
        game->world.ui.units_window.active_tab = UnitsWindowTabName_Ability;
}
    else if (ui_event->event_name == UIEventName_UnitsWindowJobChangeTab) {
        game->world.ui.units_window.active_tab = UnitsWindowTabName_JobChange;
}
    else if (ui_event->event_name == UIEventName_UnitsWindowAITab) {
        game->world.ui.units_window.active_tab = UnitsWindowTabName_AI;
}
    else if (ui_event->event_name == UIEventName_UnitsWindowJobChange) {
        guild_unit_idx = game->world.ui.units_window.active_slot_idx;
        if (0 < 0 || 0 > game->world.guilds.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", 0, game->world.guilds.size);
                ct_stacktrace_push(ct_stacktrace, 191, 159);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            player_guild = &game->world.guilds.arr[0];
        if (guild_unit_idx < 0 || guild_unit_idx > player_guild->unit_handles.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", guild_unit_idx, player_guild->unit_handles.size);
                ct_stacktrace_push(ct_stacktrace, 191, 160);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit_handle = player_guild->unit_handles.arr[guild_unit_idx];
        if (unit_handle < 0 || unit_handle > game->world.units.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", unit_handle, game->world.units.size);
                ct_stacktrace_push(ct_stacktrace, 191, 161);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit = &game->world.units.arr[unit_handle];
        unit_name = ui_event->unit_name;
        void_mfunc_Unit_set_to_UnitPtr_GamePtr_UnitName_Faction(ct_stacktrace, 191, 163, unit, game, unit_name, unit->faction);
}
    else if (ui_event->event_name == UIEventName_UnitsWindowLearnAbility) {
        guild_unit_idx = game->world.ui.units_window.active_slot_idx;
        if (0 < 0 || 0 > game->world.guilds.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", 0, game->world.guilds.size);
                ct_stacktrace_push(ct_stacktrace, 191, 166);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            player_guild = &game->world.guilds.arr[0];
        if (guild_unit_idx < 0 || guild_unit_idx > player_guild->unit_handles.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", guild_unit_idx, player_guild->unit_handles.size);
                ct_stacktrace_push(ct_stacktrace, 191, 167);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit_handle = player_guild->unit_handles.arr[guild_unit_idx];
        if (unit_handle < 0 || unit_handle > game->world.units.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", unit_handle, game->world.units.size);
                ct_stacktrace_push(ct_stacktrace, 191, 168);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit = &game->world.units.arr[unit_handle];
        if (ui_event->handle < 0 || ui_event->handle > unit->job_abilities.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", ui_event->handle, unit->job_abilities.size);
                ct_stacktrace_push(ct_stacktrace, 191, 169);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            job_ability = &unit->job_abilities.arr[ui_event->handle];
        ability = SharedAbilityPtr_mfunc_Unit_get_ability_UnitPtr_AbilityName(ct_stacktrace, 191, 170, unit, job_ability->ability->ability_name);
        if (unit->available_skill_points == 0) {
                        ct_stacktrace_pop(ct_stacktrace);
return;
}
        if (ability->skill_points < job_ability->ability->stats.max_skill_points) {
            unit->available_skill_points -= 1;
            ability->skill_points += 1;
    }
}
    else if (ui_event->event_name == UIEventName_UnitsWindowIncreaseStats) {
        guild_unit_idx = game->world.ui.units_window.active_slot_idx;
        if (0 < 0 || 0 > game->world.guilds.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", 0, game->world.guilds.size);
                ct_stacktrace_push(ct_stacktrace, 191, 178);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            player_guild = &game->world.guilds.arr[0];
        if (guild_unit_idx < 0 || guild_unit_idx > player_guild->unit_handles.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", guild_unit_idx, player_guild->unit_handles.size);
                ct_stacktrace_push(ct_stacktrace, 191, 179);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit_handle = player_guild->unit_handles.arr[guild_unit_idx];
        if (unit_handle < 0 || unit_handle > game->world.units.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", unit_handle, game->world.units.size);
                ct_stacktrace_push(ct_stacktrace, 191, 180);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit = &game->world.units.arr[unit_handle];
        stat_name = ui_event->stat_name;
        inc_val = (Uint64)(1);
        stat_cost = 0;
        if (stat_name == StatName_Strength) {
            stat_cost = int_get_stat_cost_Uint64(ct_stacktrace, 191, 185, unit->stats.strength.value);
            if (unit->available_stat_points >= stat_cost) {
                unit->available_stat_points -= stat_cost;
                void_mfunc_Range_inc_RangePtr_Uint64(ct_stacktrace, 191, 188, &unit->stats.strength, inc_val);
    }
}
        else if (stat_name == StatName_Intelligence) {
            stat_cost = int_get_stat_cost_Uint64(ct_stacktrace, 191, 190, unit->stats.intelligence.value);
            if (unit->available_stat_points >= stat_cost) {
                unit->available_stat_points -= stat_cost;
                void_mfunc_Range_inc_RangePtr_Uint64(ct_stacktrace, 191, 193, &unit->stats.intelligence, inc_val);
    }
}
        else if (stat_name == StatName_Dexterity) {
            stat_cost = int_get_stat_cost_Uint64(ct_stacktrace, 191, 195, unit->stats.dexterity.value);
            if (unit->available_stat_points >= stat_cost) {
                unit->available_stat_points -= stat_cost;
                void_mfunc_Range_inc_RangePtr_Uint64(ct_stacktrace, 191, 198, &unit->stats.dexterity, inc_val);
    }
}
        else if (stat_name == StatName_Vitality) {
            stat_cost = int_get_stat_cost_Uint64(ct_stacktrace, 191, 200, unit->stats.vitality.value);
            if (unit->available_stat_points >= stat_cost) {
                unit->available_stat_points -= stat_cost;
                void_mfunc_Range_inc_RangePtr_Uint64(ct_stacktrace, 191, 203, &unit->stats.vitality, inc_val);
    }
}
        else if (stat_name == StatName_Agility) {
            stat_cost = int_get_stat_cost_Uint64(ct_stacktrace, 191, 205, unit->stats.agility.value);
            if (unit->available_stat_points >= stat_cost) {
                unit->available_stat_points -= stat_cost;
                void_mfunc_Range_inc_RangePtr_Uint64(ct_stacktrace, 191, 208, &unit->stats.agility, inc_val);
    }
}
        else if (stat_name == StatName_Luck) {
            stat_cost = int_get_stat_cost_Uint64(ct_stacktrace, 191, 210, unit->stats.luck.value);
            if (unit->available_stat_points >= stat_cost) {
                unit->available_stat_points -= stat_cost;
                void_mfunc_Range_inc_RangePtr_Uint64(ct_stacktrace, 191, 213, &unit->stats.luck, inc_val);
        }
    }
}
    else if (ui_event->event_name == UIEventName_UnitsWindowAISelect) {
        if ((game->world.ui.units_window.ai_ability_dropdown_visible && game->world.ui.units_window.ai_ability_active_idx == ui_event->handle)) {
            game->world.ui.units_window.ai_ability_dropdown_visible = false;
}
        else {
            game->world.ui.units_window.ai_ability_dropdown_visible = true;
            game->world.ui.units_window.ai_ability_active_idx = ui_event->handle;
    }
}
    else if (ui_event->event_name == UIEventName_UnitsWindowAISelectOption) {
        guild_unit_idx = game->world.ui.units_window.active_slot_idx;
        if (0 < 0 || 0 > game->world.guilds.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", 0, game->world.guilds.size);
                ct_stacktrace_push(ct_stacktrace, 191, 222);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            player_guild = &game->world.guilds.arr[0];
        if (guild_unit_idx < 0 || guild_unit_idx > player_guild->unit_handles.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", guild_unit_idx, player_guild->unit_handles.size);
                ct_stacktrace_push(ct_stacktrace, 191, 223);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit_handle = player_guild->unit_handles.arr[guild_unit_idx];
        if (unit_handle < 0 || unit_handle > game->world.units.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", unit_handle, game->world.units.size);
                ct_stacktrace_push(ct_stacktrace, 191, 224);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit = &game->world.units.arr[unit_handle];
        ability_handle = ui_event->handle;
        if (ability_handle == (game->world.ui.units_window.ai_ability_dropdown_options.size - 1)) {
            ai_ability_handle = game->world.ui.units_window.ai_ability_active_idx;
            if (ai_ability_handle < 0 || ai_ability_handle > unit->ai_abilities.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", ai_ability_handle, unit->ai_abilities.size);
                    ct_stacktrace_push(ct_stacktrace, 191, 229);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                ai_ability = &unit->ai_abilities.arr[ai_ability_handle];
            void_mfunc_AIAbility_clear_AIAbilityPtr(ct_stacktrace, 191, 230, ai_ability);
            game->world.ui.units_window.ai_ability_dropdown_visible = false;
}
        else if (ability_handle <= (unit->abilities.size - 1)) {
            if (ability_handle < 0 || ability_handle > unit->abilities.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", ability_handle, unit->abilities.size);
                    ct_stacktrace_push(ct_stacktrace, 191, 233);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                ability = &unit->abilities.arr[ability_handle];
            ai_ability_handle = game->world.ui.units_window.ai_ability_active_idx;
            if (ai_ability_handle < 0 || ai_ability_handle > unit->ai_abilities.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", ai_ability_handle, unit->ai_abilities.size);
                    ct_stacktrace_push(ct_stacktrace, 191, 235);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                ai_ability = &unit->ai_abilities.arr[ai_ability_handle];
            void_mfunc_AIAbility_set_AIAbilityPtr_int_AIAbilityCondition(ct_stacktrace, 191, 236, ai_ability, ability_handle, AIAbilityCondition_Always);
            game->world.ui.units_window.ai_ability_dropdown_visible = false;
    }
}
    else if (ui_event->event_name == UIEventName_UnitsWindowAISelectBackground) {
                ct_stacktrace_pop(ct_stacktrace);
return;
}
    else if (ui_event->event_name == UIEventName_MerchantsWindowOpen) {
        opposite_visible_state = !(game->world.ui.merchants_window.visible);
        void_mfunc_MerchantsWindow_set_visible_MerchantsWindowPtr_bool(ct_stacktrace, 191, 243, &game->world.ui.merchants_window, opposite_visible_state);
}
    else if (ui_event->event_name == UIEventName_MerchantsWindowClose) {
        void_mfunc_MerchantsWindow_set_visible_MerchantsWindowPtr_bool(ct_stacktrace, 191, 245, &game->world.ui.merchants_window, false);
}
    else if (ui_event->event_name == UIEventName_MerchantsWindowBackground) {
                ct_stacktrace_pop(ct_stacktrace);
return;
}
    else if (ui_event->event_name == UIEventName_MerchantsWindowSlot) {
        handle = ui_event->handle;
        guild_handle = ui_event->guild_handle;
        if (guild_handle < 0 || guild_handle > game->world.guilds.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", guild_handle, game->world.guilds.size);
                ct_stacktrace_push(ct_stacktrace, 191, 252);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            guild = &game->world.guilds.arr[guild_handle];
        if (handle <= (guild->merchant_handles.size - 1)) {
            game->world.ui.merchants_window.active_slot_idx = handle;
    }
}
    else if (ui_event->event_name == UIEventName_GuildWindowOpen) {
        opposite_visible_state = !(game->world.ui.guild_window.visible);
        void_mfunc_GuildWindow_set_visible_GuildWindowPtr_bool(ct_stacktrace, 191, 258, &game->world.ui.guild_window, opposite_visible_state);
}
    else if (ui_event->event_name == UIEventName_GuildWindowClose) {
        void_mfunc_GuildWindow_set_visible_GuildWindowPtr_bool(ct_stacktrace, 191, 260, &game->world.ui.guild_window, false);
}
    else if (ui_event->event_name == UIEventName_GuildWindowBackground) {
                ct_stacktrace_pop(ct_stacktrace);
return;
}
    else {
        self->on_click_fired_this_frame = false;
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_UI_after_on_click_UIPtr_GamePtr_UIEventPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UI* self, Game* game, UIEvent* ui_event) {
    bool not_ai_dropdown = false;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    not_ai_dropdown = !(((ui_event->event_name == UIEventName_UnitsWindowAISelect || ui_event->event_name == UIEventName_UnitsWindowAISelectBackground) || ui_event->event_name == UIEventName_UnitsWindowAISelectOption));
    if ((game->world.ui.units_window.ai_ability_dropdown_visible && not_ai_dropdown)) {
        game->world.ui.units_window.ai_ability_dropdown_visible = false;
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_UI_update_UIPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UI* self, Game* game) {
    int i = 0;
    UIRenderable* renderable = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    void_mfunc_TopNav_update_TopNavPtr_GamePtr(ct_stacktrace, 193, 39, &self->top_nav, game);
    void_mfunc_GuildWindow_update_GuildWindowPtr_GamePtr(ct_stacktrace, 193, 40, &self->guild_window, game);
    void_mfunc_UnitsWindow_update_UnitsWindowPtr_GamePtr(ct_stacktrace, 193, 41, &self->units_window, game);
    void_mfunc_MerchantsWindow_update_MerchantsWindowPtr_GamePtr(ct_stacktrace, 193, 42, &self->merchants_window, game);
    void_mfunc_RecruitNoviceModal_update_RecruitNoviceModalPtr_GamePtr(ct_stacktrace, 193, 43, &self->recruit_novice_modal, game);
    self->is_mouse_over_ui = false;
    self->on_click_fired_this_frame = false;
    for (i = (self->renderables.size - 1); i >= 0; i -= 1) {
        if (i < 0 || i > self->renderables.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->renderables.size);
                ct_stacktrace_push(ct_stacktrace, 193, 53);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            renderable = &self->renderables.arr[i];
        if (renderable->text_lg != NULL) {
            void_text_update_TextLGPtr_GamePtr(ct_stacktrace, 193, 55, renderable->text_lg, game);
}
        else if (renderable->sprite != NULL) {
            void_mfunc_UISprite_update_UISpritePtr_GamePtr(ct_stacktrace, 193, 57, renderable->sprite, game);
            if (renderable->sprite->input_events.is_mouse_over) {
                self->is_mouse_over_ui = true;
}
            if ((!(self->on_click_fired_this_frame) && renderable->sprite->input_events.is_click)) {
                void_mfunc_UI_on_click_UIPtr_GamePtr_UIEventPtr(ct_stacktrace, 193, 62, self, game, &renderable->sprite->ui_event);
                if (self->on_click_fired_this_frame) {
                    void_mfunc_UI_after_on_click_UIPtr_GamePtr_UIEventPtr(ct_stacktrace, 193, 64, self, game, &renderable->sprite->ui_event);
                }
            }
        }
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_UI_draw_UIPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UI* self, Game* game) {
    Unit* unit = NULL;
    UIRenderable* renderable = NULL;
    int i = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    for (i = 0; i < self->renderables.size; i++) {
        renderable = &self->renderables.arr[i];
        if (renderable->sprite != NULL) {
            void_mfunc_UISprite_draw_UISpritePtr_GamePtr(ct_stacktrace, 211, 69, renderable->sprite, game);
}
        else if (renderable->text_lg != NULL) {
            void_text_draw_TextLGPtr_GamePtr(ct_stacktrace, 211, 71, renderable->text_lg, game);
}
        else if (renderable->regular_sprite.sprite != NULL) {
            void_mfunc_Sprite_draw_at_SpritePtr_GamePtr_SDL_RectPtr(ct_stacktrace, 211, 73, renderable->regular_sprite.sprite, game, &renderable->regular_sprite.dst);
}
        else if (renderable->unit_sprite.sprite != NULL) {
            void_mfunc_UnitSprite_draw_idle_at_UnitSpritePtr_GamePtr_SDL_RectPtr(ct_stacktrace, 211, 75, renderable->unit_sprite.sprite, game, &renderable->unit_sprite.dst);
}
        else {
            if (renderable->unit.handle < 0 || renderable->unit.handle > game->world.units.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", renderable->unit.handle, game->world.units.size);
                    ct_stacktrace_push(ct_stacktrace, 211, 79);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                unit = &game->world.units.arr[renderable->unit.handle];
            void_mfunc_Unit_draw_idle_at_UnitPtr_GamePtr_SDL_RectPtr(ct_stacktrace, 211, 80, unit, game, &renderable->unit.dst);
        }
    }
    ct_stacktrace_pop(ct_stacktrace);
}

