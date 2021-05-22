#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "ct_stacktrace.h"
#include "ui_containers.h"
#include "engine.h"
#include "utils.h"
#include "image.h"
#include "ct_array.h"
#include "ui_sprite.h"
#include "text.h"
#include "sprite.h"
#include "constants.h"
#include "unit_sprite.h"
#include "game.h"

void void_mfunc_TopNav_init_TopNavPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, TopNav* self, Game* game) {
    SDL_Point text_dst = {0};
    SDL_Color text_outline_color = {0};
    SDL_Rect units_button_src = {0};
    SDL_Rect guild_button_src = {0};
    SDL_Rect merchants_button_src = {0};
    SDL_Color text_color = {0};
    SDL_Rect background_src = {0};

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->visible = true;
    self->background.render_dst.is_camera_rendered = false;
    self->background.anim_speed = 100;
    background_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 34, 88, 0, 240, 80, 40);
    self->background.shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 34, 89, &game->sprite_db, game, ImageName_UI, &background_src);
    self->guild_button.render_dst.is_camera_rendered = false;
    self->guild_button.anim_speed = 100;
    self->guild_button.ui_event.event_name = UIEventName_GuildWindowOpen;
    guild_button_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 34, 93, 48, 288, 24, 24);
    self->guild_button.shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 34, 94, &game->sprite_db, game, ImageName_UI, &guild_button_src);
    self->units_button.render_dst.is_camera_rendered = false;
    self->units_button.anim_speed = 100;
    self->units_button.ui_event.event_name = UIEventName_UnitsWindowOpen;
    units_button_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 34, 98, 0, 288, 24, 24);
    self->units_button.shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 34, 99, &game->sprite_db, game, ImageName_UI, &units_button_src);
    self->merchants_button.render_dst.is_camera_rendered = false;
    self->merchants_button.anim_speed = 100;
    self->merchants_button.ui_event.event_name = UIEventName_MerchantsWindowOpen;
    merchants_button_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 34, 103, 24, 288, 24, 24);
    self->merchants_button.shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 34, 104, &game->sprite_db, game, ImageName_UI, &merchants_button_src);
    text_color = SDL_Color_create_color_int_int_int_int(ct_stacktrace, 34, 106, 255, 255, 255, 255);
    text_outline_color = SDL_Color_create_color_int_int_int_int(ct_stacktrace, 34, 107, 0, 0, 0, 255);
    text_dst = SDL_Point_create_point_int_int(ct_stacktrace, 34, 108, 0, 0);
    void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 34, 109, &self->league_text, game, "Muny", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 1, &text_outline_color, false);
    text_color = SDL_Color_create_color_int_int_int_int(ct_stacktrace, 34, 110, 0, 0, 0, 255);
    text_outline_color = SDL_Color_create_color_int_int_int_int(ct_stacktrace, 34, 111, 0, 0, 0, 255);
    text_dst = SDL_Point_create_point_int_int(ct_stacktrace, 34, 112, 0, 0);
    void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 34, 113, &self->money_text, game, "Muny", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 0, &text_outline_color, false);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_RecruitNoviceModal_init_RecruitNoviceModalPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, RecruitNoviceModal* self, Game* game) {
    char* unit_header_str = NULL;
    SDL_Point text_dst = {0};
    SDL_Color text_color = {0};
    TextLG* ok_button_text = NULL;
    SDL_Rect src = {0};
    TextLG* unit_cost_text = NULL;
    SDL_Rect background_src = {0};
    SDL_Color text_outline_color = {0};
    SDL_Rect backdrop_src = {0};
    SDL_Rect close_button_src = {0};
    UISprite* ok_button = NULL;
    int i = 0;
    TextLG* unit_header_text = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->backdrop.render_dst.is_camera_rendered = false;
    self->backdrop.anim_speed = 100;
    self->backdrop.ui_event.event_name = UIEventName_BuyRecruitBackdrop;
    backdrop_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 35, 160, 0, 1688, 640, 360);
    self->backdrop.shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 35, 161, &game->sprite_db, game, ImageName_UI, &backdrop_src);
    self->background.render_dst.is_camera_rendered = false;
    self->background.anim_speed = 100;
    self->background.ui_event.event_name = UIEventName_BuyRecruitModal;
    background_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 35, 165, 0, 32, 180, 165);
    self->background.shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 35, 166, &game->sprite_db, game, ImageName_UI, &background_src);
    self->close_button.render_dst.is_camera_rendered = false;
    self->close_button.anim_speed = 100;
    self->close_button.ui_event.event_name = UIEventName_BuyRecruitClose;
    close_button_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 35, 170, 0, 1664, 10, 10);
    self->close_button.shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 35, 171, &game->sprite_db, game, ImageName_UI, &close_button_src);
    self->unit_header_texts.size = 2;
    self->unit_cost_texts.size = 2;
    self->unit_slots_ok_buttons.size = 2;
    self->unit_slots_ok_button_texts.size = 2;
    for (i = 0; i < self->unit_slots_ok_buttons.size; i += 1) {
        if (i < 0 || i > self->unit_slots_ok_buttons.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->unit_slots_ok_buttons.size);
                ct_stacktrace_push(ct_stacktrace, 35, 178);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            ok_button = &self->unit_slots_ok_buttons.arr[i];
        if (i == 0) {
            ok_button->ui_event.event_name = UIEventName_BuyExplorer;
}
        else if (i == 1) {
            ok_button->ui_event.event_name = UIEventName_BuyMerchant;
}
        ok_button->render_dst.is_camera_rendered = false;
        ok_button->anim_speed = 100;
        src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 35, 185, 60, 0, 60, 24);
        ok_button->shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 35, 186, &game->sprite_db, game, ImageName_UI, &src);
        if (i < 0 || i > self->unit_slots_ok_button_texts.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->unit_slots_ok_button_texts.size);
                ct_stacktrace_push(ct_stacktrace, 35, 187);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            ok_button_text = &self->unit_slots_ok_button_texts.arr[i];
        text_color = SDL_Color_create_color_int_int_int_int(ct_stacktrace, 35, 188, 255, 255, 255, 255);
        text_outline_color = SDL_Color_create_color_int_int_int_int(ct_stacktrace, 35, 189, 0, 0, 0, 255);
        text_dst = SDL_Point_create_point_int_int(ct_stacktrace, 35, 190, 0, 0);
        void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 35, 191, ok_button_text, game, "Recruit", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 1, &text_outline_color, false);
        if (i < 0 || i > self->unit_header_texts.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->unit_header_texts.size);
                ct_stacktrace_push(ct_stacktrace, 35, 192);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit_header_text = &self->unit_header_texts.arr[i];
        text_color = SDL_Color_create_color_int_int_int_int(ct_stacktrace, 35, 193, 0, 0, 0, 255);
        unit_header_str = "Explorer";
        if (i == 1) {
            unit_header_str = "Merchant";
}
        void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 35, 197, unit_header_text, game, unit_header_str, &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 0, &text_outline_color, false);
        if (i < 0 || i > self->unit_cost_texts.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->unit_cost_texts.size);
                ct_stacktrace_push(ct_stacktrace, 35, 198);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit_cost_text = &self->unit_cost_texts.arr[i];
        void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 35, 199, unit_cost_text, game, "500 Muny", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 0, &text_outline_color, false);
}
    text_color = SDL_Color_create_color_int_int_int_int(ct_stacktrace, 35, 201, 0, 0, 0, 255);
    text_outline_color = SDL_Color_create_color_int_int_int_int(ct_stacktrace, 35, 202, 0, 0, 0, 255);
    text_dst = SDL_Point_create_point_int_int(ct_stacktrace, 35, 203, 0, 0);
    void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 35, 204, &self->header_text, game, "Recruit new unit", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 0, &text_outline_color, false);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_GuildWindow_init_GuildWindowPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, GuildWindow* self, Game* game) {
    TextLG* inventory_quantity_text = NULL;
    UISprite* inventory_slot = NULL;
    SDL_Color text_outline_color = {0};
    SDL_Rect tab_src = {0};
    SDL_Rect background_src = {0};
    SDL_Rect close_button_src = {0};
    SDL_Color text_color = {0};
    SDL_Rect slot_src = {0};
    SDL_Point text_dst = {0};
    int i = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->background.render_dst.is_camera_rendered = false;
    self->background.anim_speed = 100;
    self->background.ui_event.event_name = UIEventName_GuildWindowBackground;
    background_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 36, 1108, 640, 1786, 544, 262);
    self->background.shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 36, 1109, &game->sprite_db, game, ImageName_UI, &background_src);
    self->window_close_button.render_dst.is_camera_rendered = false;
    self->window_close_button.anim_speed = 100;
    self->window_close_button.ui_event.event_name = UIEventName_GuildWindowClose;
    close_button_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 36, 1113, 10, 1664, 10, 10);
    self->window_close_button.shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 36, 1114, &game->sprite_db, game, ImageName_UI, &close_button_src);
    self->inventory_tab.render_dst.is_camera_rendered = false;
    self->inventory_tab.anim_speed = 100;
    self->inventory_tab.ui_event.event_name = UIEventName_UnitsWindowInventoryTab;
    tab_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 36, 1118, 0, 364, 64, 25);
    self->inventory_tab.shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 36, 1119, &game->sprite_db, game, ImageName_UI, &tab_src);
    text_color = SDL_Color_create_color_int_int_int_int(ct_stacktrace, 36, 1121, 255, 255, 255, 255);
    text_outline_color = SDL_Color_create_color_int_int_int_int(ct_stacktrace, 36, 1122, 0, 0, 0, 255);
    text_dst = SDL_Point_create_point_int_int(ct_stacktrace, 36, 1123, 0, 0);
    void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 36, 1124, &self->window_text, game, "League", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 1, &text_outline_color, false);
    text_color = SDL_Color_create_color_int_int_int_int(ct_stacktrace, 36, 1126, 0, 0, 0, 255);
    text_outline_color = SDL_Color_create_color_int_int_int_int(ct_stacktrace, 36, 1127, 0, 0, 0, 255);
    void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 36, 1128, &self->inventory_tab_text, game, "Inventory", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 0, &text_outline_color, false);
    self->inventory_slots.size = 50;
    self->inventory_quantity_texts.size = 50;
    if (self->inventory_slots.size != self->inventory_quantity_texts.size) {
        printf("%s\n", "ui_containers. UnitsWindow - inventory slots size != inventory quantity texts size.");
        ct_stacktrace_push(ct_stacktrace, 36, 1135);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    for (i = 0; i < self->inventory_slots.size; i += 1) {
        if (i < 0 || i > self->inventory_slots.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->inventory_slots.size);
                ct_stacktrace_push(ct_stacktrace, 36, 1137);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            inventory_slot = &self->inventory_slots.arr[i];
        inventory_slot->render_dst.is_camera_rendered = false;
        inventory_slot->anim_speed = 100;
        slot_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 36, 1140, 0, 389, 24, 24);
        inventory_slot->shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 36, 1141, &game->sprite_db, game, ImageName_UI, &slot_src);
        text_color = SDL_Color_create_color_int_int_int_int(ct_stacktrace, 36, 1143, 0, 0, 0, 255);
        text_outline_color = SDL_Color_create_color_int_int_int_int(ct_stacktrace, 36, 1144, 255, 255, 255, 255);
        text_dst = SDL_Point_create_point_int_int(ct_stacktrace, 36, 1145, 0, 0);
        if (i < 0 || i > self->inventory_quantity_texts.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->inventory_quantity_texts.size);
                ct_stacktrace_push(ct_stacktrace, 36, 1146);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            inventory_quantity_text = &self->inventory_quantity_texts.arr[i];
        void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 36, 1147, inventory_quantity_text, game, "0", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 1, &text_outline_color, false);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_UnitsWindow_init_UnitsWindowPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitsWindow* self, Game* game) {
    SDL_Point text_dst = {0};
    SDL_Color text_color = {0};
    SDL_Color text_outline_color = {0};
    SDL_Rect tab_src = {0};
    UISprite* stat_button = NULL;
    UISprite* stat_icon = NULL;
    SDL_Rect background_src = {0};
    TextLG* ability_skill_point_text = NULL;
    UISprite* unit_slot = NULL;
    SDL_Rect close_button_src = {0};
    SDL_Rect increase_stat_button_src = {0};
    UISprite* inventory_slot = NULL;
    SDL_Rect stat_icon_src = {0};
    SDL_Rect src = {0};
    TextLG* inventory_quantity_text = NULL;
    int i = 0;
    StatName stat_enum_value = (StatName) 0;
    TextLG* stat_cost_text = NULL;
    SDL_Rect slot_src = {0};
    UISprite* slot = NULL;
    UISprite* ability_slot = NULL;
    TextLG* ability_order_text = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->active_tab = UnitsWindowTabName_Status;
    self->background.render_dst.is_camera_rendered = false;
    self->background.anim_speed = 100;
    self->background.ui_event.event_name = UIEventName_UnitsWindowBackground;
    background_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 37, 322, 640, 1786, 544, 262);
    self->background.shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 37, 323, &game->sprite_db, game, ImageName_UI, &background_src);
    self->window_close_button.render_dst.is_camera_rendered = false;
    self->window_close_button.anim_speed = 100;
    self->window_close_button.ui_event.event_name = UIEventName_UnitsWindowClose;
    close_button_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 37, 327, 10, 1664, 10, 10);
    self->window_close_button.shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 37, 328, &game->sprite_db, game, ImageName_UI, &close_button_src);
    self->status_tab.render_dst.is_camera_rendered = false;
    self->status_tab.anim_speed = 100;
    self->status_tab.ui_event.event_name = UIEventName_UnitsWindowStatusTab;
    tab_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 37, 332, 0, 364, 64, 25);
    self->status_tab.shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 37, 333, &game->sprite_db, game, ImageName_UI, &tab_src);
    self->inventory_tab.render_dst.is_camera_rendered = false;
    self->inventory_tab.anim_speed = 100;
    self->inventory_tab.ui_event.event_name = UIEventName_UnitsWindowInventoryTab;
    tab_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 37, 337, 0, 364, 64, 25);
    self->inventory_tab.shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 37, 338, &game->sprite_db, game, ImageName_UI, &tab_src);
    self->ability_tab.render_dst.is_camera_rendered = false;
    self->ability_tab.anim_speed = 100;
    self->ability_tab.ui_event.event_name = UIEventName_UnitsWindowAbilityTab;
    tab_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 37, 342, 0, 364, 64, 25);
    self->ability_tab.shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 37, 343, &game->sprite_db, game, ImageName_UI, &tab_src);
    self->job_change_tab.render_dst.is_camera_rendered = false;
    self->job_change_tab.anim_speed = 100;
    self->job_change_tab.ui_event.event_name = UIEventName_UnitsWindowJobChangeTab;
    tab_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 37, 347, 0, 364, 64, 25);
    self->job_change_tab.shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 37, 348, &game->sprite_db, game, ImageName_UI, &tab_src);
    self->ai_tab.render_dst.is_camera_rendered = false;
    self->ai_tab.anim_speed = 100;
    self->ai_tab.ui_event.event_name = UIEventName_UnitsWindowAITab;
    tab_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 37, 352, 0, 364, 64, 25);
    self->ai_tab.shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 37, 353, &game->sprite_db, game, ImageName_UI, &tab_src);
    self->ai_ability_dropdown_background.render_dst.is_camera_rendered = false;
    self->ai_ability_dropdown_background.anim_speed = 100;
    src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 37, 356, 0, 431, 80, 80);
    self->ai_ability_dropdown_background.shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 37, 357, &game->sprite_db, game, ImageName_UI, &src);
    self->ai_ability_dropdown_background.ui_event.event_name = UIEventName_UnitsWindowAISelectBackground;
    self->ai_ability_remove_icon.render_dst.is_camera_rendered = false;
    self->ai_ability_remove_icon.anim_speed = 100;
    src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 37, 361, 20, 40, 20, 20);
    self->ai_ability_remove_icon.shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 37, 362, &game->sprite_db, game, ImageName_Items, &src);
    text_color = SDL_Color_create_color_int_int_int_int(ct_stacktrace, 37, 364, 255, 255, 255, 255);
    text_outline_color = SDL_Color_create_color_int_int_int_int(ct_stacktrace, 37, 365, 0, 0, 0, 255);
    text_dst = SDL_Point_create_point_int_int(ct_stacktrace, 37, 366, 0, 0);
    void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 37, 367, &self->window_text, game, "Units", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 1, &text_outline_color, false);
    text_color = SDL_Color_create_color_int_int_int_int(ct_stacktrace, 37, 369, 0, 0, 0, 255);
    text_outline_color = SDL_Color_create_color_int_int_int_int(ct_stacktrace, 37, 370, 0, 0, 0, 255);
    text_dst = SDL_Point_create_point_int_int(ct_stacktrace, 37, 371, 0, 0);
    void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 37, 372, &self->status_tab_text, game, "Status", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 0, &text_outline_color, false);
    void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 37, 373, &self->inventory_tab_text, game, "Inventory", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 0, &text_outline_color, false);
    void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 37, 374, &self->ability_tab_text, game, "Ability", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 0, &text_outline_color, false);
    void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 37, 375, &self->job_change_tab_text, game, "Job", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 0, &text_outline_color, false);
    void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 37, 376, &self->ai_tab_text, game, "AI", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 0, &text_outline_color, false);
    void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 37, 378, &self->job_text, game, "Job name", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 0, &text_outline_color, false);
    void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 37, 379, &self->level_text, game, "Level", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 0, &text_outline_color, false);
    void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 37, 380, &self->job_level_text, game, "Level", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 0, &text_outline_color, false);
    void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 37, 381, &self->experience_text, game, "Experience", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 0, &text_outline_color, false);
    void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 37, 382, &self->job_experience_text, game, "Experience", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 0, &text_outline_color, false);
    void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 37, 383, &self->strength_text, game, "Strength:", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 0, &text_outline_color, false);
    void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 37, 384, &self->intelligence_text, game, "Intelligence:", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 0, &text_outline_color, false);
    void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 37, 385, &self->dexterity_text, game, "Dexterity:", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 0, &text_outline_color, false);
    void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 37, 386, &self->vitality_text, game, "Vitality:", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 0, &text_outline_color, false);
    void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 37, 387, &self->agility_text, game, "Agility:", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 0, &text_outline_color, false);
    void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 37, 388, &self->luck_text, game, "Luck:", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 0, &text_outline_color, false);
    void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 37, 389, &self->next_job_change_level_text, game, "Next Job Change", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 0, &text_outline_color, false);
    void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 37, 390, &self->available_stat_points_text, game, "Stat Points", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 0, &text_outline_color, false);
    void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 37, 391, &self->available_skill_points_text, game, "Skill points", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 0, &text_outline_color, false);
    increase_stat_button_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 37, 394, 0, 413, 13, 12);
    stat_icon_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 37, 395, 0, 425, 9, 6);
    self->increase_stat_buttons.size = 6;
    self->increase_stat_icons.size = 6;
    self->increase_stat_cost_texts.size = 6;
    for (i = 0; i < self->increase_stat_buttons.size; i++) {
        stat_button = &self->increase_stat_buttons.arr[i];
        stat_enum_value = (StatName)((i + 1));
        if (i < 0 || i > self->increase_stat_icons.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->increase_stat_icons.size);
                ct_stacktrace_push(ct_stacktrace, 37, 401);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            stat_icon = &self->increase_stat_icons.arr[i];
        if (i < 0 || i > self->increase_stat_cost_texts.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->increase_stat_cost_texts.size);
                ct_stacktrace_push(ct_stacktrace, 37, 402);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            stat_cost_text = &self->increase_stat_cost_texts.arr[i];
        stat_button->render_dst.is_camera_rendered = false;
        stat_button->anim_speed = 100;
        stat_button->ui_event.event_name = UIEventName_UnitsWindowIncreaseStats;
        stat_button->ui_event.stat_name = stat_enum_value;
        stat_button->shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 37, 407, &game->sprite_db, game, ImageName_UI, &increase_stat_button_src);
        stat_icon->render_dst.is_camera_rendered = false;
        stat_icon->anim_speed = 100;
        stat_icon->shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 37, 410, &game->sprite_db, game, ImageName_UI, &stat_icon_src);
        void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 37, 411, stat_cost_text, game, "1", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 0, &text_outline_color, false);
}
    self->unit_slots.size = 30;
    for (i = 0; i < self->unit_slots.size; i += 1) {
        if (i < 0 || i > self->unit_slots.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->unit_slots.size);
                ct_stacktrace_push(ct_stacktrace, 37, 416);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit_slot = &self->unit_slots.arr[i];
        unit_slot->render_dst.is_camera_rendered = false;
        unit_slot->anim_speed = 100;
        unit_slot->ui_event.event_name = UIEventName_UnitsWindowSlot;
        unit_slot->ui_event.handle = i;
        unit_slot->ui_event.guild_handle = 0;
        slot_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 37, 423, 0, 320, 24, 44);
        unit_slot->shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 37, 424, &game->sprite_db, game, ImageName_UI, &slot_src);
}
    self->inventory_slots.size = 50;
    self->inventory_quantity_texts.size = 50;
    if (self->inventory_slots.size != self->inventory_quantity_texts.size) {
        printf("%s\n", "ui_containers. UnitsWindow - inventory slots size != inventory quantity texts size.");
        ct_stacktrace_push(ct_stacktrace, 37, 431);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    for (i = 0; i < self->inventory_slots.size; i += 1) {
        if (i < 0 || i > self->inventory_slots.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->inventory_slots.size);
                ct_stacktrace_push(ct_stacktrace, 37, 433);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            inventory_slot = &self->inventory_slots.arr[i];
        inventory_slot->render_dst.is_camera_rendered = false;
        inventory_slot->anim_speed = 100;
        slot_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 37, 436, 0, 389, 24, 24);
        inventory_slot->shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 37, 437, &game->sprite_db, game, ImageName_UI, &slot_src);
        text_color = SDL_Color_create_color_int_int_int_int(ct_stacktrace, 37, 439, 0, 0, 0, 255);
        text_outline_color = SDL_Color_create_color_int_int_int_int(ct_stacktrace, 37, 440, 255, 255, 255, 255);
        text_dst = SDL_Point_create_point_int_int(ct_stacktrace, 37, 441, 0, 0);
        if (i < 0 || i > self->inventory_quantity_texts.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->inventory_quantity_texts.size);
                ct_stacktrace_push(ct_stacktrace, 37, 442);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            inventory_quantity_text = &self->inventory_quantity_texts.arr[i];
        void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 37, 443, inventory_quantity_text, game, "0", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 1, &text_outline_color, false);
}
    self->ability_slots.size = 10;
    self->ability_skill_point_texts.size = 10;
    for (i = 0; i < self->ability_slots.size; i += 1) {
        if (i < 0 || i > self->ability_slots.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->ability_slots.size);
                ct_stacktrace_push(ct_stacktrace, 37, 449);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            ability_slot = &self->ability_slots.arr[i];
        ability_slot->ui_event.event_name = UIEventName_UnitsWindowLearnAbility;
        ability_slot->ui_event.handle = i;
        ability_slot->render_dst.is_camera_rendered = false;
        ability_slot->anim_speed = 100;
        slot_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 37, 454, 0, 389, 24, 24);
        ability_slot->shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 37, 455, &game->sprite_db, game, ImageName_UI, &slot_src);
        text_color = SDL_Color_create_color_int_int_int_int(ct_stacktrace, 37, 457, 0, 0, 0, 255);
        text_outline_color = SDL_Color_create_color_int_int_int_int(ct_stacktrace, 37, 458, 255, 255, 255, 255);
        text_dst = SDL_Point_create_point_int_int(ct_stacktrace, 37, 459, 0, 0);
        if (i < 0 || i > self->ability_skill_point_texts.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->ability_skill_point_texts.size);
                ct_stacktrace_push(ct_stacktrace, 37, 460);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            ability_skill_point_text = &self->ability_skill_point_texts.arr[i];
        void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 37, 461, ability_skill_point_text, game, "0", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 1, &text_outline_color, false);
}
    self->job_change_row_2_slots.size = 5;
    self->job_change_row_3_slots.size = 10;
    for (i = 0; i < self->job_change_row_2_slots.size; i++) {
        slot = &self->job_change_row_2_slots.arr[i];
        slot->render_dst.is_camera_rendered = false;
        slot->anim_speed = 100;
        slot_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 37, 469, 0, 320, 24, 44);
        slot->shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 37, 470, &game->sprite_db, game, ImageName_UI, &slot_src);
        slot->ui_event.event_name = UIEventName_UnitsWindowJobChange;
        if (i == 0) {
            slot->ui_event.unit_name = UnitName_Mage;
}
        else {
            slot->ui_event.unit_name = UnitName_Explorer;
    }
}
    for (i = 0; i < self->job_change_row_3_slots.size; i++) {
        slot = &self->job_change_row_3_slots.arr[i];
        slot->render_dst.is_camera_rendered = false;
        slot->anim_speed = 100;
        slot_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 37, 479, 0, 320, 24, 44);
        slot->shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 37, 480, &game->sprite_db, game, ImageName_UI, &slot_src);
        slot->ui_event.event_name = UIEventName_UnitsWindowJobChange;
        if (i == 0) {
            slot->ui_event.unit_name = UnitName_Wizard;
}
        else if (i == 1) {
            slot->ui_event.unit_name = UnitName_Scholar;
}
        else {
            slot->ui_event.unit_name = UnitName_Explorer;
    }
}
    self->ai_ability_slots.size = 12;
    self->ai_ability_slot_order_texts.size = 12;
    self->ai_ability_dropdown_options.size = 9;
    for (i = 0; i < self->ai_ability_slots.size; i++) {
        slot = &self->ai_ability_slots.arr[i];
        slot->render_dst.is_camera_rendered = false;
        slot->anim_speed = 100;
        slot_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 37, 496, 0, 389, 24, 24);
        slot->shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 37, 497, &game->sprite_db, game, ImageName_UI, &slot_src);
        slot->ui_event.event_name = UIEventName_UnitsWindowAISelect;
        slot->ui_event.handle = i;
        if (i < 0 || i > self->ai_ability_slot_order_texts.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->ai_ability_slot_order_texts.size);
                ct_stacktrace_push(ct_stacktrace, 37, 500);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            ability_order_text = &self->ai_ability_slot_order_texts.arr[i];
        void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 37, 501, ability_order_text, game, "0", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 1, &text_outline_color, false);
}
    for (i = 0; i < self->ai_ability_dropdown_options.size; i++) {
        slot = &self->ai_ability_dropdown_options.arr[i];
        slot->render_dst.is_camera_rendered = false;
        slot->anim_speed = 100;
        slot_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 37, 505, 0, 389, 24, 24);
        slot->shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 37, 506, &game->sprite_db, game, ImageName_UI, &slot_src);
        slot->ui_event.event_name = UIEventName_UnitsWindowAISelectOption;
        slot->ui_event.handle = i;
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_MerchantsWindow_init_MerchantsWindowPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, MerchantsWindow* self, Game* game) {
    int i = 0;
    SDL_Point text_dst = {0};
    SDL_Color text_outline_color = {0};
    UISprite* unit_slot = NULL;
    SDL_Color text_color = {0};
    SDL_Rect close_button_src = {0};
    SDL_Rect background_src = {0};
    SDL_Rect slot_src = {0};

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->background.render_dst.is_camera_rendered = false;
    self->background.anim_speed = 100;
    self->background.ui_event.event_name = UIEventName_MerchantsWindowBackground;
    background_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 38, 1006, 640, 1786, 544, 262);
    self->background.shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 38, 1007, &game->sprite_db, game, ImageName_UI, &background_src);
    self->window_close_button.render_dst.is_camera_rendered = false;
    self->window_close_button.anim_speed = 100;
    self->window_close_button.ui_event.event_name = UIEventName_MerchantsWindowClose;
    close_button_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 38, 1011, 10, 1664, 10, 10);
    self->window_close_button.shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 38, 1012, &game->sprite_db, game, ImageName_UI, &close_button_src);
    text_color = SDL_Color_create_color_int_int_int_int(ct_stacktrace, 38, 1014, 255, 255, 255, 255);
    text_outline_color = SDL_Color_create_color_int_int_int_int(ct_stacktrace, 38, 1015, 0, 0, 0, 255);
    text_dst = SDL_Point_create_point_int_int(ct_stacktrace, 38, 1016, 0, 0);
    void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(ct_stacktrace, 38, 1017, &self->window_text, game, "Merchants", &text_dst, FontStyle_Bold, TextAlignment_Left, TextWordWrap_NoWrap, 500, 12, &text_color, 1, &text_outline_color, false);
    self->unit_slots.size = 30;
    for (i = 0; i < self->unit_slots.size; i += 1) {
        if (i < 0 || i > self->unit_slots.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->unit_slots.size);
                ct_stacktrace_push(ct_stacktrace, 38, 1022);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit_slot = &self->unit_slots.arr[i];
        unit_slot->render_dst.is_camera_rendered = false;
        unit_slot->anim_speed = 100;
        unit_slot->ui_event.event_name = UIEventName_MerchantsWindowSlot;
        unit_slot->ui_event.handle = i;
        unit_slot->ui_event.guild_handle = 0;
        slot_src = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 38, 1029, 0, 320, 24, 44);
        unit_slot->shared_srcs = SpriteSrcsPtr_mfunc_SpriteDB_find_SpriteDBPtr_GamePtr_ImageName_SDL_RectPtr(ct_stacktrace, 38, 1030, &game->sprite_db, game, ImageName_UI, &slot_src);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_RecruitNoviceModal_set_visible_RecruitNoviceModalPtr_bool(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, RecruitNoviceModal* self, bool visible) {
    int i = 0;
    UISprite* ok_button = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->visible = visible;
    if (!(self->visible)) {
        void_mfunc_InputEvents_clear_InputEventsPtr(ct_stacktrace, 162, 210, &self->backdrop.input_events);
        void_mfunc_InputEvents_clear_InputEventsPtr(ct_stacktrace, 162, 211, &self->backdrop.input_events);
        void_mfunc_InputEvents_clear_InputEventsPtr(ct_stacktrace, 162, 212, &self->close_button.input_events);
        for (i = 0; i < self->unit_slots_ok_buttons.size; i += 1) {
            if (i < 0 || i > self->unit_slots_ok_buttons.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", i, self->unit_slots_ok_buttons.size);
                    ct_stacktrace_push(ct_stacktrace, 162, 214);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                ok_button = &self->unit_slots_ok_buttons.arr[i];
            void_mfunc_InputEvents_clear_InputEventsPtr(ct_stacktrace, 162, 215, &ok_button->input_events);
        }
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_UIRenderable_clear_UIRenderablePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UIRenderable* self) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->sprite = NULL;
    self->text_lg = NULL;
    self->regular_sprite.sprite = NULL;
    self->unit_sprite.sprite = NULL;
    self->unit.handle = 0;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UIRenderable* self, Game* game, UISprite* sprite) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    void_mfunc_UIRenderable_clear_UIRenderablePtr(ct_stacktrace, 167, 36, self);
    self->sprite = sprite;
    void_push_Array_UIRenderable_300Ptr_UIRenderablePtr(ct_stacktrace, 167, 38, &game->world.ui.renderables, self);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UIRenderable* self, Game* game, TextLG* text_lg) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    void_mfunc_UIRenderable_clear_UIRenderablePtr(ct_stacktrace, 168, 41, self);
    self->text_lg = text_lg;
    void_push_Array_UIRenderable_300Ptr_UIRenderablePtr(ct_stacktrace, 168, 43, &game->world.ui.renderables, self);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_TopNav_update_TopNavPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, TopNav* self, Game* game) {
    UIRenderable renderable = {0};
    Guild* player_guild = NULL;
    SDL_Rect background_dst = {0};

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (!(self->visible)) {
                ct_stacktrace_pop(ct_stacktrace);
return;
}
    if (0 < 0 || 0 > game->world.guilds.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", 0, game->world.guilds.size);
            ct_stacktrace_push(ct_stacktrace, 169, 121);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        player_guild = &game->world.guilds.arr[0];
    void_string_set_Array_char_200Ptr_Array_char_100Ptr(ct_stacktrace, 169, 122, &self->league_text.str, &player_guild->display_name);
    snprintf(self->money_text.str.arr, (size_t) 200, "%lu Muny", player_guild->current_money);
    self->money_text.str.size = strlen(self->money_text.str.arr);
    background_dst = self->background.render_dst.dst;
    self->league_text.render_dst.dst.x = (background_dst.x + 2);
    self->league_text.render_dst.dst.y = (background_dst.y + 2);
    self->money_text.render_dst.dst.x = (background_dst.x + 4);
    self->money_text.render_dst.dst.y = (background_dst.y + 21);
    self->guild_button.render_dst.dst.x = (background_dst.x + 2);
    self->guild_button.render_dst.dst.y = (background_dst.y + 44);
    self->units_button.render_dst.dst = self->guild_button.render_dst.dst;
    self->units_button.render_dst.dst.x += 26;
    self->merchants_button.render_dst.dst = self->units_button.render_dst.dst;
    self->merchants_button.render_dst.dst.x += 26;
    void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 169, 137, &renderable, game, &self->background);
    void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 169, 138, &renderable, game, &self->league_text);
    void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 169, 139, &renderable, game, &self->money_text);
    void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 169, 140, &renderable, game, &self->guild_button);
    void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 169, 141, &renderable, game, &self->units_button);
    void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 169, 142, &renderable, game, &self->merchants_button);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_UIRenderable_set_regular_sprite_UIRenderablePtr_GamePtr_SpritePtr_SDL_RectPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UIRenderable* self, Game* game, Sprite* sprite, SDL_Rect* dst) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    void_mfunc_UIRenderable_clear_UIRenderablePtr(ct_stacktrace, 170, 52, self);
    self->regular_sprite.sprite = sprite;
    self->regular_sprite.dst = *dst;
    void_push_Array_UIRenderable_300Ptr_UIRenderablePtr(ct_stacktrace, 170, 55, &game->world.ui.renderables, self);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_GuildWindow_update_inventory_tab_GuildWindowPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, GuildWindow* self, Game* game) {
    SDL_Point slot_inc = {0};
    int cols = 0;
    SDL_Rect slot_dst = {0};
    SDL_Rect background_dst = {0};
    SDL_Rect start_slot_dst = {0};
    int wrap_at_idx = 0;
    SDL_Rect inventory_item_dst = {0};
    int i = 0;
    UISprite* inventory_slot = NULL;
    UIRenderable renderable = {0};
    TextLG* inventory_quantity_text = NULL;
    InventorySlot* inventory_item = NULL;
    Guild* player_guild = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    background_dst = self->background.render_dst.dst;
    if (0 < 0 || 0 > game->world.guilds.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", 0, game->world.guilds.size);
            ct_stacktrace_push(ct_stacktrace, 171, 1201);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        player_guild = &game->world.guilds.arr[0];
    slot_dst = background_dst;
    slot_dst.x += 250;
    slot_dst.y += 70;
    start_slot_dst = slot_dst;
    slot_inc = SDL_Point_create_point_int_int(ct_stacktrace, 171, 1206, 25, 25);
    cols = 10;
    wrap_at_idx = (cols - 1);
    for (i = 0; i < self->inventory_slots.size; i += 1) {
        if (i < 0 || i > self->inventory_slots.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->inventory_slots.size);
                ct_stacktrace_push(ct_stacktrace, 171, 1210);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            inventory_slot = &self->inventory_slots.arr[i];
        if (i < 0 || i > self->inventory_quantity_texts.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->inventory_quantity_texts.size);
                ct_stacktrace_push(ct_stacktrace, 171, 1211);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            inventory_quantity_text = &self->inventory_quantity_texts.arr[i];
        inventory_slot->render_dst.dst = slot_dst;
        inventory_quantity_text->render_dst.dst = slot_dst;
        inventory_quantity_text->render_dst.dst.x += 16;
        inventory_quantity_text->render_dst.dst.y += 12;
        void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 171, 1216, &renderable, game, inventory_slot);
        if (i < 0 || i > player_guild->inventory.slots.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, player_guild->inventory.slots.size);
                ct_stacktrace_push(ct_stacktrace, 171, 1218);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            inventory_item = &player_guild->inventory.slots.arr[i];
        if (!(inventory_item->slot_is_empty)) {
            inventory_item_dst = slot_dst;
            inventory_item_dst.x += 2;
            inventory_item_dst.y += 2;
            snprintf(inventory_quantity_text->str.arr, (size_t) 200, "%d", inventory_item->shared_item.quantity);
            inventory_quantity_text->str.size = strlen(inventory_quantity_text->str.arr);
            void_mfunc_UIRenderable_set_regular_sprite_UIRenderablePtr_GamePtr_SpritePtr_SDL_RectPtr(ct_stacktrace, 171, 1224, &renderable, game, &inventory_item->shared_item.item->sprite, &inventory_item_dst);
            void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 171, 1225, &renderable, game, inventory_quantity_text);
}
        slot_dst.x += slot_inc.x;
        if (i == wrap_at_idx) {
            wrap_at_idx += cols;
            slot_dst.x = start_slot_dst.x;
            slot_dst.y += slot_inc.y;
        }
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_GuildWindow_update_GuildWindowPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, GuildWindow* self, Game* game) {
    SDL_Rect* background_src = NULL;
    SDL_Rect start_slot_dst = {0};
    SDL_Rect background_dst = {0};
    SDL_Rect slot_dst = {0};
    int cols = 0;
    int base_res_h = 0;
    int base_res_w = 0;
    SDL_Point slot_inc = {0};
    int slot_padding = 0;
    UIRenderable renderable = {0};
    int wrap_at_idx = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (!(self->visible)) {
                ct_stacktrace_pop(ct_stacktrace);
return;
}
    self->background.render_dst.dst.x = 0;
    self->background.render_dst.dst.y = 0;
    if (0 < 0 || 0 > self->background.shared_srcs->srcs.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", 0, self->background.shared_srcs->srcs.size);
            ct_stacktrace_push(ct_stacktrace, 172, 1159);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        background_src = &self->background.shared_srcs->srcs.arr[0];
    base_res_w = game->engine.base_resolution.x;
    base_res_h = game->engine.base_resolution.y;
    self->background.render_dst.dst.x = ((base_res_w / 2) - (background_src->w / 2));
    self->background.render_dst.dst.y = ((base_res_h / 2) - (background_src->h / 2));
    background_dst = self->background.render_dst.dst;
    self->window_text.render_dst.dst = background_dst;
    self->window_text.render_dst.dst.x += 4;
    self->window_text.render_dst.dst.y += 6;
    self->window_close_button.render_dst.dst = background_dst;
    self->window_close_button.render_dst.dst.x += (background_src->w - 15);
    self->window_close_button.render_dst.dst.y += 6;
    slot_dst = background_dst;
    slot_dst.x += 6;
    slot_dst.y += (24 + 6);
    start_slot_dst = slot_dst;
    slot_inc = SDL_Point_create_point_int_int(ct_stacktrace, 172, 1175, 25, 45);
    slot_padding = 2;
    cols = 6;
    wrap_at_idx = (cols - 1);
    void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 172, 1182, &renderable, game, &self->background);
    void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 172, 1183, &renderable, game, &self->window_text);
    void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 172, 1184, &renderable, game, &self->window_close_button);
    self->inventory_tab.render_dst.dst = self->background.render_dst.dst;
    self->inventory_tab.render_dst.dst.x += 168;
    self->inventory_tab.render_dst.dst.y += 28;
    self->inventory_tab_text.render_dst.dst = self->inventory_tab.render_dst.dst;
    self->inventory_tab_text.render_dst.dst.x += 4;
    self->inventory_tab_text.render_dst.dst.y += 6;
    void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 172, 1193, &renderable, game, &self->inventory_tab);
    void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 172, 1194, &renderable, game, &self->inventory_tab_text);
    void_mfunc_GuildWindow_update_inventory_tab_GuildWindowPtr_GamePtr(ct_stacktrace, 172, 1196, self, game);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_UIRenderable_set_unit_UIRenderablePtr_GamePtr_int_SDL_RectPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UIRenderable* self, Game* game, int unit_handle, SDL_Rect* dst) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    void_mfunc_UIRenderable_clear_UIRenderablePtr(ct_stacktrace, 173, 46, self);
    self->unit.handle = unit_handle;
    self->unit.dst = *dst;
    void_push_Array_UIRenderable_300Ptr_UIRenderablePtr(ct_stacktrace, 173, 49, &game->world.ui.renderables, self);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_UnitsWindow_update_status_tab_UnitsWindowPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitsWindow* self, Game* game) {
    int stat_cost = 0;
    SDL_Rect stat_button_dst = {0};
    UIRenderable renderable = {0};
    int text_y_diff = 0;
    SDL_Rect background_dst = {0};
    SDL_Rect active_unit_dst = {0};
    Guild* player_guild = NULL;
    Unit* active_unit = NULL;
    int i = 0;
    StatName stat_name = (StatName) 0;
    UISprite* stat_button = NULL;
    UISprite* stat_icon = NULL;
    TextLG* stat_cost_text = NULL;
    int active_unit_handle = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    background_dst = self->background.render_dst.dst;
    if (0 < 0 || 0 > game->world.guilds.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", 0, game->world.guilds.size);
            ct_stacktrace_push(ct_stacktrace, 174, 621);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        player_guild = &game->world.guilds.arr[0];
    if (self->active_slot_idx < 0 || self->active_slot_idx > player_guild->unit_handles.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->active_slot_idx, player_guild->unit_handles.size);
            ct_stacktrace_push(ct_stacktrace, 174, 622);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        active_unit_handle = player_guild->unit_handles.arr[self->active_slot_idx];
    if (active_unit_handle < 0 || active_unit_handle > game->world.units.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", active_unit_handle, game->world.units.size);
            ct_stacktrace_push(ct_stacktrace, 174, 623);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        active_unit = &game->world.units.arr[active_unit_handle];
    active_unit_dst = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 174, 625, (background_dst.x + 350), (background_dst.y + 100), 0, 0);
    void_mfunc_UIRenderable_set_unit_UIRenderablePtr_GamePtr_int_SDL_RectPtr(ct_stacktrace, 174, 626, &renderable, game, active_unit->handle, &active_unit_dst);
    self->job_text.render_dst.dst = active_unit_dst;
    self->level_text.render_dst.dst = active_unit_dst;
    self->job_level_text.render_dst.dst = active_unit_dst;
    self->experience_text.render_dst.dst = active_unit_dst;
    self->job_experience_text.render_dst.dst = active_unit_dst;
    self->strength_text.render_dst.dst = active_unit_dst;
    self->intelligence_text.render_dst.dst = active_unit_dst;
    self->dexterity_text.render_dst.dst = active_unit_dst;
    self->vitality_text.render_dst.dst = active_unit_dst;
    self->agility_text.render_dst.dst = active_unit_dst;
    self->luck_text.render_dst.dst = active_unit_dst;
    text_y_diff = 20;
    self->job_text.render_dst.dst.y -= 20;
    self->level_text.render_dst.dst.x -= 75;
    self->experience_text.render_dst.dst = self->level_text.render_dst.dst;
    self->experience_text.render_dst.dst.y += text_y_diff;
    self->job_level_text.render_dst.dst = self->experience_text.render_dst.dst;
    self->job_level_text.render_dst.dst.y += text_y_diff;
    self->job_experience_text.render_dst.dst = self->job_level_text.render_dst.dst;
    self->job_experience_text.render_dst.dst.y += text_y_diff;
    self->strength_text.render_dst.dst.x += 50;
    self->intelligence_text.render_dst.dst.x = self->strength_text.render_dst.dst.x;
    self->intelligence_text.render_dst.dst.y += text_y_diff;
    self->dexterity_text.render_dst.dst.x = self->strength_text.render_dst.dst.x;
    self->dexterity_text.render_dst.dst.y += (text_y_diff * 2);
    self->vitality_text.render_dst.dst.x = self->strength_text.render_dst.dst.x;
    self->vitality_text.render_dst.dst.y += (text_y_diff * 3);
    self->agility_text.render_dst.dst.x = self->strength_text.render_dst.dst.x;
    self->agility_text.render_dst.dst.y += (text_y_diff * 4);
    self->luck_text.render_dst.dst.x = self->strength_text.render_dst.dst.x;
    self->luck_text.render_dst.dst.y += (text_y_diff * 5);
    self->available_stat_points_text.render_dst.dst = self->strength_text.render_dst.dst;
    self->available_stat_points_text.render_dst.dst.x += 0;
    self->available_stat_points_text.render_dst.dst.y -= text_y_diff;
    void_string_set_Array_char_200Ptr_Array_char_100Ptr(ct_stacktrace, 174, 665, &self->job_text.str, &active_unit->display_name);
    snprintf(self->level_text.str.arr, (size_t) 200, "Lvl. %d", active_unit->stats.level);
    self->level_text.str.size = strlen(self->level_text.str.arr);
    snprintf(self->job_level_text.str.arr, (size_t) 200, "Job Lvl. %d", active_unit->stats.job_level);
    self->job_level_text.str.size = strlen(self->job_level_text.str.arr);
    snprintf(self->experience_text.str.arr, (size_t) 200, "Exp: %lu / %lu", active_unit->stats.experience.value, active_unit->stats.experience.max);
    self->experience_text.str.size = strlen(self->experience_text.str.arr);
    snprintf(self->job_experience_text.str.arr, (size_t) 200, "Job Exp: %lu / %lu", active_unit->stats.job_experience.value, active_unit->stats.job_experience.max);
    self->job_experience_text.str.size = strlen(self->job_experience_text.str.arr);
    snprintf(self->strength_text.str.arr, (size_t) 200, "Strength: %lu", active_unit->stats.strength.value);
    self->strength_text.str.size = strlen(self->strength_text.str.arr);
    snprintf(self->intelligence_text.str.arr, (size_t) 200, "Intelligence: %lu", active_unit->stats.intelligence.value);
    self->intelligence_text.str.size = strlen(self->intelligence_text.str.arr);
    snprintf(self->dexterity_text.str.arr, (size_t) 200, "Dexterity: %lu", active_unit->stats.dexterity.value);
    self->dexterity_text.str.size = strlen(self->dexterity_text.str.arr);
    snprintf(self->vitality_text.str.arr, (size_t) 200, "Vitality: %lu", active_unit->stats.vitality.value);
    self->vitality_text.str.size = strlen(self->vitality_text.str.arr);
    snprintf(self->agility_text.str.arr, (size_t) 200, "Agility: %lu", active_unit->stats.agility.value);
    self->agility_text.str.size = strlen(self->agility_text.str.arr);
    snprintf(self->luck_text.str.arr, (size_t) 200, "Luck: %lu", active_unit->stats.luck.value);
    self->luck_text.str.size = strlen(self->luck_text.str.arr);
    snprintf(self->available_stat_points_text.str.arr, (size_t) 200, "Available Stat Points: %d", active_unit->available_stat_points);
    self->available_stat_points_text.str.size = strlen(self->available_stat_points_text.str.arr);
    void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 174, 678, &renderable, game, &self->available_stat_points_text);
    stat_button_dst = self->strength_text.render_dst.dst;
    stat_button_dst.x += 80;
    stat_button_dst.y -= 1;
    for (i = 0; i < self->increase_stat_buttons.size; i++) {
        stat_button = &self->increase_stat_buttons.arr[i];
        stat_name = (StatName)((i + 1));
        if (i < 0 || i > self->increase_stat_icons.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->increase_stat_icons.size);
                ct_stacktrace_push(ct_stacktrace, 174, 685);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            stat_icon = &self->increase_stat_icons.arr[i];
        if (i < 0 || i > self->increase_stat_cost_texts.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->increase_stat_cost_texts.size);
                ct_stacktrace_push(ct_stacktrace, 174, 686);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            stat_cost_text = &self->increase_stat_cost_texts.arr[i];
        stat_button->render_dst.dst = stat_button_dst;
        stat_icon->render_dst.dst = stat_button_dst;
        stat_icon->render_dst.dst.x += 2;
        stat_icon->render_dst.dst.y += 3;
        stat_cost_text->render_dst.dst = stat_button_dst;
        stat_cost_text->render_dst.dst.x += 16;
        stat_cost = 0;
        if (stat_name == StatName_Strength) {
            stat_cost = int_get_stat_cost_Uint64(ct_stacktrace, 174, 695, active_unit->stats.strength.value);
            snprintf(stat_cost_text->str.arr, (size_t) 200, "%d", stat_cost);
            stat_cost_text->str.size = strlen(stat_cost_text->str.arr);
}
        else if (stat_name == StatName_Intelligence) {
            stat_cost = int_get_stat_cost_Uint64(ct_stacktrace, 174, 698, active_unit->stats.intelligence.value);
            snprintf(stat_cost_text->str.arr, (size_t) 200, "%d", stat_cost);
            stat_cost_text->str.size = strlen(stat_cost_text->str.arr);
}
        else if (stat_name == StatName_Dexterity) {
            stat_cost = int_get_stat_cost_Uint64(ct_stacktrace, 174, 701, active_unit->stats.dexterity.value);
            snprintf(stat_cost_text->str.arr, (size_t) 200, "%d", stat_cost);
            stat_cost_text->str.size = strlen(stat_cost_text->str.arr);
}
        else if (stat_name == StatName_Vitality) {
            stat_cost = int_get_stat_cost_Uint64(ct_stacktrace, 174, 704, active_unit->stats.vitality.value);
            snprintf(stat_cost_text->str.arr, (size_t) 200, "%d", stat_cost);
            stat_cost_text->str.size = strlen(stat_cost_text->str.arr);
}
        else if (stat_name == StatName_Agility) {
            stat_cost = int_get_stat_cost_Uint64(ct_stacktrace, 174, 707, active_unit->stats.agility.value);
            snprintf(stat_cost_text->str.arr, (size_t) 200, "%d", stat_cost);
            stat_cost_text->str.size = strlen(stat_cost_text->str.arr);
}
        else if (stat_name == StatName_Luck) {
            stat_cost = int_get_stat_cost_Uint64(ct_stacktrace, 174, 710, active_unit->stats.luck.value);
            snprintf(stat_cost_text->str.arr, (size_t) 200, "%d", stat_cost);
            stat_cost_text->str.size = strlen(stat_cost_text->str.arr);
}
        if (active_unit->available_stat_points >= stat_cost) {
            void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 174, 713, &renderable, game, stat_button);
            void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 174, 714, &renderable, game, stat_icon);
}
        void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 174, 715, &renderable, game, stat_cost_text);
        stat_button_dst.y += text_y_diff;
}
    void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 174, 718, &renderable, game, &self->job_text);
    void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 174, 719, &renderable, game, &self->level_text);
    void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 174, 720, &renderable, game, &self->experience_text);
    void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 174, 721, &renderable, game, &self->job_level_text);
    void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 174, 722, &renderable, game, &self->job_experience_text);
    void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 174, 723, &renderable, game, &self->strength_text);
    void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 174, 724, &renderable, game, &self->intelligence_text);
    void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 174, 725, &renderable, game, &self->dexterity_text);
    void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 174, 726, &renderable, game, &self->vitality_text);
    void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 174, 727, &renderable, game, &self->agility_text);
    void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 174, 728, &renderable, game, &self->luck_text);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_UnitsWindow_update_inventory_tab_UnitsWindowPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitsWindow* self, Game* game) {
    SDL_Rect inventory_item_dst = {0};
    InventorySlot* inventory_item = NULL;
    Unit* active_unit = NULL;
    Guild* player_guild = NULL;
    SDL_Rect active_unit_dst = {0};
    int i = 0;
    UIRenderable renderable = {0};
    SDL_Rect start_slot_dst = {0};
    SDL_Rect background_dst = {0};
    SDL_Rect slot_dst = {0};
    int cols = 0;
    int active_unit_handle = 0;
    SDL_Point slot_inc = {0};
    int wrap_at_idx = 0;
    UISprite* inventory_slot = NULL;
    TextLG* inventory_quantity_text = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    background_dst = self->background.render_dst.dst;
    if (0 < 0 || 0 > game->world.guilds.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", 0, game->world.guilds.size);
            ct_stacktrace_push(ct_stacktrace, 175, 733);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        player_guild = &game->world.guilds.arr[0];
    if (self->active_slot_idx < 0 || self->active_slot_idx > player_guild->unit_handles.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->active_slot_idx, player_guild->unit_handles.size);
            ct_stacktrace_push(ct_stacktrace, 175, 734);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        active_unit_handle = player_guild->unit_handles.arr[self->active_slot_idx];
    if (active_unit_handle < 0 || active_unit_handle > game->world.units.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", active_unit_handle, game->world.units.size);
            ct_stacktrace_push(ct_stacktrace, 175, 735);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        active_unit = &game->world.units.arr[active_unit_handle];
    active_unit_dst = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 175, 736, (background_dst.x + 210), (background_dst.y + 70), 0, 0);
    void_mfunc_UIRenderable_set_unit_UIRenderablePtr_GamePtr_int_SDL_RectPtr(ct_stacktrace, 175, 737, &renderable, game, active_unit->handle, &active_unit_dst);
    slot_dst = background_dst;
    slot_dst.x += 250;
    slot_dst.y += 70;
    start_slot_dst = slot_dst;
    slot_inc = SDL_Point_create_point_int_int(ct_stacktrace, 175, 742, 25, 25);
    cols = 10;
    wrap_at_idx = (cols - 1);
    for (i = 0; i < self->inventory_slots.size; i += 1) {
        if (i < 0 || i > self->inventory_slots.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->inventory_slots.size);
                ct_stacktrace_push(ct_stacktrace, 175, 746);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            inventory_slot = &self->inventory_slots.arr[i];
        if (i < 0 || i > self->inventory_quantity_texts.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->inventory_quantity_texts.size);
                ct_stacktrace_push(ct_stacktrace, 175, 747);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            inventory_quantity_text = &self->inventory_quantity_texts.arr[i];
        inventory_slot->render_dst.dst = slot_dst;
        inventory_quantity_text->render_dst.dst = slot_dst;
        inventory_quantity_text->render_dst.dst.x += 16;
        inventory_quantity_text->render_dst.dst.y += 12;
        void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 175, 752, &renderable, game, inventory_slot);
        if (i < 0 || i > active_unit->inventory.slots.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, active_unit->inventory.slots.size);
                ct_stacktrace_push(ct_stacktrace, 175, 754);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            inventory_item = &active_unit->inventory.slots.arr[i];
        if (!(inventory_item->slot_is_empty)) {
            inventory_item_dst = slot_dst;
            inventory_item_dst.x += 2;
            inventory_item_dst.y += 2;
            snprintf(inventory_quantity_text->str.arr, (size_t) 200, "%d", inventory_item->shared_item.quantity);
            inventory_quantity_text->str.size = strlen(inventory_quantity_text->str.arr);
            void_mfunc_UIRenderable_set_regular_sprite_UIRenderablePtr_GamePtr_SpritePtr_SDL_RectPtr(ct_stacktrace, 175, 760, &renderable, game, &inventory_item->shared_item.item->sprite, &inventory_item_dst);
            void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 175, 761, &renderable, game, inventory_quantity_text);
}
        slot_dst.x += slot_inc.x;
        if (i == wrap_at_idx) {
            wrap_at_idx += cols;
            slot_dst.x = start_slot_dst.x;
            slot_dst.y += slot_inc.y;
        }
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_UnitsWindow_update_ability_tab_UnitsWindowPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitsWindow* self, Game* game) {
    SDL_Rect job_ability_dst = {0};
    int ability_skill_points = 0;
    SharedAbility* job_ability = NULL;
    TextLG* ability_skill_point_text = NULL;
    Unit* active_unit = NULL;
    Guild* player_guild = NULL;
    SDL_Rect active_unit_dst = {0};
    int i = 0;
    UIRenderable renderable = {0};
    SDL_Rect start_slot_dst = {0};
    SDL_Rect background_dst = {0};
    SDL_Rect slot_dst = {0};
    int cols = 0;
    int active_unit_handle = 0;
    SDL_Point slot_inc = {0};
    int wrap_at_idx = 0;
    UISprite* ability_slot = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    background_dst = self->background.render_dst.dst;
    if (0 < 0 || 0 > game->world.guilds.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", 0, game->world.guilds.size);
            ct_stacktrace_push(ct_stacktrace, 177, 773);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        player_guild = &game->world.guilds.arr[0];
    if (self->active_slot_idx < 0 || self->active_slot_idx > player_guild->unit_handles.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->active_slot_idx, player_guild->unit_handles.size);
            ct_stacktrace_push(ct_stacktrace, 177, 774);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        active_unit_handle = player_guild->unit_handles.arr[self->active_slot_idx];
    if (active_unit_handle < 0 || active_unit_handle > game->world.units.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", active_unit_handle, game->world.units.size);
            ct_stacktrace_push(ct_stacktrace, 177, 775);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        active_unit = &game->world.units.arr[active_unit_handle];
    active_unit_dst = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 177, 776, (background_dst.x + 210), (background_dst.y + 70), 0, 0);
    void_mfunc_UIRenderable_set_unit_UIRenderablePtr_GamePtr_int_SDL_RectPtr(ct_stacktrace, 177, 777, &renderable, game, active_unit->handle, &active_unit_dst);
    snprintf(self->available_skill_points_text.str.arr, (size_t) 200, "Available Skill Points: %d", active_unit->available_skill_points);
    self->available_skill_points_text.str.size = strlen(self->available_skill_points_text.str.arr);
    self->available_skill_points_text.render_dst.dst = active_unit_dst;
    self->available_skill_points_text.render_dst.dst.x += 100;
    void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 177, 781, &renderable, game, &self->available_skill_points_text);
    slot_dst = background_dst;
    slot_dst.x += 250;
    slot_dst.y += 90;
    start_slot_dst = slot_dst;
    slot_inc = SDL_Point_create_point_int_int(ct_stacktrace, 177, 786, 25, 25);
    cols = 10;
    wrap_at_idx = (cols - 1);
    for (i = 0; i < self->ability_slots.size; i += 1) {
        if (i < 0 || i > self->ability_slots.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->ability_slots.size);
                ct_stacktrace_push(ct_stacktrace, 177, 790);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            ability_slot = &self->ability_slots.arr[i];
        if (i < 0 || i > self->ability_skill_point_texts.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->ability_skill_point_texts.size);
                ct_stacktrace_push(ct_stacktrace, 177, 791);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            ability_skill_point_text = &self->ability_skill_point_texts.arr[i];
        ability_slot->render_dst.dst = slot_dst;
        ability_skill_point_text->render_dst.dst = slot_dst;
        ability_skill_point_text->render_dst.dst.x += 16;
        ability_skill_point_text->render_dst.dst.y += 12;
        void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 177, 796, &renderable, game, ability_slot);
        if (i <= (active_unit->job_abilities.size - 1)) {
            if (i < 0 || i > active_unit->job_abilities.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", i, active_unit->job_abilities.size);
                    ct_stacktrace_push(ct_stacktrace, 177, 799);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                job_ability = &active_unit->job_abilities.arr[i];
            ability_skill_points = int_mfunc_Unit_get_ability_skill_points_UnitPtr_AbilityName(ct_stacktrace, 177, 801, active_unit, job_ability->ability->ability_name);
            job_ability_dst = slot_dst;
            job_ability_dst.x += 2;
            job_ability_dst.y += 2;
            snprintf(ability_skill_point_text->str.arr, (size_t) 200, "%d", ability_skill_points);
            ability_skill_point_text->str.size = strlen(ability_skill_point_text->str.arr);
            void_mfunc_UIRenderable_set_regular_sprite_UIRenderablePtr_GamePtr_SpritePtr_SDL_RectPtr(ct_stacktrace, 177, 806, &renderable, game, &job_ability->ability->portrait, &job_ability_dst);
            void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 177, 807, &renderable, game, ability_skill_point_text);
}
        slot_dst.x += slot_inc.x;
        if (i == wrap_at_idx) {
            wrap_at_idx += cols;
            slot_dst.x = start_slot_dst.x;
            slot_dst.y += slot_inc.y;
        }
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_UIRenderable_set_unit_sprite_UIRenderablePtr_GamePtr_UnitSpritePtr_SDL_RectPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UIRenderable* self, Game* game, UnitSprite* sprite, SDL_Rect* dst) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    void_mfunc_UIRenderable_clear_UIRenderablePtr(ct_stacktrace, 181, 58, self);
    self->unit_sprite.sprite = sprite;
    self->unit_sprite.dst = *dst;
    void_push_Array_UIRenderable_300Ptr_UIRenderablePtr(ct_stacktrace, 181, 61, &game->world.ui.renderables, self);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_UnitsWindow_update_job_change_tab_UnitsWindowPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitsWindow* self, Game* game) {
    SDL_Rect row_3_slot_1_unit_dst = {0};
    SDL_Rect row_3_slot_0_unit_dst = {0};
    bool can_tier_one_job_change = false;
    UISprite* row_3_slot_1 = NULL;
    bool had_previous_tier2_job = false;
    UnitName slot_unit_name = (UnitName) 0;
    Unit* active_unit = NULL;
    Guild* player_guild = NULL;
    int job_row_1_y = 0;
    int job_row_3_idx = 0;
    int job_row_2_x = 0;
    Unit* unit = NULL;
    SDL_Rect active_unit_dst = {0};
    int i = 0;
    SDL_Rect background_dst = {0};
    SDL_Rect slot_dst = {0};
    UISprite* row_3_slot_0 = NULL;
    int active_unit_handle = 0;
    UISprite* slot = NULL;
    int job_row_2_y = 0;
    int job_tier = 0;
    bool can_job_change = false;
    int job_row_1_x = 0;
    int job_row_3_y = 0;
    UIRenderable renderable = {0};
    SDL_Rect slot_row_3_dst = {0};

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    background_dst = self->background.render_dst.dst;
    if (0 < 0 || 0 > game->world.guilds.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", 0, game->world.guilds.size);
            ct_stacktrace_push(ct_stacktrace, 182, 819);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        player_guild = &game->world.guilds.arr[0];
    if (self->active_slot_idx < 0 || self->active_slot_idx > player_guild->unit_handles.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->active_slot_idx, player_guild->unit_handles.size);
            ct_stacktrace_push(ct_stacktrace, 182, 820);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        active_unit_handle = player_guild->unit_handles.arr[self->active_slot_idx];
    if (active_unit_handle < 0 || active_unit_handle > game->world.units.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", active_unit_handle, game->world.units.size);
            ct_stacktrace_push(ct_stacktrace, 182, 821);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        active_unit = &game->world.units.arr[active_unit_handle];
    active_unit_dst = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 182, 822, (background_dst.x + 350), (background_dst.y + 100), 0, 0);
    job_tier = int_get_unit_name_job_tier_UnitName(ct_stacktrace, 182, 823, active_unit->unit_name);
    can_job_change = bool_unit_can_job_change_UnitName_int(ct_stacktrace, 182, 824, active_unit->unit_name, active_unit->stats.job_level);
    job_row_1_x = (background_dst.x + 335);
    job_row_2_x = (background_dst.x + 235);
    job_row_1_y = (background_dst.y + 70);
    job_row_2_y = (job_row_1_y + 70);
    job_row_3_y = (job_row_2_y + 70);
    unit = UnitPtr_mfunc_UnitDB_get_unit_UnitDBPtr_UnitName(ct_stacktrace, 182, 830, &game->unit_db, UnitName_Explorer);
    active_unit_dst = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 182, 831, job_row_1_x, job_row_1_y, 0, 0);
    void_mfunc_UIRenderable_set_unit_sprite_UIRenderablePtr_GamePtr_UnitSpritePtr_SDL_RectPtr(ct_stacktrace, 182, 832, &renderable, game, &unit->sprite, &active_unit_dst);
    slot_dst = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 182, 834, job_row_2_x, job_row_2_y, 0, 0);
    slot_row_3_dst = slot_dst;
    slot_row_3_dst.y = job_row_3_y;
    job_row_3_idx = 0;
    for (i = 0; i < self->job_change_row_2_slots.size; i++) {
        slot = &self->job_change_row_2_slots.arr[i];
        slot_unit_name = slot->ui_event.unit_name;
        slot->render_dst.dst = slot_dst;
        had_previous_tier2_job = false;
        if (job_row_3_idx < 0 || job_row_3_idx > self->job_change_row_3_slots.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", job_row_3_idx, self->job_change_row_3_slots.size);
                ct_stacktrace_push(ct_stacktrace, 182, 842);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            row_3_slot_0 = &self->job_change_row_3_slots.arr[job_row_3_idx];
        job_row_3_idx += 1;
        if (job_row_3_idx < 0 || job_row_3_idx > self->job_change_row_3_slots.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", job_row_3_idx, self->job_change_row_3_slots.size);
                ct_stacktrace_push(ct_stacktrace, 182, 844);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            row_3_slot_1 = &self->job_change_row_3_slots.arr[job_row_3_idx];
        job_row_3_idx += 1;
        if (job_tier == 2) {
            if ((row_3_slot_0->ui_event.unit_name == active_unit->unit_name || row_3_slot_1->ui_event.unit_name == active_unit->unit_name)) {
                had_previous_tier2_job = true;
    }
}
        if ((can_job_change && job_tier == 0)) {
            void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 182, 850, &renderable, game, slot);
}
        active_unit_dst = slot_dst;
        active_unit_dst.x += 2;
        active_unit_dst.y += 2;
        can_tier_one_job_change = (can_job_change && job_tier == 0);
        if ((can_tier_one_job_change || had_previous_tier2_job)) {
            unit = UnitPtr_mfunc_UnitDB_get_unit_UnitDBPtr_UnitName(ct_stacktrace, 182, 858, &game->unit_db, slot->ui_event.unit_name);
            void_mfunc_UIRenderable_set_unit_sprite_UIRenderablePtr_GamePtr_UnitSpritePtr_SDL_RectPtr(ct_stacktrace, 182, 859, &renderable, game, &unit->sprite, &active_unit_dst);
}
        else if ((job_tier == 1 && slot->ui_event.unit_name == active_unit->unit_name)) {
            unit = UnitPtr_mfunc_UnitDB_get_unit_UnitDBPtr_UnitName(ct_stacktrace, 182, 863, &game->unit_db, slot->ui_event.unit_name);
            void_mfunc_UIRenderable_set_unit_sprite_UIRenderablePtr_GamePtr_UnitSpritePtr_SDL_RectPtr(ct_stacktrace, 182, 864, &renderable, game, &unit->sprite, &active_unit_dst);
}
        slot_row_3_dst = slot_dst;
        slot_row_3_dst.y = job_row_3_y;
        row_3_slot_0->render_dst.dst = slot_row_3_dst;
        row_3_slot_1->render_dst.dst = slot_row_3_dst;
        row_3_slot_0->render_dst.dst.x -= 50;
        row_3_slot_1->render_dst.dst.x += 50;
        row_3_slot_0_unit_dst = row_3_slot_0->render_dst.dst;
        row_3_slot_0_unit_dst.x += 2;
        row_3_slot_0_unit_dst.y += 2;
        row_3_slot_1_unit_dst = row_3_slot_1->render_dst.dst;
        row_3_slot_1_unit_dst.x += 2;
        row_3_slot_1_unit_dst.y += 2;
        if (((can_job_change && job_tier == 1) && slot_unit_name == active_unit->unit_name)) {
            void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 182, 882, &renderable, game, row_3_slot_0);
            unit = UnitPtr_mfunc_UnitDB_get_unit_UnitDBPtr_UnitName(ct_stacktrace, 182, 884, &game->unit_db, row_3_slot_0->ui_event.unit_name);
            void_mfunc_UIRenderable_set_unit_sprite_UIRenderablePtr_GamePtr_UnitSpritePtr_SDL_RectPtr(ct_stacktrace, 182, 885, &renderable, game, &unit->sprite, &row_3_slot_0_unit_dst);
            void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 182, 887, &renderable, game, row_3_slot_1);
            unit = UnitPtr_mfunc_UnitDB_get_unit_UnitDBPtr_UnitName(ct_stacktrace, 182, 889, &game->unit_db, row_3_slot_1->ui_event.unit_name);
            void_mfunc_UIRenderable_set_unit_sprite_UIRenderablePtr_GamePtr_UnitSpritePtr_SDL_RectPtr(ct_stacktrace, 182, 890, &renderable, game, &unit->sprite, &row_3_slot_1_unit_dst);
}
        else if (job_tier == 2) {
            if (row_3_slot_0->ui_event.unit_name == active_unit->unit_name) {
                unit = UnitPtr_mfunc_UnitDB_get_unit_UnitDBPtr_UnitName(ct_stacktrace, 182, 893, &game->unit_db, row_3_slot_0->ui_event.unit_name);
                void_mfunc_UIRenderable_set_unit_sprite_UIRenderablePtr_GamePtr_UnitSpritePtr_SDL_RectPtr(ct_stacktrace, 182, 894, &renderable, game, &unit->sprite, &row_3_slot_0_unit_dst);
}
            else if (row_3_slot_1->ui_event.unit_name == active_unit->unit_name) {
                unit = UnitPtr_mfunc_UnitDB_get_unit_UnitDBPtr_UnitName(ct_stacktrace, 182, 896, &game->unit_db, row_3_slot_1->ui_event.unit_name);
                void_mfunc_UIRenderable_set_unit_sprite_UIRenderablePtr_GamePtr_UnitSpritePtr_SDL_RectPtr(ct_stacktrace, 182, 897, &renderable, game, &unit->sprite, &row_3_slot_1_unit_dst);
    }
}
        slot_dst.x += 50;
}
    if ((!(can_job_change) && job_tier != 2)) {
        if (job_tier == 0) {
            void_string_set_literal_Array_char_200Ptr_charPtr(ct_stacktrace, 182, 904, &self->next_job_change_level_text.str, "Job Change Available at Job Lvl. 10.");
            self->next_job_change_level_text.render_dst.dst.x = (background_dst.x + 270);
            self->next_job_change_level_text.render_dst.dst.y = job_row_2_y;
            void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 182, 907, &renderable, game, &self->next_job_change_level_text);
}
        else if (job_tier == 1) {
            void_string_set_literal_Array_char_200Ptr_charPtr(ct_stacktrace, 182, 909, &self->next_job_change_level_text.str, "Job Change Available at Job Lvl. 40.");
            self->next_job_change_level_text.render_dst.dst.x = (background_dst.x + 270);
            self->next_job_change_level_text.render_dst.dst.y = job_row_3_y;
            void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 182, 912, &renderable, game, &self->next_job_change_level_text);
        }
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_UnitsWindow_update_ai_tab_UnitsWindowPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitsWindow* self, Game* game) {
    SDL_Rect ability_dst = {0};
    UISprite* active_slot = NULL;
    SDL_Rect job_ability_dst = {0};
    SharedAbility* ability = NULL;
    Guild* player_guild = NULL;
    AIAbility* ai_ability = NULL;
    SDL_Rect active_unit_dst = {0};
    int i = 0;
    UIRenderable renderable = {0};
    SDL_Rect remove_icon_dst = {0};
    SDL_Rect background_dst = {0};
    SDL_Rect slot_dst = {0};
    int cols = 0;
    int active_unit_handle = 0;
    SDL_Point slot_inc = {0};
    int wrap_at_idx = 0;
    UISprite* ai_ability_slot = NULL;
    SDL_Rect start_slot_dst = {0};
    UISprite* ai_option_slot = NULL;
    TextLG* ai_ability_order_text = NULL;
    Unit* active_unit = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    background_dst = self->background.render_dst.dst;
    if (0 < 0 || 0 > game->world.guilds.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", 0, game->world.guilds.size);
            ct_stacktrace_push(ct_stacktrace, 183, 917);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        player_guild = &game->world.guilds.arr[0];
    if (self->active_slot_idx < 0 || self->active_slot_idx > player_guild->unit_handles.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", self->active_slot_idx, player_guild->unit_handles.size);
            ct_stacktrace_push(ct_stacktrace, 183, 918);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        active_unit_handle = player_guild->unit_handles.arr[self->active_slot_idx];
    if (active_unit_handle < 0 || active_unit_handle > game->world.units.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", active_unit_handle, game->world.units.size);
            ct_stacktrace_push(ct_stacktrace, 183, 919);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        active_unit = &game->world.units.arr[active_unit_handle];
    active_unit_dst = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 183, 920, (background_dst.x + 350), (background_dst.y + 100), 0, 0);
    void_mfunc_UIRenderable_set_unit_UIRenderablePtr_GamePtr_int_SDL_RectPtr(ct_stacktrace, 183, 921, &renderable, game, active_unit->handle, &active_unit_dst);
    slot_dst = background_dst;
    slot_dst.x += 250;
    slot_dst.y += 90;
    start_slot_dst = slot_dst;
    slot_inc = SDL_Point_create_point_int_int(ct_stacktrace, 183, 926, 50, 25);
    cols = 6;
    wrap_at_idx = (cols - 1);
    for (i = 0; i < self->ai_ability_slots.size; i++) {
        ai_ability_slot = &self->ai_ability_slots.arr[i];
        if (i < 0 || i > self->ai_ability_slot_order_texts.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->ai_ability_slot_order_texts.size);
                ct_stacktrace_push(ct_stacktrace, 183, 930);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            ai_ability_order_text = &self->ai_ability_slot_order_texts.arr[i];
        ai_ability_slot->render_dst.dst = slot_dst;
        ai_ability_order_text->render_dst.dst = slot_dst;
        ai_ability_order_text->render_dst.dst.x += 16;
        ai_ability_order_text->render_dst.dst.y += 12;
        void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 183, 935, &renderable, game, ai_ability_slot);
        if (i <= (active_unit->ai_abilities.size - 1)) {
            if (i < 0 || i > active_unit->ai_abilities.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", i, active_unit->ai_abilities.size);
                    ct_stacktrace_push(ct_stacktrace, 183, 938);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                ai_ability = &active_unit->ai_abilities.arr[i];
            if (!(ai_ability->is_empty)) {
                if (ai_ability->unit_ability_handle < 0 || ai_ability->unit_ability_handle > active_unit->abilities.size - 1) {
                        printf("Out of bounds error: idx: %d size: %d.\n", ai_ability->unit_ability_handle, active_unit->abilities.size);
                        ct_stacktrace_push(ct_stacktrace, 183, 940);
                        ct_stacktrace_print(ct_stacktrace);
                        exit(1);
                    }
                    ability = &active_unit->abilities.arr[ai_ability->unit_ability_handle];
                job_ability_dst = slot_dst;
                job_ability_dst.x += 2;
                job_ability_dst.y += 2;
                void_mfunc_UIRenderable_set_regular_sprite_UIRenderablePtr_GamePtr_SpritePtr_SDL_RectPtr(ct_stacktrace, 183, 944, &renderable, game, &ability->ability->portrait, &job_ability_dst);
    }
}
        snprintf(ai_ability_order_text->str.arr, (size_t) 200, "%d", (i + 1));
        ai_ability_order_text->str.size = strlen(ai_ability_order_text->str.arr);
        void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 183, 946, &renderable, game, ai_ability_order_text);
        slot_dst.y += slot_inc.y;
        if (i == wrap_at_idx) {
            wrap_at_idx += cols;
            slot_dst.x += slot_inc.x;
            slot_dst.y = start_slot_dst.y;
    }
}
    if (self->ai_ability_dropdown_visible) {
        if (self->ai_ability_active_idx < 0 || self->ai_ability_active_idx > self->ai_ability_slots.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", self->ai_ability_active_idx, self->ai_ability_slots.size);
                ct_stacktrace_push(ct_stacktrace, 183, 955);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            active_slot = &self->ai_ability_slots.arr[self->ai_ability_active_idx];
        self->ai_ability_dropdown_background.render_dst.dst = active_slot->render_dst.dst;
        self->ai_ability_dropdown_background.render_dst.dst.x += 25;
        self->ai_ability_dropdown_background.render_dst.dst.y += 0;
        void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 183, 959, &renderable, game, &self->ai_ability_dropdown_background);
        slot_dst = self->ai_ability_dropdown_background.render_dst.dst;
        slot_dst.x += 3;
        slot_dst.y += 2;
        start_slot_dst = slot_dst;
        slot_inc = SDL_Point_create_point_int_int(ct_stacktrace, 183, 965, 25, 25);
        cols = 3;
        wrap_at_idx = (cols - 1);
        for (i = 0; i < self->ai_ability_dropdown_options.size; i++) {
            ai_option_slot = &self->ai_ability_dropdown_options.arr[i];
            ai_option_slot->render_dst.dst = slot_dst;
            void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 183, 970, &renderable, game, ai_option_slot);
            if (i == (self->ai_ability_dropdown_options.size - 1)) {
                remove_icon_dst = slot_dst;
                remove_icon_dst.x += 2;
                remove_icon_dst.y += 2;
                self->ai_ability_remove_icon.render_dst.dst = remove_icon_dst;
                void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 183, 977, &renderable, game, &self->ai_ability_remove_icon);
}
            else if (i <= (active_unit->abilities.size - 1)) {
                if (i < 0 || i > active_unit->abilities.size - 1) {
                        printf("Out of bounds error: idx: %d size: %d.\n", i, active_unit->abilities.size);
                        ct_stacktrace_push(ct_stacktrace, 183, 979);
                        ct_stacktrace_print(ct_stacktrace);
                        exit(1);
                    }
                    ability = &active_unit->abilities.arr[i];
                ability_dst = slot_dst;
                ability_dst.x += 2;
                ability_dst.y += 2;
                void_mfunc_UIRenderable_set_regular_sprite_UIRenderablePtr_GamePtr_SpritePtr_SDL_RectPtr(ct_stacktrace, 183, 983, &renderable, game, &ability->ability->portrait, &ability_dst);
}
            slot_dst.x += slot_inc.x;
            if (i == wrap_at_idx) {
                wrap_at_idx += cols;
                slot_dst.x = start_slot_dst.x;
                slot_dst.y += slot_inc.y;
            }
        }
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_UnitsWindow_update_UnitsWindowPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitsWindow* self, Game* game) {
    SDL_Rect unit_dst = {0};
    int unit_handle = 0;
    int wrap_at_idx = 0;
    UIRenderable renderable = {0};
    SDL_Point slot_inc = {0};
    int base_res_w = 0;
    int i = 0;
    int base_res_h = 0;
    SDL_Rect slot_dst = {0};
    SDL_Rect background_dst = {0};
    SDL_Rect start_slot_dst = {0};
    int cols = 0;
    Guild* player_guild = NULL;
    int slot_padding = 0;
    SDL_Rect* background_src = NULL;
    UISprite* unit_slot = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (!(self->visible)) {
                ct_stacktrace_pop(ct_stacktrace);
return;
}
    self->background.render_dst.dst.x = 0;
    self->background.render_dst.dst.y = 0;
    if (0 < 0 || 0 > self->background.shared_srcs->srcs.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", 0, self->background.shared_srcs->srcs.size);
            ct_stacktrace_push(ct_stacktrace, 184, 520);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        background_src = &self->background.shared_srcs->srcs.arr[0];
    base_res_w = game->engine.base_resolution.x;
    base_res_h = game->engine.base_resolution.y;
    self->background.render_dst.dst.x = ((base_res_w / 2) - (background_src->w / 2));
    self->background.render_dst.dst.y = ((base_res_h / 2) - (background_src->h / 2));
    background_dst = self->background.render_dst.dst;
    self->window_text.render_dst.dst = background_dst;
    self->window_text.render_dst.dst.x += 4;
    self->window_text.render_dst.dst.y += 6;
    self->window_close_button.render_dst.dst = background_dst;
    self->window_close_button.render_dst.dst.x += (background_src->w - 15);
    self->window_close_button.render_dst.dst.y += 6;
    slot_dst = background_dst;
    slot_dst.x += 6;
    slot_dst.y += (24 + 6);
    start_slot_dst = slot_dst;
    slot_inc = SDL_Point_create_point_int_int(ct_stacktrace, 184, 536, 25, 45);
    slot_padding = 2;
    cols = 6;
    wrap_at_idx = (cols - 1);
    void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 184, 543, &renderable, game, &self->background);
    void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 184, 544, &renderable, game, &self->window_text);
    void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 184, 545, &renderable, game, &self->window_close_button);
    self->status_tab.render_dst.dst = background_dst;
    self->status_tab.render_dst.dst.x += 168;
    self->status_tab.render_dst.dst.y += 28;
    self->inventory_tab.render_dst.dst = self->status_tab.render_dst.dst;
    self->inventory_tab.render_dst.dst.x += 66;
    self->ability_tab.render_dst.dst = self->inventory_tab.render_dst.dst;
    self->ability_tab.render_dst.dst.x += 66;
    self->job_change_tab.render_dst.dst = self->ability_tab.render_dst.dst;
    self->job_change_tab.render_dst.dst.x += 66;
    self->ai_tab.render_dst.dst = self->job_change_tab.render_dst.dst;
    self->ai_tab.render_dst.dst.x += 66;
    self->status_tab_text.render_dst.dst = self->status_tab.render_dst.dst;
    self->status_tab_text.render_dst.dst.x += 4;
    self->status_tab_text.render_dst.dst.y += 6;
    self->inventory_tab_text.render_dst.dst = self->inventory_tab.render_dst.dst;
    self->inventory_tab_text.render_dst.dst.x += 4;
    self->inventory_tab_text.render_dst.dst.y += 6;
    self->ability_tab_text.render_dst.dst = self->ability_tab.render_dst.dst;
    self->ability_tab_text.render_dst.dst.x += 4;
    self->ability_tab_text.render_dst.dst.y += 6;
    self->job_change_tab_text.render_dst.dst = self->job_change_tab.render_dst.dst;
    self->job_change_tab_text.render_dst.dst.x += 4;
    self->job_change_tab_text.render_dst.dst.y += 6;
    self->ai_tab_text.render_dst.dst = self->ai_tab.render_dst.dst;
    self->ai_tab_text.render_dst.dst.x += 4;
    self->ai_tab_text.render_dst.dst.y += 6;
    void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 184, 574, &renderable, game, &self->status_tab);
    void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 184, 575, &renderable, game, &self->inventory_tab);
    void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 184, 576, &renderable, game, &self->ability_tab);
    void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 184, 577, &renderable, game, &self->job_change_tab);
    void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 184, 578, &renderable, game, &self->ai_tab);
    void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 184, 579, &renderable, game, &self->status_tab_text);
    void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 184, 580, &renderable, game, &self->inventory_tab_text);
    void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 184, 581, &renderable, game, &self->ability_tab_text);
    void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 184, 582, &renderable, game, &self->job_change_tab_text);
    void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 184, 583, &renderable, game, &self->ai_tab_text);
    if (0 < 0 || 0 > game->world.guilds.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", 0, game->world.guilds.size);
            ct_stacktrace_push(ct_stacktrace, 184, 586);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        player_guild = &game->world.guilds.arr[0];
    for (i = 0; i < self->unit_slots.size; i += 1) {
        if (i < 0 || i > self->unit_slots.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->unit_slots.size);
                ct_stacktrace_push(ct_stacktrace, 184, 588);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit_slot = &self->unit_slots.arr[i];
        unit_slot->render_dst.dst = slot_dst;
        void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 184, 590, &renderable, game, unit_slot);
        if (i <= (player_guild->unit_handles.size - 1)) {
            if (i < 0 || i > player_guild->unit_handles.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", i, player_guild->unit_handles.size);
                    ct_stacktrace_push(ct_stacktrace, 184, 594);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                unit_handle = player_guild->unit_handles.arr[i];
            unit_dst = slot_dst;
            unit_dst.x += slot_padding;
            unit_dst.y += slot_padding;
            void_mfunc_UIRenderable_set_unit_UIRenderablePtr_GamePtr_int_SDL_RectPtr(ct_stacktrace, 184, 598, &renderable, game, unit_handle, &unit_dst);
}
        slot_dst.x += slot_inc.x;
        if (i == wrap_at_idx) {
            wrap_at_idx += cols;
            slot_dst.x = start_slot_dst.x;
            slot_dst.y += slot_inc.y;
    }
}
    if (self->active_tab == UnitsWindowTabName_Status) {
        void_mfunc_UnitsWindow_update_status_tab_UnitsWindowPtr_GamePtr(ct_stacktrace, 184, 608, self, game);
}
    else if (self->active_tab == UnitsWindowTabName_Inventory) {
        void_mfunc_UnitsWindow_update_inventory_tab_UnitsWindowPtr_GamePtr(ct_stacktrace, 184, 610, self, game);
}
    else if (self->active_tab == UnitsWindowTabName_Ability) {
        void_mfunc_UnitsWindow_update_ability_tab_UnitsWindowPtr_GamePtr(ct_stacktrace, 184, 612, self, game);
}
    else if (self->active_tab == UnitsWindowTabName_JobChange) {
        void_mfunc_UnitsWindow_update_job_change_tab_UnitsWindowPtr_GamePtr(ct_stacktrace, 184, 614, self, game);
}
    else if (self->active_tab == UnitsWindowTabName_AI) {
        void_mfunc_UnitsWindow_update_ai_tab_UnitsWindowPtr_GamePtr(ct_stacktrace, 184, 616, self, game);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_MerchantsWindow_update_MerchantsWindowPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, MerchantsWindow* self, Game* game) {
    SDL_Rect unit_dst = {0};
    UISprite* unit_slot = NULL;
    Guild* player_guild = NULL;
    SDL_Rect* background_src = NULL;
    SDL_Rect start_slot_dst = {0};
    SDL_Rect background_dst = {0};
    SDL_Rect slot_dst = {0};
    int cols = 0;
    int base_res_h = 0;
    int i = 0;
    int unit_handle = 0;
    int base_res_w = 0;
    SDL_Point slot_inc = {0};
    int slot_padding = 0;
    UIRenderable renderable = {0};
    int wrap_at_idx = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (!(self->visible)) {
                ct_stacktrace_pop(ct_stacktrace);
return;
}
    self->background.render_dst.dst.x = 0;
    self->background.render_dst.dst.y = 0;
    if (0 < 0 || 0 > self->background.shared_srcs->srcs.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", 0, self->background.shared_srcs->srcs.size);
            ct_stacktrace_push(ct_stacktrace, 185, 1042);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        background_src = &self->background.shared_srcs->srcs.arr[0];
    base_res_w = game->engine.base_resolution.x;
    base_res_h = game->engine.base_resolution.y;
    self->background.render_dst.dst.x = ((base_res_w / 2) - (background_src->w / 2));
    self->background.render_dst.dst.y = ((base_res_h / 2) - (background_src->h / 2));
    background_dst = self->background.render_dst.dst;
    self->window_text.render_dst.dst = background_dst;
    self->window_text.render_dst.dst.x += 4;
    self->window_text.render_dst.dst.y += 6;
    self->window_close_button.render_dst.dst = background_dst;
    self->window_close_button.render_dst.dst.x += (background_src->w - 15);
    self->window_close_button.render_dst.dst.y += 6;
    slot_dst = background_dst;
    slot_dst.x += 6;
    slot_dst.y += (24 + 6);
    start_slot_dst = slot_dst;
    slot_inc = SDL_Point_create_point_int_int(ct_stacktrace, 185, 1058, 25, 45);
    slot_padding = 2;
    cols = 6;
    wrap_at_idx = (cols - 1);
    void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 185, 1065, &renderable, game, &self->background);
    void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 185, 1066, &renderable, game, &self->window_text);
    void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 185, 1067, &renderable, game, &self->window_close_button);
    if (0 < 0 || 0 > game->world.guilds.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", 0, game->world.guilds.size);
            ct_stacktrace_push(ct_stacktrace, 185, 1070);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        player_guild = &game->world.guilds.arr[0];
    for (i = 0; i < self->unit_slots.size; i += 1) {
        if (i < 0 || i > self->unit_slots.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->unit_slots.size);
                ct_stacktrace_push(ct_stacktrace, 185, 1072);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit_slot = &self->unit_slots.arr[i];
        unit_slot->render_dst.dst = slot_dst;
        void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 185, 1074, &renderable, game, unit_slot);
        if (i <= (player_guild->merchant_handles.size - 1)) {
            if (i < 0 || i > player_guild->merchant_handles.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", i, player_guild->merchant_handles.size);
                    ct_stacktrace_push(ct_stacktrace, 185, 1078);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                unit_handle = player_guild->merchant_handles.arr[i];
            unit_dst = slot_dst;
            unit_dst.x += slot_padding;
            unit_dst.y += slot_padding;
            void_mfunc_UIRenderable_set_unit_UIRenderablePtr_GamePtr_int_SDL_RectPtr(ct_stacktrace, 185, 1082, &renderable, game, unit_handle, &unit_dst);
}
        slot_dst.x += slot_inc.x;
        if (i == wrap_at_idx) {
            wrap_at_idx += cols;
            slot_dst.x = start_slot_dst.x;
            slot_dst.y += slot_inc.y;
        }
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_RecruitNoviceModal_update_RecruitNoviceModalPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, RecruitNoviceModal* self, Game* game) {
    TextLG* ok_button_text = NULL;
    UISprite* ok_button = NULL;
    TextLG* unit_cost_text = NULL;
    Unit* unit = NULL;
    UnitName unit_name = (UnitName) 0;
    int i = 0;
    SDL_Rect unit_dst = {0};
    UIRenderable renderable = {0};
    TextLG* unit_header_text = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (!(self->visible)) {
                ct_stacktrace_pop(ct_stacktrace);
return;
}
    self->backdrop.render_dst.dst.x = 0;
    self->backdrop.render_dst.dst.y = 0;
    self->background.render_dst.dst.x = ((640 / 2) - (180 / 2));
    self->background.render_dst.dst.y = ((360 / 2) - (200 / 2));
    self->header_text.render_dst.dst = self->background.render_dst.dst;
    self->header_text.render_dst.dst.x += 5;
    self->header_text.render_dst.dst.y += 12;
    self->close_button.render_dst.dst = self->background.render_dst.dst;
    self->close_button.render_dst.dst.x += 162;
    self->close_button.render_dst.dst.y += 10;
    void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 186, 231, &renderable, game, &self->backdrop);
    void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 186, 232, &renderable, game, &self->background);
    void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 186, 233, &renderable, game, &self->close_button);
    void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 186, 234, &renderable, game, &self->header_text);
    for (i = 0; i < self->unit_slots_ok_buttons.size; i += 1) {
        unit_name = UnitName_Explorer;
        if (i == 1) {
            unit_name = UnitName_Merchant;
}
        unit = UnitPtr_mfunc_UnitDB_get_unit_UnitDBPtr_UnitName(ct_stacktrace, 186, 239, &game->unit_db, unit_name);
        unit_dst = self->background.render_dst.dst;
        unit_dst.x += (34 + (i * 90));
        unit_dst.y += 80;
        void_mfunc_UIRenderable_set_unit_sprite_UIRenderablePtr_GamePtr_UnitSpritePtr_SDL_RectPtr(ct_stacktrace, 186, 243, &renderable, game, &unit->sprite, &unit_dst);
        if (i < 0 || i > self->unit_header_texts.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->unit_header_texts.size);
                ct_stacktrace_push(ct_stacktrace, 186, 245);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit_header_text = &self->unit_header_texts.arr[i];
        unit_header_text->render_dst.dst = unit_dst;
        unit_header_text->render_dst.dst.x -= 10;
        unit_header_text->render_dst.dst.y -= 35;
        if (i < 0 || i > self->unit_cost_texts.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->unit_cost_texts.size);
                ct_stacktrace_push(ct_stacktrace, 186, 249);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            unit_cost_text = &self->unit_cost_texts.arr[i];
        unit_cost_text->render_dst.dst = unit_header_text->render_dst.dst;
        unit_cost_text->render_dst.dst.y += 12;
        if (i < 0 || i > self->unit_slots_ok_buttons.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->unit_slots_ok_buttons.size);
                ct_stacktrace_push(ct_stacktrace, 186, 252);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            ok_button = &self->unit_slots_ok_buttons.arr[i];
        ok_button->render_dst.dst = unit_dst;
        ok_button->render_dst.dst.x -= 20;
        ok_button->render_dst.dst.y += 45;
        if (i < 0 || i > self->unit_slots_ok_button_texts.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->unit_slots_ok_button_texts.size);
                ct_stacktrace_push(ct_stacktrace, 186, 256);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            ok_button_text = &self->unit_slots_ok_button_texts.arr[i];
        ok_button_text->render_dst.dst = ok_button->render_dst.dst;
        ok_button_text->render_dst.dst.x += 12;
        ok_button_text->render_dst.dst.y += 6;
        void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 186, 261, &renderable, game, unit_header_text);
        void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 186, 262, &renderable, game, unit_cost_text);
        void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(ct_stacktrace, 186, 263, &renderable, game, ok_button);
        void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(ct_stacktrace, 186, 264, &renderable, game, ok_button_text);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_UnitsWindow_set_visible_UnitsWindowPtr_bool(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitsWindow* self, bool visible) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->visible = visible;
    if (!(self->visible)) {
        void_mfunc_InputEvents_clear_InputEventsPtr(ct_stacktrace, 187, 513, &self->background.input_events);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_MerchantsWindow_set_visible_MerchantsWindowPtr_bool(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, MerchantsWindow* self, bool visible) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->visible = visible;
    if (!(self->visible)) {
        void_mfunc_InputEvents_clear_InputEventsPtr(ct_stacktrace, 189, 1035, &self->background.input_events);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_GuildWindow_set_visible_GuildWindowPtr_bool(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, GuildWindow* self, bool visible) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->visible = visible;
    if (!(self->visible)) {
        void_mfunc_InputEvents_clear_InputEventsPtr(ct_stacktrace, 190, 1152, &self->background.input_events);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

