#ifndef GAME_PATH_FINDER
#define GAME_PATH_FINDER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "stbttf_sdl.h"
#include "utils.h"
#include "ct_array.h"

struct CT_StackTrace;
struct Game;
struct Map;
struct Unit;

typedef struct PQNode {
  SDL_Point p;
  int f;
} PQNode;

typedef struct Array_PQNode_2000 {
  PQNode arr[2000];
  int size;
  int capacity;
} Array_PQNode_2000;

typedef struct PathNode {
  SDL_Point p;
  int g;
  bool contains_key;
  Uint32 call_number;
} PathNode;

typedef struct Array_PathNode_640000 {
  PathNode arr[640000];
  int size;
  int capacity;
} Array_PathNode_640000;

typedef struct CameFrom {
  SDL_Point from_point;
  SDL_Point to_point;
  bool contains_key;
  Uint32 call_number;
} CameFrom;

typedef struct Array_CameFrom_640000 {
  CameFrom arr[640000];
  int size;
  int capacity;
} Array_CameFrom_640000;

typedef struct PathFinder {
  Array_SDL_Point_2000 path;
  Array_PQNode_2000 pq_arr;
  Array_PathNode_640000 g_arr;
  Array_CameFrom_640000 came_from;
  SDL_Point closest_point_to_target;
  int closest_dist_to_target;
  Uint32 call_number;
} PathFinder;

void void_mfunc_PathFinder_check_lookup_table_size_PathFinderPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, PathFinder* self, struct Game* game);
void void_mfunc_PathFinder_clear_prev_path_data_PathFinderPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, PathFinder* self);
void void_insert_point_Array_PathNode_640000Ptr_SDL_PointPtr_PathNodePtr_int_Uint32(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_PathNode_640000* arr, struct SDL_Point* point, PathNode* value, int rows, Uint32 call_number);
bool bool_arr_contains_key_Array_CameFrom_640000Ptr_SDL_PointPtr_int_Uint32(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_CameFrom_640000* arr, struct SDL_Point* point, int rows, Uint32 call_number);
bool bool_arr_contains_key_Array_PathNode_640000Ptr_SDL_PointPtr_int_Uint32(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_PathNode_640000* arr, struct SDL_Point* point, int rows, Uint32 call_number);
void void_pq_insertion_sort_Array_PQNode_2000Ptr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_PQNode_2000* pq_arr);
void void_insert_point_Array_CameFrom_640000Ptr_SDL_PointPtr_CameFromPtr_int_Uint32(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_CameFrom_640000* arr, struct SDL_Point* point, CameFrom* value, int rows, Uint32 call_number);
void void_mfunc_PathFinder_set_path_PathFinderPtr_GamePtr_MapPtr_UnitPtr_SDL_PointPtr_SDL_PointPtr_bool(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, PathFinder* self, struct Game* game, struct Map* map, struct Unit* acting_unit, struct SDL_Point* p1, struct SDL_Point* p2, bool check_unit_collissions);

#endif // GAME_PATH_FINDER
