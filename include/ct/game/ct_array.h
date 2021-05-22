#ifndef GAME_CT_ARRAY
#define GAME_CT_ARRAY

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "stbttf_sdl.h"

struct CT_StackTrace;
struct Tile;
struct Array_Tile_10000;
struct Array_Unit_3000;
struct Array_char_100;
struct Array_Map_100;
struct Array_int_100;
struct Array_int_300;
struct Array_TweenXY_20000;
struct Array_Guild_100;
struct Array_int_30;
struct PQNode;
struct Array_SDL_Point_2000;
struct Array_PQNode_2000;
struct Game;
struct Array_TextSM_5000;
struct Array_char_200;
struct Array_Building_2000;
struct SpriteSrcs;
struct Array_SpriteSrcs_200;
struct Array_SharedItem_5000;
struct Array_SharedItem_5;
struct SharedItem;
struct Array_SharedAbility_5000;
struct Array_SharedAbility_10;
struct Array_SharedAbility_30;
struct SharedAbility;
struct Array_UIRenderable_300;
struct UIRenderable;
struct Array_WarpPoint_7;
struct WarpPoint;

typedef struct Array_int_10 {
  int arr[10];
  int size;
  int capacity;
} Array_int_10;

typedef struct Array_SDL_Point_4 {
  SDL_Point arr[4];
  int size;
  int capacity;
} Array_SDL_Point_4;

typedef struct Array_SDL_Rect_10 {
  SDL_Rect arr[10];
  int size;
  int capacity;
} Array_SDL_Rect_10;

typedef struct Array_bool_322 {
  bool arr[322];
  int size;
  int capacity;
} Array_bool_322;

typedef struct Array_SDL_Point_2000 {
  SDL_Point arr[2000];
  int size;
  int capacity;
} Array_SDL_Point_2000;

typedef struct Array_int_300 {
  int arr[300];
  int size;
  int capacity;
} Array_int_300;

typedef struct Array_int_100 {
  int arr[100];
  int size;
  int capacity;
} Array_int_100;

typedef struct Array_char_200 {
  char arr[200];
  int size;
  int capacity;
} Array_char_200;

typedef struct Array_char_21 {
  char arr[21];
  int size;
  int capacity;
} Array_char_21;

typedef struct Array_SDL_Rect_3 {
  SDL_Rect arr[3];
  int size;
  int capacity;
} Array_SDL_Rect_3;

typedef struct Array_int_30 {
  int arr[30];
  int size;
  int capacity;
} Array_int_30;

typedef struct Array_char_100 {
  char arr[100];
  int size;
  int capacity;
} Array_char_100;

void void_push_value_Array_bool_322Ptr_bool(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_bool_322* arr, bool value);
struct SpriteSrcs* SpriteSrcsPtr_next_Array_SpriteSrcs_200Ptr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_SpriteSrcs_200* arr);
void void_push_Array_SDL_Rect_10Ptr_SDL_RectPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_SDL_Rect_10* arr, struct SDL_Rect* value_ptr);
void void_clear_Array_SDL_Rect_10Ptr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_SDL_Rect_10* arr);
void void_string_set_literal_Array_char_200Ptr_charPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_char_200* arr, char* string_literal);
void void_clear_Array_SharedAbility_10Ptr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_SharedAbility_10* arr);
void void_clear_Array_SharedAbility_30Ptr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_SharedAbility_30* arr);
void void_clear_Array_SharedItem_5Ptr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_SharedItem_5* arr);
void void_clear_Array_SDL_Rect_3Ptr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_SDL_Rect_3* arr);
void void_push_Array_SDL_Rect_3Ptr_SDL_RectPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_SDL_Rect_3* arr, struct SDL_Rect* value_ptr);
void void_string_set_literal_Array_char_100Ptr_charPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_char_100* arr, char* string_literal);
struct SharedAbility* SharedAbilityPtr_next_Array_SharedAbility_10Ptr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_SharedAbility_10* arr);
struct SharedAbility* SharedAbilityPtr_next_Array_SharedAbility_30Ptr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_SharedAbility_30* arr);
void void_push_Array_SharedItem_5Ptr_SharedItemPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_SharedItem_5* arr, struct SharedItem* value_ptr);
void void_string_set_Array_char_200Ptr_Array_char_100Ptr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_char_200* arr1, struct Array_char_100* arr2);
void void_pool_init_GamePtr_Array_Map_100Ptr_intPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Game* game, struct Array_Map_100* arr, int* last_in_use_handle_ptr);
void void_pool_init_GamePtr_Array_Building_2000Ptr_intPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Game* game, struct Array_Building_2000* arr, int* last_in_use_handle_ptr);
void void_pool_init_GamePtr_Array_Unit_3000Ptr_intPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Game* game, struct Array_Unit_3000* arr, int* last_in_use_handle_ptr);
void void_pool_init_GamePtr_Array_Guild_100Ptr_intPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Game* game, struct Array_Guild_100* arr, int* last_in_use_handle_ptr);
void void_pool_init_GamePtr_Array_SharedItem_5000Ptr_intPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Game* game, struct Array_SharedItem_5000* arr, int* last_in_use_handle_ptr);
void void_pool_init_GamePtr_Array_SharedAbility_5000Ptr_intPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Game* game, struct Array_SharedAbility_5000* arr, int* last_in_use_handle_ptr);
void void_pool_of_text_init_GamePtr_Array_TextSM_5000Ptr_intPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Game* game, struct Array_TextSM_5000* arr, int* last_in_use_handle_ptr);
void void_pool_init_GamePtr_Array_TweenXY_20000Ptr_intPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Game* game, struct Array_TweenXY_20000* arr, int* last_in_use_handle_ptr);
int int_pool_get_handle_Array_Map_100Ptr_intPtr_charPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_Map_100* arr, int* last_in_use_handle_ptr, char* debug_pool_name_char_ptr);
int int_pool_get_handle_Array_Building_2000Ptr_intPtr_charPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_Building_2000* arr, int* last_in_use_handle_ptr, char* debug_pool_name_char_ptr);
int int_pool_get_handle_Array_Unit_3000Ptr_intPtr_charPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_Unit_3000* arr, int* last_in_use_handle_ptr, char* debug_pool_name_char_ptr);
int int_pool_get_handle_Array_Guild_100Ptr_intPtr_charPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_Guild_100* arr, int* last_in_use_handle_ptr, char* debug_pool_name_char_ptr);
int int_pool_get_handle_Array_SharedItem_5000Ptr_intPtr_charPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_SharedItem_5000* arr, int* last_in_use_handle_ptr, char* debug_pool_name_char_ptr);
int int_pool_get_handle_Array_SharedAbility_5000Ptr_intPtr_charPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_SharedAbility_5000* arr, int* last_in_use_handle_ptr, char* debug_pool_name_char_ptr);
int int_pool_get_handle_Array_TweenXY_20000Ptr_intPtr_charPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_TweenXY_20000* arr, int* last_in_use_handle_ptr, char* debug_pool_name_char_ptr);
int int_pool_get_handle_Array_TextSM_5000Ptr_intPtr_charPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_TextSM_5000* arr, int* last_in_use_handle_ptr, char* debug_pool_name_char_ptr);
void void_push_Array_Tile_10000Ptr_TilePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_Tile_10000* arr, struct Tile* value_ptr);
void void_push_Array_WarpPoint_7Ptr_WarpPointPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_WarpPoint_7* arr, struct WarpPoint* value_ptr);
void void_remove_at_Array_int_300Ptr_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_int_300* arr, int idx);
void void_find_and_remove_handle_Array_int_300Ptr_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_int_300* arr, int handle_to_remove);
void void_push_value_Array_int_300Ptr_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_int_300* arr, int value);
void void_push_value_Array_int_100Ptr_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_int_100* arr, int value);
void void_push_value_Array_int_30Ptr_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_int_30* arr, int value);
void void_string_cat_Array_char_100Ptr_Array_char_100Ptr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_char_100* arr1, struct Array_char_100* arr2);
void void_string_cat_literal_Array_char_100Ptr_charPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_char_100* arr, char* string_literal);
void void_clear_Array_UIRenderable_300Ptr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_UIRenderable_300* arr);
int int_pool_get_last_in_use_handle_Array_Map_100Ptr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_Map_100* arr);
void void_pool_release_handle_Array_Map_100Ptr_int_intPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_Map_100* arr, int handle, int* last_in_use_handle_ptr);
int int_pool_get_last_in_use_handle_Array_Building_2000Ptr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_Building_2000* arr);
void void_pool_release_handle_Array_Building_2000Ptr_int_intPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_Building_2000* arr, int handle, int* last_in_use_handle_ptr);
int int_pool_get_last_in_use_handle_Array_Unit_3000Ptr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_Unit_3000* arr);
void void_pool_release_handle_Array_Unit_3000Ptr_int_intPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_Unit_3000* arr, int handle, int* last_in_use_handle_ptr);
int int_pool_get_last_in_use_handle_Array_Guild_100Ptr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_Guild_100* arr);
void void_pool_release_handle_Array_Guild_100Ptr_int_intPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_Guild_100* arr, int handle, int* last_in_use_handle_ptr);
int int_pool_get_last_in_use_handle_Array_SharedItem_5000Ptr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_SharedItem_5000* arr);
void void_pool_release_handle_Array_SharedItem_5000Ptr_int_intPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_SharedItem_5000* arr, int handle, int* last_in_use_handle_ptr);
int int_pool_get_last_in_use_handle_Array_SharedAbility_5000Ptr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_SharedAbility_5000* arr);
void void_pool_release_handle_Array_SharedAbility_5000Ptr_int_intPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_SharedAbility_5000* arr, int handle, int* last_in_use_handle_ptr);
int int_pool_get_last_in_use_handle_Array_TweenXY_20000Ptr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_TweenXY_20000* arr);
void void_pool_release_handle_Array_TweenXY_20000Ptr_int_intPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_TweenXY_20000* arr, int handle, int* last_in_use_handle_ptr);
int int_pool_get_last_in_use_handle_Array_TextSM_5000Ptr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_TextSM_5000* arr);
void void_pool_release_handle_Array_TextSM_5000Ptr_int_intPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_TextSM_5000* arr, int handle, int* last_in_use_handle_ptr);
void void_clear_Array_SDL_Point_2000Ptr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_SDL_Point_2000* arr);
void void_clear_Array_PQNode_2000Ptr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_PQNode_2000* arr);
void void_push_Array_PQNode_2000Ptr_PQNodePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_PQNode_2000* arr, struct PQNode* value_ptr);
void void_push_Array_SDL_Point_2000Ptr_SDL_PointPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_SDL_Point_2000* arr, struct SDL_Point* value_ptr);
void void_reverse_Array_SDL_Point_2000Ptr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_SDL_Point_2000* arr);
void void_push_value_Array_int_10Ptr_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_int_10* arr, int value);
void void_push_Array_UIRenderable_300Ptr_UIRenderablePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, struct Array_UIRenderable_300* arr, struct UIRenderable* value_ptr);

#endif // GAME_CT_ARRAY
