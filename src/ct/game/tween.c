#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "ct_stacktrace.h"
#include "tween.h"
#include "constants.h"
#include "utils.h"
#include "game.h"

void void_mfunc_TweenXY_init_TweenXYPtr_GamePtr_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, TweenXY* self, Game* game, int handle) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->handle = handle;
    self->in_use_in_pool = false;
    ct_stacktrace_pop(ct_stacktrace);
}

TweenCompletion TweenCompletion_mfunc_TweenXY_update_TweenXYPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, TweenXY* self, Game* game) {
    int diff_x = 0;
    int total_delay = 0;
    double y = 0.0;
    double frac = 0.0;
    double delta_dist = 0.0;
    double delta_y = 0.0;
    int diff_y = 0;
    Uint32 current_time = 0;
    TweenCompletion tween_completion = {0};
    double x = 0.0;
    double delta_x = 0.0;
    int elapsed = 0;
    int y_as_int = 0;
    int x_as_int = 0;
    double duration_as_double = 0.0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    tween_completion.initial_has_started = false;
    tween_completion.completed = false;
    current_time = game->engine.current_time;
    if (current_time < (self->spawn_time + self->delay)) {
                ct_stacktrace_pop(ct_stacktrace);
return tween_completion;
}
    if (!(self->has_started)) {
        self->has_started = true;
        tween_completion.initial_has_started = true;
}
    if (self->is_constant_speed) {
        delta_x = (self->target_val_ptr->x - self->double_point.x);
        delta_y = (self->target_val_ptr->y - self->double_point.y);
        delta_dist = sqrt(((delta_x * delta_x) + (delta_y * delta_y)));
        frac = (self->speed / delta_dist);
        x = (frac * delta_x);
        y = (frac * delta_y);
        self->double_point.x += x;
        self->double_point.y += y;
        self->val->x = (int)(self->double_point.x);
        self->val->y = (int)(self->double_point.y);
        if (delta_dist < 4.0) {
            tween_completion.completed = true;
                        ct_stacktrace_pop(ct_stacktrace);
return tween_completion;
    }
}
    else {
        duration_as_double = (double)(self->duration);
        total_delay = (self->spawn_time + self->delay);
        elapsed = (current_time - total_delay);
        frac = (elapsed / duration_as_double);
        if (frac > 1.0) {
            frac = 1.0;
}
        diff_x = (self->target_val.x - self->start_val.x);
        diff_y = (self->target_val.y - self->start_val.y);
        x = (diff_x * frac);
        y = (diff_y * frac);
        x_as_int = (int)(x);
        y_as_int = (int)(y);
        self->val->x = (self->start_val.x + x_as_int);
        self->val->y = (self->start_val.y + y_as_int);
        if (current_time >= ((self->spawn_time + self->delay) + self->duration)) {
            tween_completion.completed = true;
                        ct_stacktrace_pop(ct_stacktrace);
return tween_completion;
    }
}
        ct_stacktrace_pop(ct_stacktrace);
return tween_completion;
}

void void_mfunc_TweenXY_set_TweenXYPtr_GamePtr_SDL_RectPtr_SDL_RectPtr_SDL_RectPtr_bool_double_Uint32_Uint32_TweenCallbackPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, TweenXY* self, Game* game, SDL_Rect* start_val, SDL_Rect* val, SDL_Rect* target_val, bool is_constant_speed, double speed, Uint32 duration, Uint32 delay, TweenCallback* callback) {
    double x_as_double = 0.0;
    double y_as_double = 0.0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->start_val = *start_val;
    self->val = val;
    self->target_val = *target_val;
    self->target_val_ptr = target_val;
    self->speed = speed;
    self->is_constant_speed = is_constant_speed;
    self->duration = duration;
    self->delay = delay;
    self->spawn_time = game->engine.current_time;
    x_as_double = (double)(start_val->x);
    y_as_double = (double)(start_val->y);
    void_mfunc_DoublePoint_init_DoublePointPtr_double_double(ct_stacktrace, 89, 60, &self->double_point, x_as_double, y_as_double);
    self->callback = *callback;
    self->remove_in_update = false;
    self->has_started = false;
    ct_stacktrace_pop(ct_stacktrace);
}

