#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "ct_stacktrace.h"
#include "ai.h"
#include "engine.h"
#include "utils.h"
#include "ct_array.h"
#include "constants.h"
#include "game.h"

void void_mfunc_AIAbility_clear_AIAbilityPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, AIAbility* self) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->is_empty = true;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_AIAbility_set_AIAbilityPtr_int_AIAbilityCondition(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, AIAbility* self, int unit_ability_handle, AIAbilityCondition condition) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->unit_ability_handle = unit_ability_handle;
    self->condition = condition;
    self->is_empty = false;
    ct_stacktrace_pop(ct_stacktrace);
}

