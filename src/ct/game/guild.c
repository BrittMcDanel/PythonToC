#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "ct_stacktrace.h"
#include "guild.h"
#include "utils.h"
#include "ct_array.h"
#include "inventory.h"
#include "game.h"

void void_mfunc_Guild_init_GuildPtr_GamePtr_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Guild* self, Game* game, int handle) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->handle = handle;
    self->in_use_in_pool = false;
    self->current_money = 500;
    void_mfunc_Inventory_init_InventoryPtr(ct_stacktrace, 43, 24, &self->inventory);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Guild_set_to_GuildPtr_charPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Guild* self, char* display_name_str) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    void_string_set_literal_Array_char_100Ptr_charPtr(ct_stacktrace, 65, 28, &self->display_name, display_name_str);
    ct_stacktrace_pop(ct_stacktrace);
}

