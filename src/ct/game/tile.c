#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "ct_stacktrace.h"
#include "tile.h"
#include "image.h"
#include "utils.h"
#include "image.h"
#include "ct_array.h"
#include "sprite.h"
#include "shared_sprite.h"
#include "game.h"

void void_mfunc_Tile_update_TilePtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Tile* self, Game* game) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    void_mfunc_SharedSprite_update_SharedSpritePtr_GamePtr(ct_stacktrace, 159, 13, &self->sprite, game);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_Tile_draw_TilePtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Tile* self, Game* game) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    void_mfunc_SharedSprite_draw_SharedSpritePtr_GamePtr(ct_stacktrace, 197, 16, &self->sprite, game);
    ct_stacktrace_pop(ct_stacktrace);
}

