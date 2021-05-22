#ifndef GAME_UTILS
#define GAME_UTILS

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "stbttf_sdl.h"
#include "constants.h"

struct CT_StackTrace;

typedef struct DoublePoint {
  double x;
  double y;
} DoublePoint;

typedef struct Range {
  Uint64 min;
  Uint64 value_before_buffs;
  Uint64 value;
  Uint64 max;
  Uint64 upper_bound;
} Range;

typedef struct RenderDst {
  SDL_Rect dst;
  SDL_Rect scaled_dst;
  bool is_camera_rendered;
} RenderDst;

typedef struct UIEvent {
  UIEventName event_name;
  int handle;
  int guild_handle;
  UnitName unit_name;
  AbilityName ability_name;
  StatName stat_name;
} UIEvent;

typedef struct MoveOptions {
  int warp_point_handle;
  bool check_unit_collissions;
  int merchant_unit_handle;
} MoveOptions;

Uint32 get_max_uint32();
Uint64 get_max_uint64();
SDL_Point SDL_Point_create_point_int_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, int x, int y);
SDL_Rect SDL_Rect_create_rect_int_int_int_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, int x, int y, int w, int h);
SDL_Color SDL_Color_create_color_int_int_int_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, int r, int g, int b, int a);
bool bool_rects_are_equal_SDL_RectPtr_SDL_RectPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, SDL_Rect* r1, SDL_Rect* r2);
SDL_Point SDL_Point_get_move_grid_size_dims_int_int_SDL_PointPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, int w, int h, SDL_Point* move_grid_tile_size);
void void_mfunc_Range_set_RangePtr_Uint64_Uint64_Uint64(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Range* self, Uint64 min, Uint64 value, Uint64 upper_bound);
void void_mfunc_Range_set_with_max_to_upper_bound_RangePtr_Uint64_Uint64_Uint64(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Range* self, Uint64 min, Uint64 value, Uint64 upper_bound);
SDL_Color SDL_Color_get_faction_color_Faction(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Faction faction);
SDL_Point SDL_Point_tile_point_to_world_point_SDL_PointPtr_SDL_PointPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, SDL_Point* idx, SDL_Point* tile_size);
bool bool_rect_contains_rect_SDL_RectPtr_SDL_RectPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, SDL_Rect* r1, SDL_Rect* r2);
SDL_Point SDL_Point_world_point_to_tile_point_SDL_PointPtr_SDL_PointPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, SDL_Point* world_point, SDL_Point* tile_size);
SDL_Point SDL_Point_world_point_to_index_with_camera_SDL_PointPtr_SDL_PointPtr_SDL_PointPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, SDL_Point* world_point, SDL_Point* camera_point, SDL_Point* tile_size);
int int_get_stat_points_for_level_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, int level);
int int_get_stat_cost_Uint64(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Uint64 stat_value);
void void_mfunc_Range_inc_RangePtr_Uint64(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Range* self, Uint64 value);
bool bool_points_are_equal_SDL_PointPtr_SDL_PointPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, SDL_Point* p1, SDL_Point* p2);
void void_mfunc_DoublePoint_init_DoublePointPtr_double_double(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, DoublePoint* self, double x, double y);
int int_manhattan_distance_SDL_PointPtr_SDL_PointPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, SDL_Point* p1, SDL_Point* p2);
int int_get_1d_from_2d_idx_SDL_PointPtr_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, SDL_Point* p, int rows);
bool bool_mfunc_Range_value_is_at_min_RangePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Range* self);
void void_mfunc_Range_dec_RangePtr_Uint64(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Range* self, Uint64 value);
bool bool_mfunc_Range_value_is_at_max_RangePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Range* self);
void void_mfunc_Range_set_to_min_RangePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Range* self);
void void_mfunc_Range_set_to_max_RangePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Range* self);
double double_mfunc_Range_value_pct_of_max_RangePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Range* self);
void void_set_scaled_rect_with_camera_SDL_RectPtr_SDL_PointPtr_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, SDL_Rect* rect, SDL_Point* camera_dst, int scale);
void void_set_scaled_rect_SDL_RectPtr_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, SDL_Rect* rect, int scale);
void void_mfunc_RenderDst_update_RenderDstPtr_SDL_PointPtr_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, RenderDst* self, SDL_Point* camera_dst, int engine_scale);
bool bool_rect_contains_point_SDL_RectPtr_SDL_PointPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, SDL_Rect* r, SDL_Point* p);
int int_get_unit_name_job_tier_UnitName(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitName unit_name);
bool bool_unit_can_job_change_UnitName_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitName unit_name, int job_level);

#endif // GAME_UTILS
