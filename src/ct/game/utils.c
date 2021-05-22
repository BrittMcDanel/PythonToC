#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "ct_stacktrace.h"
#include "utils.h"
#include "constants.h"

Uint32 get_max_uint32() {  /* return SDL's max uint 32 because it looks like they check for portability */  return SDL_MAX_UINT32;}

Uint64 get_max_uint64() {  /* return SDL's max uint 64 because it looks like they check for portability */  return SDL_MAX_UINT64;}

SDL_Point SDL_Point_create_point_int_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, int x, int y) {
    SDL_Point p = {0};

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    p.x = x;
    p.y = y;
        ct_stacktrace_pop(ct_stacktrace);
return p;
}

SDL_Rect SDL_Rect_create_rect_int_int_int_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, int x, int y, int w, int h) {
    SDL_Rect r = {0};

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;
        ct_stacktrace_pop(ct_stacktrace);
return r;
}

SDL_Color SDL_Color_create_color_int_int_int_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, int r, int g, int b, int a) {
    SDL_Color c = {0};

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    c.r = r;
    c.g = g;
    c.b = b;
    c.a = a;
        ct_stacktrace_pop(ct_stacktrace);
return c;
}

bool bool_rects_are_equal_SDL_RectPtr_SDL_RectPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, SDL_Rect* r1, SDL_Rect* r2) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
        ct_stacktrace_pop(ct_stacktrace);
return (((r1->x == r2->x && r1->y == r2->y) && r1->w == r2->w) && r1->h == r2->h);
}

SDL_Point SDL_Point_get_move_grid_size_dims_int_int_SDL_PointPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, int w, int h, SDL_Point* move_grid_tile_size) {
    int move_grid_h = 0;
    int move_grid_w = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    move_grid_w = (w / move_grid_tile_size->x);
    move_grid_h = (h / move_grid_tile_size->y);
        ct_stacktrace_pop(ct_stacktrace);
return SDL_Point_create_point_int_int(ct_stacktrace, 23, 236, move_grid_w, move_grid_h);
}

void void_mfunc_Range_set_RangePtr_Uint64_Uint64_Uint64(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Range* self, Uint64 min, Uint64 value, Uint64 upper_bound) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->min = min;
    self->value_before_buffs = value;
    self->value = value;
    self->max = value;
    self->upper_bound = upper_bound;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Range_set_with_max_to_upper_bound_RangePtr_Uint64_Uint64_Uint64(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Range* self, Uint64 min, Uint64 value, Uint64 upper_bound) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->min = min;
    self->value_before_buffs = value;
    self->value = value;
    self->max = upper_bound;
    self->upper_bound = upper_bound;
    ct_stacktrace_pop(ct_stacktrace);
}

SDL_Color SDL_Color_get_faction_color_Faction(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Faction faction) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (faction == Faction_Ally) {
                ct_stacktrace_pop(ct_stacktrace);
return SDL_Color_create_color_int_int_int_int(ct_stacktrace, 29, 241, 255, 255, 255, 255);
}
    else if (faction == Faction_Guild) {
                ct_stacktrace_pop(ct_stacktrace);
return SDL_Color_create_color_int_int_int_int(ct_stacktrace, 29, 243, 89, 129, 255, 255);
}
    else if (faction == Faction_Enemy) {
                ct_stacktrace_pop(ct_stacktrace);
return SDL_Color_create_color_int_int_int_int(ct_stacktrace, 29, 245, 255, 44, 83, 255);
}
    else if (faction == Faction_Neutral) {
                ct_stacktrace_pop(ct_stacktrace);
return SDL_Color_create_color_int_int_int_int(ct_stacktrace, 29, 247, 255, 205, 117, 255);
}
        ct_stacktrace_pop(ct_stacktrace);
return SDL_Color_create_color_int_int_int_int(ct_stacktrace, 29, 249, 255, 255, 255, 255);
}

SDL_Point SDL_Point_tile_point_to_world_point_SDL_PointPtr_SDL_PointPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, SDL_Point* idx, SDL_Point* tile_size) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
        ct_stacktrace_pop(ct_stacktrace);
return SDL_Point_create_point_int_int(ct_stacktrace, 51, 215, (idx->x * tile_size->x), (idx->y * tile_size->y));
}

bool bool_rect_contains_rect_SDL_RectPtr_SDL_RectPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, SDL_Rect* r1, SDL_Rect* r2) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
        ct_stacktrace_pop(ct_stacktrace);
return (((r1->x < (r2->x + r2->w) && (r1->x + r1->w) > r2->x) && r1->y < (r2->y + r2->h)) && (r1->y + r1->h) > r2->y);
}

SDL_Point SDL_Point_world_point_to_tile_point_SDL_PointPtr_SDL_PointPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, SDL_Point* world_point, SDL_Point* tile_size) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
        ct_stacktrace_pop(ct_stacktrace);
return SDL_Point_create_point_int_int(ct_stacktrace, 75, 219, (world_point->x / tile_size->x), (world_point->y / tile_size->y));
}

SDL_Point SDL_Point_world_point_to_index_with_camera_SDL_PointPtr_SDL_PointPtr_SDL_PointPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, SDL_Point* world_point, SDL_Point* camera_point, SDL_Point* tile_size) {
    SDL_Point p = {0};

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    p = *world_point;
    p.x += camera_point->x;
    p.y += camera_point->y;
        ct_stacktrace_pop(ct_stacktrace);
return SDL_Point_world_point_to_tile_point_SDL_PointPtr_SDL_PointPtr(ct_stacktrace, 76, 226, &p, tile_size);
}

int int_get_stat_points_for_level_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, int level) {
    int value_as_int = 0;
    double value = 0.0;
    double level_div = 0.0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    level_div = (level / 5.0);
    value = (floor(level_div) + 3);
    value_as_int = (int)(value);
        ct_stacktrace_pop(ct_stacktrace);
return value_as_int;
}

int int_get_stat_cost_Uint64(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Uint64 stat_value) {
    int value_as_int = 0;
    double value = 0.0;
    double stat_div = 0.0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    stat_value -= 1;
    stat_div = (stat_value / 10.0);
    value = (floor(stat_div) + 2);
    value_as_int = (int)(value);
        ct_stacktrace_pop(ct_stacktrace);
return value_as_int;
}

void void_mfunc_Range_inc_RangePtr_Uint64(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Range* self, Uint64 value) {
    int diff = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    diff = (self->max - self->value);
    if (value > diff) {
        self->value = self->max;
}
    else {
        self->value += value;
    }
    ct_stacktrace_pop(ct_stacktrace);
}

bool bool_points_are_equal_SDL_PointPtr_SDL_PointPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, SDL_Point* p1, SDL_Point* p2) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
        ct_stacktrace_pop(ct_stacktrace);
return (p1->x == p2->x && p1->y == p2->y);
}

void void_mfunc_DoublePoint_init_DoublePointPtr_double_double(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, DoublePoint* self, double x, double y) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->x = x;
    self->y = y;
    ct_stacktrace_pop(ct_stacktrace);
}

int int_manhattan_distance_SDL_PointPtr_SDL_PointPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, SDL_Point* p1, SDL_Point* p2) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
        ct_stacktrace_pop(ct_stacktrace);
return (abs((p1->x - p2->x)) + abs((p1->y - p2->y)));
}

int int_get_1d_from_2d_idx_SDL_PointPtr_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, SDL_Point* p, int rows) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
        ct_stacktrace_pop(ct_stacktrace);
return ((p->x * rows) + p->y);
}

bool bool_mfunc_Range_value_is_at_min_RangePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Range* self) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
        ct_stacktrace_pop(ct_stacktrace);
return self->value <= self->min;
}

void void_mfunc_Range_dec_RangePtr_Uint64(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Range* self, Uint64 value) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (self->value <= value) {
        self->value = self->min;
}
    else {
        self->value -= value;
    }
    ct_stacktrace_pop(ct_stacktrace);
}

bool bool_mfunc_Range_value_is_at_max_RangePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Range* self) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
        ct_stacktrace_pop(ct_stacktrace);
return self->value >= self->max;
}

void void_mfunc_Range_set_to_min_RangePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Range* self) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->value = self->min;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Range_set_to_max_RangePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Range* self) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->value = self->max;
    ct_stacktrace_pop(ct_stacktrace);
}

double double_mfunc_Range_value_pct_of_max_RangePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Range* self) {
    double max_as_double = 0.0;
    double value_as_double = 0.0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    value_as_double = (double)(self->value);
    max_as_double = (double)(self->max);
        ct_stacktrace_pop(ct_stacktrace);
return (value_as_double / max_as_double);
}

void void_set_scaled_rect_with_camera_SDL_RectPtr_SDL_PointPtr_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, SDL_Rect* rect, SDL_Point* camera_dst, int scale) {
    SDL_Point p = {0};

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    p = SDL_Point_create_point_int_int(ct_stacktrace, 145, 186, rect->x, rect->y);
    p.x -= camera_dst->x;
    p.y -= camera_dst->y;
    p.x *= scale;
    p.y *= scale;
    rect->x = p.x;
    rect->y = p.y;
    rect->w *= scale;
    rect->h *= scale;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_set_scaled_rect_SDL_RectPtr_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, SDL_Rect* rect, int scale) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    rect->x *= scale;
    rect->y *= scale;
    rect->w *= scale;
    rect->h *= scale;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_RenderDst_update_RenderDstPtr_SDL_PointPtr_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, RenderDst* self, SDL_Point* camera_dst, int engine_scale) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->scaled_dst = self->dst;
    if (self->is_camera_rendered) {
        void_set_scaled_rect_with_camera_SDL_RectPtr_SDL_PointPtr_int(ct_stacktrace, 147, 101, &self->scaled_dst, camera_dst, engine_scale);
}
    else {
        void_set_scaled_rect_SDL_RectPtr_int(ct_stacktrace, 147, 103, &self->scaled_dst, engine_scale);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

bool bool_rect_contains_point_SDL_RectPtr_SDL_PointPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, SDL_Rect* r, SDL_Point* p) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
        ct_stacktrace_pop(ct_stacktrace);
return (((p->x >= r->x && p->x <= (r->x + r->w)) && p->y >= r->y) && p->y <= (r->y + r->h));
}

int int_get_unit_name_job_tier_UnitName(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitName unit_name) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if (unit_name == UnitName_Explorer) {
                ct_stacktrace_pop(ct_stacktrace);
return 0;
}
    else if (unit_name == UnitName_Mage) {
                ct_stacktrace_pop(ct_stacktrace);
return 1;
}
    else {
                ct_stacktrace_pop(ct_stacktrace);
return 2;
    }
}

bool bool_unit_can_job_change_UnitName_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitName unit_name, int job_level) {
    int job_tier = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    job_tier = int_get_unit_name_job_tier_UnitName(ct_stacktrace, 179, 262, unit_name);
    if ((job_tier == 0 && job_level == 10)) {
                ct_stacktrace_pop(ct_stacktrace);
return true;
}
    else if ((job_tier == 1 && job_level == 40)) {
                ct_stacktrace_pop(ct_stacktrace);
return true;
}
        ct_stacktrace_pop(ct_stacktrace);
return false;
}

