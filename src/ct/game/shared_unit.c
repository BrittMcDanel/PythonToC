#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "ct_stacktrace.h"
#include "shared_unit.h"
#include "engine.h"
#include "image.h"
#include "utils.h"
#include "image.h"
#include "ct_array.h"
#include "constants.h"
#include "unit.h"
#include "game.h"

void void_mfunc_UnitDB_init_UnitDBPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitDB* self, Game* game) {
    UnitName unit_name = (UnitName) 0;
    int last_enum_idx = 0;
    int i = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->units.size = 200;
    last_enum_idx = 12;
    if (last_enum_idx > (self->units.size - 1)) {
        printf("%s\n", "UnitDB.init - UnitName's last enum idx is > units capacity.");
        ct_stacktrace_push(ct_stacktrace, 33, 19);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    for (i = 1; i < last_enum_idx; i += 1) {
        unit_name = (UnitName)(i);
        void_mfunc_Unit_init_UnitPtr_GamePtr_int(ct_stacktrace, 33, 23, &game->temp_unit, game, 0);
        void_mfunc_Unit_set_to_UnitPtr_GamePtr_UnitName_Faction(ct_stacktrace, 33, 24, &game->temp_unit, game, unit_name, Faction_Ally);
        if (i < 0 || i > self->units.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->units.size);
                ct_stacktrace_push(ct_stacktrace, 33, 25);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            self->units.arr[i] = game->temp_unit;
    }
    ct_stacktrace_pop(ct_stacktrace);
}

Unit* UnitPtr_mfunc_UnitDB_get_unit_UnitDBPtr_UnitName(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, UnitDB* self, UnitName unit_name) {
    int unit_name_as_int = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    unit_name_as_int = (int)(unit_name);
    if (unit_name_as_int < 0 || unit_name_as_int > self->units.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", unit_name_as_int, self->units.size);
            ct_stacktrace_push(ct_stacktrace, 180, 29);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
            ct_stacktrace_pop(ct_stacktrace);
return &self->units.arr[unit_name_as_int];
}

