#ifndef GAME_UNIT
#define GAME_UNIT

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "stbttf_sdl.h"
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

struct CT_StackTrace;
struct Game;
struct Map;

typedef struct Unit {
  UnitType unit_type;
  UnitName unit_name;
  Faction faction;
  Stats stats;
  UnitSprite sprite;
  int map_handle;
  int battle_map_handle;
  SDL_Rect tile_point_hit_box;
  Array_SharedAbility_10 job_abilities;
  Array_SharedAbility_30 abilities;
  SharedAbility default_attack_ability;
  Array_SharedItem_5 item_drops;
  Array_AIAbility_30 ai_abilities;
  Inventory inventory;
  Array_char_100 display_name;
  TextLG display_name_text;
  Array_char_100 guild_display_name;
  TextLG guild_display_name_text;
  UISprite guild_icon;
  UISprite merchant_shop_background;
  TextLG merchant_shop_text;
  int guild_handle;
  int available_stat_points;
  int available_skill_points;
  int aggro_towards_unit_handle;
  Uint32 last_move_calc_time;
  Uint32 last_failed_path_time;
  Uint32 last_try_merchant_buy_time;
  Uint32 last_attack_time;
  Uint32 last_sit_heal_time;
  Uint32 last_non_guild_merchant_restock_time;
  Uint32 neutral_can_try_buy_again_time;
  bool path_could_not_be_found;
  Uint32 next_random_move_time;
  Uint32 death_time;
  Uint32 respawn_time;
  bool aggro_nearest_unit;
  int attacked_by_guild_handle;
  int unit_handle_buying_from_merchant;
  UnitAIState ai_state;
  bool is_sitting;
  bool inside_building;
  int handle;
  bool in_use_in_pool;
} Unit;

typedef struct Array_Unit_200 {
  Unit arr[200];
  int size;
  int capacity;
} Array_Unit_200;

typedef struct Array_Unit_3000 {
  Unit arr[3000];
  int size;
  int capacity;
} Array_Unit_3000;

void void_mfunc_Unit_init_UnitPtr_GamePtr_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game, int handle);
void void_mfunc_Unit_set_to_UnitPtr_GamePtr_UnitName_Faction(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game, UnitName unit_name, Faction faction);
void void_mfunc_Unit_join_map_UnitPtr_GamePtr_MapPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game, struct Map* map);
void void_mfunc_Unit_set_random_spawn_point_UnitPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game);
bool bool_mfunc_Unit_is_merchant_UnitPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self);
void void_mfunc_Unit_join_guild_UnitPtr_GamePtr_GuildPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game, struct Guild* guild);
void void_mfunc_Unit_sell_items_UnitPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game);
void void_mfunc_Unit_clear_move_tweens_UnitPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game);
void void_mfunc_Unit_move_to_UnitPtr_GamePtr_SDL_PointPtr_TweenType_MoveOptionsPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game, struct SDL_Point* target_point, TweenType move_tween_type, struct MoveOptions* move_options);
bool bool_mfunc_Unit_try_find_and_move_to_merchant_shop_UnitPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game);
void void_mfunc_Unit_move_to_overworld_warp_point_UnitPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game);
void void_mfunc_Unit_merchant_get_sellable_items_from_guild_UnitPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game);
void void_mfunc_Unit_move_to_setup_merchant_shop_UnitPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game);
void void_mfunc_Unit_give_items_to_guild_UnitPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game);
void void_mfunc_Unit_move_to_shop_UnitPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game);
void void_mfunc_Unit_move_to_random_town_point_UnitPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game);
void void_mfunc_Unit_set_spawn_point_UnitPtr_GamePtr_SDL_PointPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game, struct SDL_Point* spawn_move_tile_point);
void void_mfunc_Unit_move_to_town_warp_point_UnitPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game);
void void_mfunc_Unit_move_to_guild_building_UnitPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game);
void void_mfunc_Unit_move_to_battle_warp_point_UnitPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game);
void void_mfunc_Unit_merchant_sell_to_unit_UnitPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game);
void void_mfunc_Unit_on_hit_UnitPtr_GamePtr_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game, int hit_by_unit_handle);
void void_mfunc_Unit_do_item_drops_UnitPtr_GamePtr_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game, int target_unit_handle);
void void_mfunc_Unit_on_dead_UnitPtr_GamePtr_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game, int hit_by_unit_handle);
void void_mfunc_Unit_change_to_sell_item_ai_state_UnitPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game);
void void_mfunc_Unit_update_towns_person_ai_UnitPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game);
void void_mfunc_Unit_update_merchant_ai_UnitPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game);
bool bool_mfunc_Unit_is_ally_or_guild_faction_UnitPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self);
void void_mfunc_Unit_move_towards_tile_point_UnitPtr_GamePtr_SDL_PointPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game, struct SDL_Point* target_point);
int int_mfunc_Unit_closest_opposite_unit_handle_UnitPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game);
struct SharedAbility* SharedAbilityPtr_mfunc_Unit_get_ai_ability_UnitPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game);
void void_mfunc_Unit_perform_ability_UnitPtr_GamePtr_SharedAbilityPtr_Array_int_10Ptr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game, struct SharedAbility* ability_to_perform, struct Array_int_10* target_unit_handles);
void void_mfunc_Unit_update_ai_UnitPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game);
void void_mfunc_Unit_update_UnitPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game);
int int_mfunc_Unit_get_ability_skill_points_UnitPtr_AbilityName(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, AbilityName ability_name);
struct SharedAbility* SharedAbilityPtr_mfunc_Unit_get_ability_UnitPtr_AbilityName(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, AbilityName ability_name);
void void_mfunc_Unit_draw_UnitPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game);
void void_mfunc_Unit_draw_idle_at_UnitPtr_GamePtr_SDL_RectPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Unit* self, struct Game* game, struct SDL_Rect* unscaled_dst);

#endif // GAME_UNIT
