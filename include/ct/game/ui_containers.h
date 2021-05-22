#ifndef GAME_UI_CONTAINERS
#define GAME_UI_CONTAINERS

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "stbttf_sdl.h"
#include "engine.h"
#include "utils.h"
#include "image.h"
#include "ct_array.h"
#include "ui_sprite.h"
#include "text.h"
#include "sprite.h"
#include "constants.h"
#include "unit_sprite.h"

struct CT_StackTrace;
struct Game;

typedef struct UIUnitRender {
  int handle;
  SDL_Rect dst;
} UIUnitRender;

typedef struct UnitSpriteRender {
  UnitSprite* sprite;
  SDL_Rect dst;
} UnitSpriteRender;

typedef struct SpriteRender {
  Sprite* sprite;
  SDL_Rect dst;
} SpriteRender;

typedef struct UIRenderable {
  UISprite* sprite;
  TextLG* text_lg;
  SpriteRender regular_sprite;
  UnitSpriteRender unit_sprite;
  UIUnitRender unit;
} UIRenderable;

typedef struct Array_UIRenderable_300 {
  UIRenderable arr[300];
  int size;
  int capacity;
} Array_UIRenderable_300;

typedef struct TopNav {
  UISprite background;
  TextLG league_text;
  TextLG money_text;
  UISprite guild_button;
  UISprite units_button;
  UISprite merchants_button;
  bool visible;
} TopNav;

typedef struct RecruitNoviceModal {
  UISprite backdrop;
  UISprite background;
  UISprite close_button;
  TextLG header_text;
  Array_UISprite_2 unit_slots_ok_buttons;
  Array_TextLG_2 unit_slots_ok_button_texts;
  Array_TextLG_2 unit_header_texts;
  Array_TextLG_2 unit_cost_texts;
  bool visible;
} RecruitNoviceModal;

typedef struct UnitsWindow {
  UISprite background;
  TextLG window_text;
  UISprite window_close_button;
  Array_UISprite_30 unit_slots;
  UISprite status_tab;
  UISprite inventory_tab;
  UISprite ability_tab;
  UISprite job_change_tab;
  UISprite ai_tab;
  TextLG status_tab_text;
  TextLG inventory_tab_text;
  TextLG ability_tab_text;
  TextLG job_change_tab_text;
  TextLG ai_tab_text;
  TextLG job_text;
  TextLG level_text;
  TextLG job_level_text;
  TextLG experience_text;
  TextLG job_experience_text;
  TextLG strength_text;
  TextLG intelligence_text;
  TextLG dexterity_text;
  TextLG vitality_text;
  TextLG agility_text;
  TextLG luck_text;
  TextLG available_stat_points_text;
  Array_UISprite_6 increase_stat_buttons;
  Array_UISprite_6 increase_stat_icons;
  Array_TextLG_6 increase_stat_cost_texts;
  Array_UISprite_50 inventory_slots;
  Array_TextLG_50 inventory_quantity_texts;
  TextLG available_skill_points_text;
  Array_UISprite_10 ability_slots;
  Array_TextLG_10 ability_skill_point_texts;
  Array_UISprite_5 job_change_row_2_slots;
  Array_UISprite_10 job_change_row_3_slots;
  TextLG next_job_change_level_text;
  Array_UISprite_12 ai_ability_slots;
  Array_TextLG_12 ai_ability_slot_order_texts;
  UISprite ai_ability_dropdown_background;
  Array_UISprite_9 ai_ability_dropdown_options;
  UISprite ai_ability_remove_icon;
  UnitsWindowTabName active_tab;
  int active_slot_idx;
  bool ai_ability_dropdown_visible;
  int ai_ability_active_idx;
  bool visible;
} UnitsWindow;

typedef struct MerchantsWindow {
  UISprite background;
  TextLG window_text;
  UISprite window_close_button;
  Array_UISprite_30 unit_slots;
  int active_slot_idx;
  bool visible;
} MerchantsWindow;

typedef struct GuildWindow {
  UISprite background;
  TextLG window_text;
  UISprite window_close_button;
  UISprite inventory_tab;
  TextLG inventory_tab_text;
  Array_UISprite_50 inventory_slots;
  Array_TextLG_50 inventory_quantity_texts;
  int active_slot_idx;
  bool visible;
} GuildWindow;

void void_mfunc_TopNav_init_TopNavPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, TopNav* self, struct Game* game);
void void_mfunc_RecruitNoviceModal_init_RecruitNoviceModalPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, RecruitNoviceModal* self, struct Game* game);
void void_mfunc_GuildWindow_init_GuildWindowPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, GuildWindow* self, struct Game* game);
void void_mfunc_UnitsWindow_init_UnitsWindowPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitsWindow* self, struct Game* game);
void void_mfunc_MerchantsWindow_init_MerchantsWindowPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, MerchantsWindow* self, struct Game* game);
void void_mfunc_RecruitNoviceModal_set_visible_RecruitNoviceModalPtr_bool(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, RecruitNoviceModal* self, bool visible);
void void_mfunc_UIRenderable_clear_UIRenderablePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UIRenderable* self);
void void_mfunc_UIRenderable_set_sprite_UIRenderablePtr_GamePtr_UISpritePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UIRenderable* self, struct Game* game, struct UISprite* sprite);
void void_mfunc_UIRenderable_set_text_lg_UIRenderablePtr_GamePtr_TextLGPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UIRenderable* self, struct Game* game, struct TextLG* text_lg);
void void_mfunc_TopNav_update_TopNavPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, TopNav* self, struct Game* game);
void void_mfunc_UIRenderable_set_regular_sprite_UIRenderablePtr_GamePtr_SpritePtr_SDL_RectPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UIRenderable* self, struct Game* game, struct Sprite* sprite, struct SDL_Rect* dst);
void void_mfunc_GuildWindow_update_inventory_tab_GuildWindowPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, GuildWindow* self, struct Game* game);
void void_mfunc_GuildWindow_update_GuildWindowPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, GuildWindow* self, struct Game* game);
void void_mfunc_UIRenderable_set_unit_UIRenderablePtr_GamePtr_int_SDL_RectPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UIRenderable* self, struct Game* game, int unit_handle, struct SDL_Rect* dst);
void void_mfunc_UnitsWindow_update_status_tab_UnitsWindowPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitsWindow* self, struct Game* game);
void void_mfunc_UnitsWindow_update_inventory_tab_UnitsWindowPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitsWindow* self, struct Game* game);
void void_mfunc_UnitsWindow_update_ability_tab_UnitsWindowPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitsWindow* self, struct Game* game);
void void_mfunc_UIRenderable_set_unit_sprite_UIRenderablePtr_GamePtr_UnitSpritePtr_SDL_RectPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UIRenderable* self, struct Game* game, struct UnitSprite* sprite, struct SDL_Rect* dst);
void void_mfunc_UnitsWindow_update_job_change_tab_UnitsWindowPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitsWindow* self, struct Game* game);
void void_mfunc_UnitsWindow_update_ai_tab_UnitsWindowPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitsWindow* self, struct Game* game);
void void_mfunc_UnitsWindow_update_UnitsWindowPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitsWindow* self, struct Game* game);
void void_mfunc_MerchantsWindow_update_MerchantsWindowPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, MerchantsWindow* self, struct Game* game);
void void_mfunc_RecruitNoviceModal_update_RecruitNoviceModalPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, RecruitNoviceModal* self, struct Game* game);
void void_mfunc_UnitsWindow_set_visible_UnitsWindowPtr_bool(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitsWindow* self, bool visible);
void void_mfunc_MerchantsWindow_set_visible_MerchantsWindowPtr_bool(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, MerchantsWindow* self, bool visible);
void void_mfunc_GuildWindow_set_visible_GuildWindowPtr_bool(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, GuildWindow* self, bool visible);

#endif // GAME_UI_CONTAINERS
