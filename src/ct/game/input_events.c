#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "ct_stacktrace.h"
#include "input_events.h"
#include "engine.h"
#include "image.h"
#include "utils.h"
#include "image.h"
#include "ct_array.h"
#include "game.h"

void void_mfunc_InputEvents_update_InputEventsPtr_GamePtr_bool(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, InputEvents* self, Game* game, bool _is_mouse_over) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->is_click = false;
    if (_is_mouse_over) {
        if (!(self->is_mouse_over)) {
            self->is_mouse_enter = true;
}
        self->is_mouse_over = true;
}
    else {
        if (self->is_mouse_over) {
            self->is_mouse_exit = false;
}
        self->is_mouse_over = false;
}
    if (game->engine.is_mouse_down) {
        if (self->is_mouse_over) {
            self->was_mouse_down_when_mouse_over = true;
            self->is_mouse_down = true;
}
        else {
            self->was_mouse_down_when_mouse_over = false;
    }
}
    if (game->engine.is_mouse_up) {
        if (self->is_mouse_over) {
            self->is_mouse_up = true;
            if (self->was_mouse_down_when_mouse_over) {
                self->is_click = true;
    }
}
        self->was_mouse_down_when_mouse_over = false;
}
    if (game->engine.is_mouse_held_down) {
        if (self->is_mouse_over) {
            self->is_mouse_held_down = true;
    }
}
    if (game->engine.is_right_mouse_down) {
        if (self->is_mouse_over) {
            self->was_right_mouse_down_when_mouse_over = true;
            self->is_right_mouse_down = true;
}
        else {
            self->was_right_mouse_down_when_mouse_over = false;
    }
}
    if (game->engine.is_right_mouse_up) {
        if (self->is_mouse_over) {
            self->is_right_mouse_up = true;
            if (self->was_right_mouse_down_when_mouse_over) {
                self->is_right_click = true;
    }
}
        self->was_right_mouse_down_when_mouse_over = false;
}
    if (game->engine.is_right_mouse_held_down) {
        if (self->is_mouse_over) {
            self->is_right_mouse_held_down = true;
        }
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_InputEvents_clear_InputEventsPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, InputEvents* self) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->is_mouse_enter = false;
    self->is_mouse_exit = false;
    self->is_mouse_over = false;
    self->is_mouse_down = false;
    self->is_mouse_held_down = false;
    self->is_mouse_up = false;
    self->is_right_mouse_down = false;
    self->is_right_mouse_held_down = false;
    self->is_right_mouse_up = false;
    self->is_click = false;
    self->is_right_click = false;
    self->was_mouse_down_when_mouse_over = false;
    self->was_right_mouse_down_when_mouse_over = false;
    ct_stacktrace_pop(ct_stacktrace);
}

