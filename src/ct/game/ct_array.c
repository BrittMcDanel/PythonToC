#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "ct_stacktrace.h"
#include "ct_array.h"
#include "tile.h"
#include "unit.h"
#include "map.h"
#include "tween.h"
#include "guild.h"
#include "path_finder.h"
#include "game.h"
#include "ability.h"
#include "text.h"
#include "building.h"
#include "shared_sprite.h"
#include "item.h"
#include "shared_item.h"
#include "shared_ability.h"
#include "ui.h"
#include "ui_containers.h"
#include "ai.h"
#include "warp_point.h"

void void_push_value_Array_bool_322Ptr_bool(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_bool_322* arr, bool value) {
    int capacity = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    capacity = 322;
    if (arr->size > (capacity - 1)) {
        printf("%s %s %d %s %d\n", "push_value - array size is > than capacity - 1.", "size:", arr->size, "capacity:", capacity);
        ct_stacktrace_push(ct_stacktrace, 2, 45);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    arr->arr[arr->size] = value;
    arr->size += 1;
    ct_stacktrace_pop(ct_stacktrace);
}

SpriteSrcs* SpriteSrcsPtr_next_Array_SpriteSrcs_200Ptr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_SpriteSrcs_200* arr) {
    SpriteSrcs* value = NULL;
    int capacity = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    capacity = 200;
    if (arr->size > (capacity - 1)) {
        printf("%s %s %d %s %d\n", "next - array size is > than capacity - 1.", "size:", arr->size, "capacity:", capacity);
        ct_stacktrace_push(ct_stacktrace, 5, 66);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    value = &arr->arr[arr->size];
    arr->size += 1;
        ct_stacktrace_pop(ct_stacktrace);
return value;
}

void void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_SDL_Rect_10* arr, SDL_Rect* value_ptr) {
    int capacity = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    capacity = 10;
    if (arr->size > (capacity - 1)) {
        printf("%s %s %d %s %d\n", "push - array size is > than capacity - 1.", "size:", arr->size, "capacity:", capacity);
        ct_stacktrace_push(ct_stacktrace, 7, 36);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    arr->arr[arr->size] = *value_ptr;
    arr->size += 1;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_clear_Array_SDL_Rect_10Ptr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_SDL_Rect_10* arr) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    arr->size = 0;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_string_set_literal_Array_char_200Ptr_charPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_char_200* arr, char* string_literal) {
    char* buffer = NULL;
    int length = 0;
    int capacity = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    capacity = 200;
    length = strlen(string_literal);
    buffer = arr->arr;
    if (length > (capacity - 1)) {
        printf("%s %s %d %s %d %s %s %s %s\n", "string_set_literal - string literal length is > then the capacity of arr.", "\nstring literal length:", length, "\narr capacity:", capacity, "\narr str:", buffer, "\nstring_literal:", string_literal);
        ct_stacktrace_push(ct_stacktrace, 17, 107);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    strcpy(buffer, string_literal);
    arr->size = length;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_clear_Array_SharedAbility_10Ptr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_SharedAbility_10* arr) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    arr->size = 0;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_clear_Array_SharedAbility_30Ptr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_SharedAbility_30* arr) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    arr->size = 0;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_clear_Array_SharedItem_5Ptr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_SharedItem_5* arr) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    arr->size = 0;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_clear_Array_SDL_Rect_3Ptr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_SDL_Rect_3* arr) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    arr->size = 0;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_push_Array_SDL_Rect_3Ptr_SDL_RectPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_SDL_Rect_3* arr, SDL_Rect* value_ptr) {
    int capacity = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    capacity = 3;
    if (arr->size > (capacity - 1)) {
        printf("%s %s %d %s %d\n", "push - array size is > than capacity - 1.", "size:", arr->size, "capacity:", capacity);
        ct_stacktrace_push(ct_stacktrace, 7, 36);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    arr->arr[arr->size] = *value_ptr;
    arr->size += 1;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_string_set_literal_Array_char_100Ptr_charPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_char_100* arr, char* string_literal) {
    char* buffer = NULL;
    int length = 0;
    int capacity = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    capacity = 100;
    length = strlen(string_literal);
    buffer = arr->arr;
    if (length > (capacity - 1)) {
        printf("%s %s %d %s %d %s %s %s %s\n", "string_set_literal - string literal length is > then the capacity of arr.", "\nstring literal length:", length, "\narr capacity:", capacity, "\narr str:", buffer, "\nstring_literal:", string_literal);
        ct_stacktrace_push(ct_stacktrace, 17, 107);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    strcpy(buffer, string_literal);
    arr->size = length;
    ct_stacktrace_pop(ct_stacktrace);
}

SharedAbility* SharedAbilityPtr_next_Array_SharedAbility_10Ptr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_SharedAbility_10* arr) {
    SharedAbility* value = NULL;
    int capacity = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    capacity = 10;
    if (arr->size > (capacity - 1)) {
        printf("%s %s %d %s %d\n", "next - array size is > than capacity - 1.", "size:", arr->size, "capacity:", capacity);
        ct_stacktrace_push(ct_stacktrace, 5, 66);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    value = &arr->arr[arr->size];
    arr->size += 1;
        ct_stacktrace_pop(ct_stacktrace);
return value;
}

SharedAbility* SharedAbilityPtr_next_Array_SharedAbility_30Ptr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_SharedAbility_30* arr) {
    SharedAbility* value = NULL;
    int capacity = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    capacity = 30;
    if (arr->size > (capacity - 1)) {
        printf("%s %s %d %s %d\n", "next - array size is > than capacity - 1.", "size:", arr->size, "capacity:", capacity);
        ct_stacktrace_push(ct_stacktrace, 5, 66);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    value = &arr->arr[arr->size];
    arr->size += 1;
        ct_stacktrace_pop(ct_stacktrace);
return value;
}

void void_push_Array_SharedItem_5Ptr_SharedItemPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_SharedItem_5* arr, SharedItem* value_ptr) {
    int capacity = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    capacity = 5;
    if (arr->size > (capacity - 1)) {
        printf("%s %s %d %s %d\n", "push - array size is > than capacity - 1.", "size:", arr->size, "capacity:", capacity);
        ct_stacktrace_push(ct_stacktrace, 7, 36);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    arr->arr[arr->size] = *value_ptr;
    arr->size += 1;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_string_set_Array_char_200Ptr_Array_char_100Ptr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_char_200* arr1, Array_char_100* arr2) {
    int capacity = 0;
    char* buffer2 = NULL;
    char* buffer1 = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    capacity = 200;
    buffer1 = arr1->arr;
    buffer2 = arr2->arr;
    if (arr2->size > (capacity - 1)) {
        printf("%s %s %d %s %d %s %s %s %s\n", "string_set - arr2.size > then the capacity of arr1", "\narr2.size:", arr2->size, "\narr1 capacity:", capacity, "\narr1 str:", buffer1, "\narr2 str:", buffer2);
        ct_stacktrace_push(ct_stacktrace, 31, 120);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    strcpy(buffer1, buffer2);
    arr1->size = arr2->size;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_pool_init_GamePtr_Array_Map_100Ptr_intPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Game* game, Array_Map_100* arr, int* last_in_use_handle_ptr) {
    Map* item = NULL;
    int i = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    arr->size = 100;
    *last_in_use_handle_ptr = -1;
    for (i = 0; i < arr->size; i++) {
        item = &arr->arr[i];
        void_mfunc_Map_init_MapPtr_GamePtr_int(ct_stacktrace, 41, 181, item, game, i);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_pool_init_GamePtr_Array_Building_2000Ptr_intPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Game* game, Array_Building_2000* arr, int* last_in_use_handle_ptr) {
    Building* item = NULL;
    int i = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    arr->size = 2000;
    *last_in_use_handle_ptr = -1;
    for (i = 0; i < arr->size; i++) {
        item = &arr->arr[i];
        void_mfunc_Building_init_BuildingPtr_GamePtr_int(ct_stacktrace, 41, 181, item, game, i);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_pool_init_GamePtr_Array_Unit_3000Ptr_intPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Game* game, Array_Unit_3000* arr, int* last_in_use_handle_ptr) {
    Unit* item = NULL;
    int i = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    arr->size = 3000;
    *last_in_use_handle_ptr = -1;
    for (i = 0; i < arr->size; i++) {
        item = &arr->arr[i];
        void_mfunc_Unit_init_UnitPtr_GamePtr_int(ct_stacktrace, 41, 181, item, game, i);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_pool_init_GamePtr_Array_Guild_100Ptr_intPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Game* game, Array_Guild_100* arr, int* last_in_use_handle_ptr) {
    Guild* item = NULL;
    int i = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    arr->size = 100;
    *last_in_use_handle_ptr = -1;
    for (i = 0; i < arr->size; i++) {
        item = &arr->arr[i];
        void_mfunc_Guild_init_GuildPtr_GamePtr_int(ct_stacktrace, 41, 181, item, game, i);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_pool_init_GamePtr_Array_SharedItem_5000Ptr_intPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Game* game, Array_SharedItem_5000* arr, int* last_in_use_handle_ptr) {
    SharedItem* item = NULL;
    int i = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    arr->size = 5000;
    *last_in_use_handle_ptr = -1;
    for (i = 0; i < arr->size; i++) {
        item = &arr->arr[i];
        void_mfunc_SharedItem_init_SharedItemPtr_GamePtr_int(ct_stacktrace, 41, 181, item, game, i);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_pool_init_GamePtr_Array_SharedAbility_5000Ptr_intPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Game* game, Array_SharedAbility_5000* arr, int* last_in_use_handle_ptr) {
    SharedAbility* item = NULL;
    int i = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    arr->size = 5000;
    *last_in_use_handle_ptr = -1;
    for (i = 0; i < arr->size; i++) {
        item = &arr->arr[i];
        void_mfunc_SharedAbility_init_SharedAbilityPtr_GamePtr_int(ct_stacktrace, 41, 181, item, game, i);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_pool_of_text_init_GamePtr_Array_TextSM_5000Ptr_intPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Game* game, Array_TextSM_5000* arr, int* last_in_use_handle_ptr) {
    TextSM* item = NULL;
    int i = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    arr->size = 5000;
    *last_in_use_handle_ptr = -1;
    for (i = 0; i < arr->size; i++) {
        item = &arr->arr[i];
        void_text_init_TextSMPtr_GamePtr_int(ct_stacktrace, 47, 189, item, game, i);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_pool_init_GamePtr_Array_TweenXY_20000Ptr_intPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Game* game, Array_TweenXY_20000* arr, int* last_in_use_handle_ptr) {
    TweenXY* item = NULL;
    int i = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    arr->size = 20000;
    *last_in_use_handle_ptr = -1;
    for (i = 0; i < arr->size; i++) {
        item = &arr->arr[i];
        void_mfunc_TweenXY_init_TweenXYPtr_GamePtr_int(ct_stacktrace, 41, 181, item, game, i);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

int int_pool_get_handle_Array_Map_100Ptr_intPtr_charPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_Map_100* arr, int* last_in_use_handle_ptr, char* debug_pool_name_char_ptr) {
    int capacity = 0;
    Map* item = NULL;
    int i = 0;
    int last_in_use_handle = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    last_in_use_handle = *last_in_use_handle_ptr;
    for (i = 0; i < arr->size; i++) {
        item = &arr->arr[i];
        if (!(item->in_use_in_pool)) {
            item->in_use_in_pool = true;
            if (i > last_in_use_handle) {
                *last_in_use_handle_ptr = i;
}
                        ct_stacktrace_pop(ct_stacktrace);
return i;
    }
}
    capacity = 100;
    printf("%s\n", "pool_get_handle - all elements are in use.");
    printf("%s %s %s %d %s %d\n", "pool name:", debug_pool_name_char_ptr, "\npool size: ", arr->size, "\npool capacity:", capacity);
    ct_stacktrace_push(ct_stacktrace, 49, 205);
    ct_stacktrace_print(ct_stacktrace);
    exit(1);
    ct_stacktrace_pop(ct_stacktrace);
}

int int_pool_get_handle_Array_Building_2000Ptr_intPtr_charPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_Building_2000* arr, int* last_in_use_handle_ptr, char* debug_pool_name_char_ptr) {
    int capacity = 0;
    Building* item = NULL;
    int i = 0;
    int last_in_use_handle = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    last_in_use_handle = *last_in_use_handle_ptr;
    for (i = 0; i < arr->size; i++) {
        item = &arr->arr[i];
        if (!(item->in_use_in_pool)) {
            item->in_use_in_pool = true;
            if (i > last_in_use_handle) {
                *last_in_use_handle_ptr = i;
}
                        ct_stacktrace_pop(ct_stacktrace);
return i;
    }
}
    capacity = 2000;
    printf("%s\n", "pool_get_handle - all elements are in use.");
    printf("%s %s %s %d %s %d\n", "pool name:", debug_pool_name_char_ptr, "\npool size: ", arr->size, "\npool capacity:", capacity);
    ct_stacktrace_push(ct_stacktrace, 49, 205);
    ct_stacktrace_print(ct_stacktrace);
    exit(1);
    ct_stacktrace_pop(ct_stacktrace);
}

int int_pool_get_handle_Array_Unit_3000Ptr_intPtr_charPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_Unit_3000* arr, int* last_in_use_handle_ptr, char* debug_pool_name_char_ptr) {
    int capacity = 0;
    Unit* item = NULL;
    int i = 0;
    int last_in_use_handle = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    last_in_use_handle = *last_in_use_handle_ptr;
    for (i = 0; i < arr->size; i++) {
        item = &arr->arr[i];
        if (!(item->in_use_in_pool)) {
            item->in_use_in_pool = true;
            if (i > last_in_use_handle) {
                *last_in_use_handle_ptr = i;
}
                        ct_stacktrace_pop(ct_stacktrace);
return i;
    }
}
    capacity = 3000;
    printf("%s\n", "pool_get_handle - all elements are in use.");
    printf("%s %s %s %d %s %d\n", "pool name:", debug_pool_name_char_ptr, "\npool size: ", arr->size, "\npool capacity:", capacity);
    ct_stacktrace_push(ct_stacktrace, 49, 205);
    ct_stacktrace_print(ct_stacktrace);
    exit(1);
    ct_stacktrace_pop(ct_stacktrace);
}

int int_pool_get_handle_Array_Guild_100Ptr_intPtr_charPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_Guild_100* arr, int* last_in_use_handle_ptr, char* debug_pool_name_char_ptr) {
    int capacity = 0;
    Guild* item = NULL;
    int i = 0;
    int last_in_use_handle = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    last_in_use_handle = *last_in_use_handle_ptr;
    for (i = 0; i < arr->size; i++) {
        item = &arr->arr[i];
        if (!(item->in_use_in_pool)) {
            item->in_use_in_pool = true;
            if (i > last_in_use_handle) {
                *last_in_use_handle_ptr = i;
}
                        ct_stacktrace_pop(ct_stacktrace);
return i;
    }
}
    capacity = 100;
    printf("%s\n", "pool_get_handle - all elements are in use.");
    printf("%s %s %s %d %s %d\n", "pool name:", debug_pool_name_char_ptr, "\npool size: ", arr->size, "\npool capacity:", capacity);
    ct_stacktrace_push(ct_stacktrace, 49, 205);
    ct_stacktrace_print(ct_stacktrace);
    exit(1);
    ct_stacktrace_pop(ct_stacktrace);
}

int int_pool_get_handle_Array_SharedItem_5000Ptr_intPtr_charPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_SharedItem_5000* arr, int* last_in_use_handle_ptr, char* debug_pool_name_char_ptr) {
    int capacity = 0;
    SharedItem* item = NULL;
    int i = 0;
    int last_in_use_handle = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    last_in_use_handle = *last_in_use_handle_ptr;
    for (i = 0; i < arr->size; i++) {
        item = &arr->arr[i];
        if (!(item->in_use_in_pool)) {
            item->in_use_in_pool = true;
            if (i > last_in_use_handle) {
                *last_in_use_handle_ptr = i;
}
                        ct_stacktrace_pop(ct_stacktrace);
return i;
    }
}
    capacity = 5000;
    printf("%s\n", "pool_get_handle - all elements are in use.");
    printf("%s %s %s %d %s %d\n", "pool name:", debug_pool_name_char_ptr, "\npool size: ", arr->size, "\npool capacity:", capacity);
    ct_stacktrace_push(ct_stacktrace, 49, 205);
    ct_stacktrace_print(ct_stacktrace);
    exit(1);
    ct_stacktrace_pop(ct_stacktrace);
}

int int_pool_get_handle_Array_SharedAbility_5000Ptr_intPtr_charPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_SharedAbility_5000* arr, int* last_in_use_handle_ptr, char* debug_pool_name_char_ptr) {
    int capacity = 0;
    SharedAbility* item = NULL;
    int i = 0;
    int last_in_use_handle = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    last_in_use_handle = *last_in_use_handle_ptr;
    for (i = 0; i < arr->size; i++) {
        item = &arr->arr[i];
        if (!(item->in_use_in_pool)) {
            item->in_use_in_pool = true;
            if (i > last_in_use_handle) {
                *last_in_use_handle_ptr = i;
}
                        ct_stacktrace_pop(ct_stacktrace);
return i;
    }
}
    capacity = 5000;
    printf("%s\n", "pool_get_handle - all elements are in use.");
    printf("%s %s %s %d %s %d\n", "pool name:", debug_pool_name_char_ptr, "\npool size: ", arr->size, "\npool capacity:", capacity);
    ct_stacktrace_push(ct_stacktrace, 49, 205);
    ct_stacktrace_print(ct_stacktrace);
    exit(1);
    ct_stacktrace_pop(ct_stacktrace);
}

int int_pool_get_handle_Array_TweenXY_20000Ptr_intPtr_charPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_TweenXY_20000* arr, int* last_in_use_handle_ptr, char* debug_pool_name_char_ptr) {
    int capacity = 0;
    TweenXY* item = NULL;
    int i = 0;
    int last_in_use_handle = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    last_in_use_handle = *last_in_use_handle_ptr;
    for (i = 0; i < arr->size; i++) {
        item = &arr->arr[i];
        if (!(item->in_use_in_pool)) {
            item->in_use_in_pool = true;
            if (i > last_in_use_handle) {
                *last_in_use_handle_ptr = i;
}
                        ct_stacktrace_pop(ct_stacktrace);
return i;
    }
}
    capacity = 20000;
    printf("%s\n", "pool_get_handle - all elements are in use.");
    printf("%s %s %s %d %s %d\n", "pool name:", debug_pool_name_char_ptr, "\npool size: ", arr->size, "\npool capacity:", capacity);
    ct_stacktrace_push(ct_stacktrace, 49, 205);
    ct_stacktrace_print(ct_stacktrace);
    exit(1);
    ct_stacktrace_pop(ct_stacktrace);
}

int int_pool_get_handle_Array_TextSM_5000Ptr_intPtr_charPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_TextSM_5000* arr, int* last_in_use_handle_ptr, char* debug_pool_name_char_ptr) {
    int capacity = 0;
    TextSM* item = NULL;
    int i = 0;
    int last_in_use_handle = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    last_in_use_handle = *last_in_use_handle_ptr;
    for (i = 0; i < arr->size; i++) {
        item = &arr->arr[i];
        if (!(item->in_use_in_pool)) {
            item->in_use_in_pool = true;
            if (i > last_in_use_handle) {
                *last_in_use_handle_ptr = i;
}
                        ct_stacktrace_pop(ct_stacktrace);
return i;
    }
}
    capacity = 5000;
    printf("%s\n", "pool_get_handle - all elements are in use.");
    printf("%s %s %s %d %s %d\n", "pool name:", debug_pool_name_char_ptr, "\npool size: ", arr->size, "\npool capacity:", capacity);
    ct_stacktrace_push(ct_stacktrace, 49, 205);
    ct_stacktrace_print(ct_stacktrace);
    exit(1);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_push_Array_Tile_10000Ptr_TilePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_Tile_10000* arr, Tile* value_ptr) {
    int capacity = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    capacity = 10000;
    if (arr->size > (capacity - 1)) {
        printf("%s %s %d %s %d\n", "push - array size is > than capacity - 1.", "size:", arr->size, "capacity:", capacity);
        ct_stacktrace_push(ct_stacktrace, 7, 36);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    arr->arr[arr->size] = *value_ptr;
    arr->size += 1;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_push_Array_WarpPoint_7Ptr_WarpPointPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_WarpPoint_7* arr, WarpPoint* value_ptr) {
    int capacity = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    capacity = 7;
    if (arr->size > (capacity - 1)) {
        printf("%s %s %d %s %d\n", "push - array size is > than capacity - 1.", "size:", arr->size, "capacity:", capacity);
        ct_stacktrace_push(ct_stacktrace, 7, 36);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    arr->arr[arr->size] = *value_ptr;
    arr->size += 1;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_remove_at_Array_int_300Ptr_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_int_300* arr, int idx) {
    int i = 0;
    int next_idx = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    if ((idx < 0 || idx > (arr->size - 1))) {
        printf("%s %d %d\n", "remove_at - idx is out of bounds", idx, arr->size);
        ct_stacktrace_push(ct_stacktrace, 55, 85);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    arr->size -= 1;
    for (i = idx; i < arr->size; i += 1) {
        next_idx = (i + 1);
        arr->arr[i] = arr->arr[next_idx];
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_find_and_remove_handle_Array_int_300Ptr_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_int_300* arr, int handle_to_remove) {
    int handle = 0;
    int i = 0;
    int handle_to_remove_idx = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    handle_to_remove_idx = -1;
    for (i = 0; i < arr->size; i += 1) {
        if (i < 0 || i > arr->size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", i, arr->size);
            ct_stacktrace_push(ct_stacktrace, 56, 169);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        handle = arr->arr[i];
        if (handle == handle_to_remove) {
            handle_to_remove_idx = i;
            break;
    }
}
    if (handle_to_remove_idx != -1) {
        void_remove_at_Array_int_300Ptr_int(ct_stacktrace, 56, 174, arr, handle_to_remove_idx);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_push_value_Array_int_300Ptr_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_int_300* arr, int value) {
    int capacity = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    capacity = 300;
    if (arr->size > (capacity - 1)) {
        printf("%s %s %d %s %d\n", "push_value - array size is > than capacity - 1.", "size:", arr->size, "capacity:", capacity);
        ct_stacktrace_push(ct_stacktrace, 2, 45);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    arr->arr[arr->size] = value;
    arr->size += 1;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_push_value_Array_int_100Ptr_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_int_100* arr, int value) {
    int capacity = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    capacity = 100;
    if (arr->size > (capacity - 1)) {
        printf("%s %s %d %s %d\n", "push_value - array size is > than capacity - 1.", "size:", arr->size, "capacity:", capacity);
        ct_stacktrace_push(ct_stacktrace, 2, 45);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    arr->arr[arr->size] = value;
    arr->size += 1;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_push_value_Array_int_30Ptr_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_int_30* arr, int value) {
    int capacity = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    capacity = 30;
    if (arr->size > (capacity - 1)) {
        printf("%s %s %d %s %d\n", "push_value - array size is > than capacity - 1.", "size:", arr->size, "capacity:", capacity);
        ct_stacktrace_push(ct_stacktrace, 2, 45);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    arr->arr[arr->size] = value;
    arr->size += 1;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_string_cat_Array_char_100Ptr_Array_char_100Ptr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_char_100* arr1, Array_char_100* arr2) {
    int capacity = 0;
    char* buffer2 = NULL;
    char* buffer1 = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    capacity = 100;
    buffer1 = arr1->arr;
    buffer2 = arr2->arr;
    if (arr2->size == 0) {
                ct_stacktrace_pop(ct_stacktrace);
return;
}
    if (arr1->size == 0) {
        void_string_set_literal_Array_char_100Ptr_charPtr(ct_stacktrace, 68, 157, arr1, "");
}
    if ((arr1->size + arr2->size) > (capacity - 1)) {
        printf("%s %s %d %s %d %s %d %s %s %s %s\n", "string_cat - arr1.size + arr2.size is > then the capacity of arr.", "\narr1 size:", arr1->size, "\narr2 size:", arr2->size, "\narr capacity:", capacity, "\narr1 str:", buffer1, "\narr2 str:", buffer2);
        ct_stacktrace_push(ct_stacktrace, 68, 160);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    strcat(buffer1, buffer2);
    arr1->size += arr2->size;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_string_cat_literal_Array_char_100Ptr_charPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_char_100* arr, char* string_literal) {
    char* buffer = NULL;
    int length = 0;
    int capacity = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    capacity = 100;
    length = strlen(string_literal);
    buffer = arr->arr;
    if (length == 0) {
                ct_stacktrace_pop(ct_stacktrace);
return;
}
    if (arr->size == 0) {
        void_string_set_literal_Array_char_100Ptr_charPtr(ct_stacktrace, 69, 137, arr, "");
}
    if ((arr->size + length) > (capacity - 1)) {
        printf("%s %s %d %s %d %s %d %s %s %s %s\n", "string_cat_literal - arr.size + string literal length is > then the capacity of arr.", "\narr size:", arr->size, "\nstring literal length:", length, "\narr capacity:", capacity, "\narr str:", buffer, "\nstring_literal:", string_literal);
        ct_stacktrace_push(ct_stacktrace, 69, 140);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    strcat(buffer, string_literal);
    arr->size += length;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_clear_Array_UIRenderable_300Ptr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_UIRenderable_300* arr) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    arr->size = 0;
    ct_stacktrace_pop(ct_stacktrace);
}

int int_pool_get_last_in_use_handle_Array_Map_100Ptr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_Map_100* arr) {
    Map* item = NULL;
    int i = 0;
    int max_handle = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    max_handle = -1;
    for (i = 0; i < arr->size; i++) {
        item = &arr->arr[i];
        if (item->in_use_in_pool) {
            max_handle = i;
    }
}
        ct_stacktrace_pop(ct_stacktrace);
return max_handle;
}

void void_pool_release_handle_Array_Map_100Ptr_int_intPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_Map_100* arr, int handle, int* last_in_use_handle_ptr) {
    Map* item = NULL;
    int last_in_use_handle = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    last_in_use_handle = *last_in_use_handle_ptr;
    if (handle < 0 || handle > arr->size - 1) {
        printf("Out of bounds error: idx: %d size: %d.\n", handle, arr->size);
        ct_stacktrace_push(ct_stacktrace, 84, 210);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
    }
    item = &arr->arr[handle];
    if (!(item->in_use_in_pool)) {
        printf("%s\n", "pool_release_handle - tried to release an inactive item. Item must be active to be released.");
        ct_stacktrace_push(ct_stacktrace, 84, 213);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    item->in_use_in_pool = false;
    if (handle == last_in_use_handle) {
        *last_in_use_handle_ptr = int_pool_get_last_in_use_handle_Array_Map_100Ptr(ct_stacktrace, 84, 221, arr);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

int int_pool_get_last_in_use_handle_Array_Building_2000Ptr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_Building_2000* arr) {
    Building* item = NULL;
    int i = 0;
    int max_handle = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    max_handle = -1;
    for (i = 0; i < arr->size; i++) {
        item = &arr->arr[i];
        if (item->in_use_in_pool) {
            max_handle = i;
    }
}
        ct_stacktrace_pop(ct_stacktrace);
return max_handle;
}

void void_pool_release_handle_Array_Building_2000Ptr_int_intPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_Building_2000* arr, int handle, int* last_in_use_handle_ptr) {
    Building* item = NULL;
    int last_in_use_handle = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    last_in_use_handle = *last_in_use_handle_ptr;
    if (handle < 0 || handle > arr->size - 1) {
        printf("Out of bounds error: idx: %d size: %d.\n", handle, arr->size);
        ct_stacktrace_push(ct_stacktrace, 84, 210);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
    }
    item = &arr->arr[handle];
    if (!(item->in_use_in_pool)) {
        printf("%s\n", "pool_release_handle - tried to release an inactive item. Item must be active to be released.");
        ct_stacktrace_push(ct_stacktrace, 84, 213);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    item->in_use_in_pool = false;
    if (handle == last_in_use_handle) {
        *last_in_use_handle_ptr = int_pool_get_last_in_use_handle_Array_Building_2000Ptr(ct_stacktrace, 84, 221, arr);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

int int_pool_get_last_in_use_handle_Array_Unit_3000Ptr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_Unit_3000* arr) {
    Unit* item = NULL;
    int i = 0;
    int max_handle = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    max_handle = -1;
    for (i = 0; i < arr->size; i++) {
        item = &arr->arr[i];
        if (item->in_use_in_pool) {
            max_handle = i;
    }
}
        ct_stacktrace_pop(ct_stacktrace);
return max_handle;
}

void void_pool_release_handle_Array_Unit_3000Ptr_int_intPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_Unit_3000* arr, int handle, int* last_in_use_handle_ptr) {
    Unit* item = NULL;
    int last_in_use_handle = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    last_in_use_handle = *last_in_use_handle_ptr;
    if (handle < 0 || handle > arr->size - 1) {
        printf("Out of bounds error: idx: %d size: %d.\n", handle, arr->size);
        ct_stacktrace_push(ct_stacktrace, 84, 210);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
    }
    item = &arr->arr[handle];
    if (!(item->in_use_in_pool)) {
        printf("%s\n", "pool_release_handle - tried to release an inactive item. Item must be active to be released.");
        ct_stacktrace_push(ct_stacktrace, 84, 213);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    item->in_use_in_pool = false;
    if (handle == last_in_use_handle) {
        *last_in_use_handle_ptr = int_pool_get_last_in_use_handle_Array_Unit_3000Ptr(ct_stacktrace, 84, 221, arr);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

int int_pool_get_last_in_use_handle_Array_Guild_100Ptr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_Guild_100* arr) {
    Guild* item = NULL;
    int i = 0;
    int max_handle = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    max_handle = -1;
    for (i = 0; i < arr->size; i++) {
        item = &arr->arr[i];
        if (item->in_use_in_pool) {
            max_handle = i;
    }
}
        ct_stacktrace_pop(ct_stacktrace);
return max_handle;
}

void void_pool_release_handle_Array_Guild_100Ptr_int_intPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_Guild_100* arr, int handle, int* last_in_use_handle_ptr) {
    Guild* item = NULL;
    int last_in_use_handle = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    last_in_use_handle = *last_in_use_handle_ptr;
    if (handle < 0 || handle > arr->size - 1) {
        printf("Out of bounds error: idx: %d size: %d.\n", handle, arr->size);
        ct_stacktrace_push(ct_stacktrace, 84, 210);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
    }
    item = &arr->arr[handle];
    if (!(item->in_use_in_pool)) {
        printf("%s\n", "pool_release_handle - tried to release an inactive item. Item must be active to be released.");
        ct_stacktrace_push(ct_stacktrace, 84, 213);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    item->in_use_in_pool = false;
    if (handle == last_in_use_handle) {
        *last_in_use_handle_ptr = int_pool_get_last_in_use_handle_Array_Guild_100Ptr(ct_stacktrace, 84, 221, arr);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

int int_pool_get_last_in_use_handle_Array_SharedItem_5000Ptr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_SharedItem_5000* arr) {
    SharedItem* item = NULL;
    int i = 0;
    int max_handle = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    max_handle = -1;
    for (i = 0; i < arr->size; i++) {
        item = &arr->arr[i];
        if (item->in_use_in_pool) {
            max_handle = i;
    }
}
        ct_stacktrace_pop(ct_stacktrace);
return max_handle;
}

void void_pool_release_handle_Array_SharedItem_5000Ptr_int_intPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_SharedItem_5000* arr, int handle, int* last_in_use_handle_ptr) {
    SharedItem* item = NULL;
    int last_in_use_handle = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    last_in_use_handle = *last_in_use_handle_ptr;
    if (handle < 0 || handle > arr->size - 1) {
        printf("Out of bounds error: idx: %d size: %d.\n", handle, arr->size);
        ct_stacktrace_push(ct_stacktrace, 84, 210);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
    }
    item = &arr->arr[handle];
    if (!(item->in_use_in_pool)) {
        printf("%s\n", "pool_release_handle - tried to release an inactive item. Item must be active to be released.");
        ct_stacktrace_push(ct_stacktrace, 84, 213);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    item->in_use_in_pool = false;
    if (handle == last_in_use_handle) {
        *last_in_use_handle_ptr = int_pool_get_last_in_use_handle_Array_SharedItem_5000Ptr(ct_stacktrace, 84, 221, arr);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

int int_pool_get_last_in_use_handle_Array_SharedAbility_5000Ptr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_SharedAbility_5000* arr) {
    SharedAbility* item = NULL;
    int i = 0;
    int max_handle = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    max_handle = -1;
    for (i = 0; i < arr->size; i++) {
        item = &arr->arr[i];
        if (item->in_use_in_pool) {
            max_handle = i;
    }
}
        ct_stacktrace_pop(ct_stacktrace);
return max_handle;
}

void void_pool_release_handle_Array_SharedAbility_5000Ptr_int_intPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_SharedAbility_5000* arr, int handle, int* last_in_use_handle_ptr) {
    SharedAbility* item = NULL;
    int last_in_use_handle = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    last_in_use_handle = *last_in_use_handle_ptr;
    if (handle < 0 || handle > arr->size - 1) {
        printf("Out of bounds error: idx: %d size: %d.\n", handle, arr->size);
        ct_stacktrace_push(ct_stacktrace, 84, 210);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
    }
    item = &arr->arr[handle];
    if (!(item->in_use_in_pool)) {
        printf("%s\n", "pool_release_handle - tried to release an inactive item. Item must be active to be released.");
        ct_stacktrace_push(ct_stacktrace, 84, 213);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    item->in_use_in_pool = false;
    if (handle == last_in_use_handle) {
        *last_in_use_handle_ptr = int_pool_get_last_in_use_handle_Array_SharedAbility_5000Ptr(ct_stacktrace, 84, 221, arr);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

int int_pool_get_last_in_use_handle_Array_TweenXY_20000Ptr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_TweenXY_20000* arr) {
    TweenXY* item = NULL;
    int i = 0;
    int max_handle = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    max_handle = -1;
    for (i = 0; i < arr->size; i++) {
        item = &arr->arr[i];
        if (item->in_use_in_pool) {
            max_handle = i;
    }
}
        ct_stacktrace_pop(ct_stacktrace);
return max_handle;
}

void void_pool_release_handle_Array_TweenXY_20000Ptr_int_intPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_TweenXY_20000* arr, int handle, int* last_in_use_handle_ptr) {
    TweenXY* item = NULL;
    int last_in_use_handle = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    last_in_use_handle = *last_in_use_handle_ptr;
    if (handle < 0 || handle > arr->size - 1) {
        printf("Out of bounds error: idx: %d size: %d.\n", handle, arr->size);
        ct_stacktrace_push(ct_stacktrace, 84, 210);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
    }
    item = &arr->arr[handle];
    if (!(item->in_use_in_pool)) {
        printf("%s\n", "pool_release_handle - tried to release an inactive item. Item must be active to be released.");
        ct_stacktrace_push(ct_stacktrace, 84, 213);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    item->in_use_in_pool = false;
    if (handle == last_in_use_handle) {
        *last_in_use_handle_ptr = int_pool_get_last_in_use_handle_Array_TweenXY_20000Ptr(ct_stacktrace, 84, 221, arr);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

int int_pool_get_last_in_use_handle_Array_TextSM_5000Ptr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_TextSM_5000* arr) {
    TextSM* item = NULL;
    int i = 0;
    int max_handle = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    max_handle = -1;
    for (i = 0; i < arr->size; i++) {
        item = &arr->arr[i];
        if (item->in_use_in_pool) {
            max_handle = i;
    }
}
        ct_stacktrace_pop(ct_stacktrace);
return max_handle;
}

void void_pool_release_handle_Array_TextSM_5000Ptr_int_intPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_TextSM_5000* arr, int handle, int* last_in_use_handle_ptr) {
    TextSM* item = NULL;
    int last_in_use_handle = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    last_in_use_handle = *last_in_use_handle_ptr;
    if (handle < 0 || handle > arr->size - 1) {
        printf("Out of bounds error: idx: %d size: %d.\n", handle, arr->size);
        ct_stacktrace_push(ct_stacktrace, 84, 210);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
    }
    item = &arr->arr[handle];
    if (!(item->in_use_in_pool)) {
        printf("%s\n", "pool_release_handle - tried to release an inactive item. Item must be active to be released.");
        ct_stacktrace_push(ct_stacktrace, 84, 213);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    item->in_use_in_pool = false;
    if (handle == last_in_use_handle) {
        *last_in_use_handle_ptr = int_pool_get_last_in_use_handle_Array_TextSM_5000Ptr(ct_stacktrace, 84, 221, arr);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_clear_Array_SDL_Point_2000Ptr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_SDL_Point_2000* arr) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    arr->size = 0;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_clear_Array_PQNode_2000Ptr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_PQNode_2000* arr) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    arr->size = 0;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_push_Array_PQNode_2000Ptr_PQNodePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_PQNode_2000* arr, PQNode* value_ptr) {
    int capacity = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    capacity = 2000;
    if (arr->size > (capacity - 1)) {
        printf("%s %s %d %s %d\n", "push - array size is > than capacity - 1.", "size:", arr->size, "capacity:", capacity);
        ct_stacktrace_push(ct_stacktrace, 7, 36);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    arr->arr[arr->size] = *value_ptr;
    arr->size += 1;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_push_Array_SDL_Point_2000Ptr_SDL_PointPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_SDL_Point_2000* arr, SDL_Point* value_ptr) {
    int capacity = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    capacity = 2000;
    if (arr->size > (capacity - 1)) {
        printf("%s %s %d %s %d\n", "push - array size is > than capacity - 1.", "size:", arr->size, "capacity:", capacity);
        ct_stacktrace_push(ct_stacktrace, 7, 36);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    arr->arr[arr->size] = *value_ptr;
    arr->size += 1;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_reverse_Array_SDL_Point_2000Ptr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_SDL_Point_2000* arr) {
    SDL_Point temp = {0};
    int end = 0;
    int start = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    start = 0;
    end = (arr->size - 1);
    while (start < end) {
        if (start < 0 || start > arr->size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", start, arr->size);
            ct_stacktrace_push(ct_stacktrace, 100, 55);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        temp = arr->arr[start];
        if (start < 0 || start > arr->size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", start, arr->size);
            ct_stacktrace_push(ct_stacktrace, 100, 56);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        if (end < 0 || end > arr->size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", end, arr->size);
            ct_stacktrace_push(ct_stacktrace, 100, 56);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        arr->arr[start] = arr->arr[end];
        if (end < 0 || end > arr->size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", end, arr->size);
            ct_stacktrace_push(ct_stacktrace, 100, 57);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        arr->arr[end] = temp;
        start += 1;
        end -= 1;
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_push_value_Array_int_10Ptr_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_int_10* arr, int value) {
    int capacity = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    capacity = 10;
    if (arr->size > (capacity - 1)) {
        printf("%s %s %d %s %d\n", "push_value - array size is > than capacity - 1.", "size:", arr->size, "capacity:", capacity);
        ct_stacktrace_push(ct_stacktrace, 2, 45);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    arr->arr[arr->size] = value;
    arr->size += 1;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_push_Array_UIRenderable_300Ptr_UIRenderablePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_UIRenderable_300* arr, UIRenderable* value_ptr) {
    int capacity = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    capacity = 300;
    if (arr->size > (capacity - 1)) {
        printf("%s %s %d %s %d\n", "push - array size is > than capacity - 1.", "size:", arr->size, "capacity:", capacity);
        ct_stacktrace_push(ct_stacktrace, 7, 36);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    arr->arr[arr->size] = *value_ptr;
    arr->size += 1;
    ct_stacktrace_pop(ct_stacktrace);
}

