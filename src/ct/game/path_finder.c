#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "ct_stacktrace.h"
#include "path_finder.h"
#include "utils.h"
#include "ct_array.h"
#include "game.h"
#include "map.h"
#include "unit.h"

void void_mfunc_PathFinder_check_lookup_table_size_PathFinderPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, PathFinder* self, Game* game) {
    int came_from_capacity = 0;
    int map_max_capacity = 0;
    int map_col_ratio = 0;
    int map_row_ratio = 0;
    int g_arr_capacity = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    map_row_ratio = (game->max_map_size.x * game->move_grid_ratio);
    map_col_ratio = (game->max_map_size.y * game->move_grid_ratio);
    map_max_capacity = (map_row_ratio * map_col_ratio);
    g_arr_capacity = 640000;
    came_from_capacity = 640000;
    if ((g_arr_capacity < map_max_capacity || came_from_capacity < map_max_capacity)) {
        printf("%s %d %s %d %s %d\n", "PathFinder.check_lookup_table_size - path_finder g_arr capacity or came_from capacity is not large enough for the max size map.\nMax map size:", map_max_capacity, "\ng_arr capacity:", g_arr_capacity, "\ncame_from capacity:", came_from_capacity);
        ct_stacktrace_push(ct_stacktrace, 1, 46);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_PathFinder_clear_prev_path_data_PathFinderPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, PathFinder* self) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    void_clear_Array_SDL_Point_2000Ptr(ct_stacktrace, 95, 50, &self->path);
    void_clear_Array_PQNode_2000Ptr(ct_stacktrace, 95, 51, &self->pq_arr);
    self->g_arr.size = 640000;
    self->came_from.size = 640000;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_insert_point_Array_PathNode_640000Ptr_SDL_PointPtr_PathNodePtr_int_Uint32(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_PathNode_640000* arr, SDL_Point* point, PathNode* value, int rows, Uint32 call_number) {
    int idx = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    idx = int_get_1d_from_2d_idx_SDL_PointPtr_int(ct_stacktrace, 98, 201, point, rows);
    value->contains_key = true;
    value->call_number = call_number;
    if (idx < 0 || idx > arr->size - 1) {
        printf("Out of bounds error: idx: %d size: %d.\n", idx, arr->size);
        ct_stacktrace_push(ct_stacktrace, 98, 205);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
    }
    arr->arr[idx] = *value;
    ct_stacktrace_pop(ct_stacktrace);
}

bool bool_arr_contains_key_Array_CameFrom_640000Ptr_SDL_PointPtr_int_Uint32(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_CameFrom_640000* arr, SDL_Point* point, int rows, Uint32 call_number) {
    CameFrom* v = NULL;
    int idx = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    idx = int_get_1d_from_2d_idx_SDL_PointPtr_int(ct_stacktrace, 99, 209, point, rows);
    if (idx < 0 || idx > arr->size - 1) {
        printf("Out of bounds error: idx: %d size: %d.\n", idx, arr->size);
        ct_stacktrace_push(ct_stacktrace, 99, 210);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
    }
    v = &arr->arr[idx];
    if (v->call_number != call_number) {
                ct_stacktrace_pop(ct_stacktrace);
return false;
}
        ct_stacktrace_pop(ct_stacktrace);
return v->contains_key;
}

bool bool_arr_contains_key_Array_PathNode_640000Ptr_SDL_PointPtr_int_Uint32(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_PathNode_640000* arr, SDL_Point* point, int rows, Uint32 call_number) {
    PathNode* v = NULL;
    int idx = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    idx = int_get_1d_from_2d_idx_SDL_PointPtr_int(ct_stacktrace, 99, 209, point, rows);
    if (idx < 0 || idx > arr->size - 1) {
        printf("Out of bounds error: idx: %d size: %d.\n", idx, arr->size);
        ct_stacktrace_push(ct_stacktrace, 99, 210);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
    }
    v = &arr->arr[idx];
    if (v->call_number != call_number) {
                ct_stacktrace_pop(ct_stacktrace);
return false;
}
        ct_stacktrace_pop(ct_stacktrace);
return v->contains_key;
}

void void_pq_insertion_sort_Array_PQNode_2000Ptr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_PQNode_2000* pq_arr) {
    int next_idx = 0;
    int i = 0;
    PQNode key = {0};
    PQNode key_j = {0};
    int j = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    for (i = 1; i < pq_arr->size; i += 1) {
        if (i < 0 || i > pq_arr->size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", i, pq_arr->size);
            ct_stacktrace_push(ct_stacktrace, 101, 234);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        key = pq_arr->arr[i];
        j = (i - 1);
        if (j < 0 || j > pq_arr->size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", j, pq_arr->size);
            ct_stacktrace_push(ct_stacktrace, 101, 236);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        key_j = pq_arr->arr[j];
        while ((j >= 0 && key_j.f < key.f)) {
            next_idx = (j + 1);
            if (next_idx < 0 || next_idx > pq_arr->size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", next_idx, pq_arr->size);
                ct_stacktrace_push(ct_stacktrace, 101, 242);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            if (j < 0 || j > pq_arr->size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", j, pq_arr->size);
                ct_stacktrace_push(ct_stacktrace, 101, 242);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            pq_arr->arr[next_idx] = pq_arr->arr[j];
            j -= 1;
            if (j >= 0) {
                if (j < 0 || j > pq_arr->size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", j, pq_arr->size);
                    ct_stacktrace_push(ct_stacktrace, 101, 246);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                key_j = pq_arr->arr[j];
    }
}
        next_idx = (j + 1);
        if (next_idx < 0 || next_idx > pq_arr->size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", next_idx, pq_arr->size);
            ct_stacktrace_push(ct_stacktrace, 101, 249);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
        pq_arr->arr[next_idx] = key;
    }
    ct_stacktrace_pop(ct_stacktrace);
}

void void_insert_point_Array_CameFrom_640000Ptr_SDL_PointPtr_CameFromPtr_int_Uint32(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Array_CameFrom_640000* arr, SDL_Point* point, CameFrom* value, int rows, Uint32 call_number) {
    int idx = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    idx = int_get_1d_from_2d_idx_SDL_PointPtr_int(ct_stacktrace, 98, 201, point, rows);
    value->contains_key = true;
    value->call_number = call_number;
    if (idx < 0 || idx > arr->size - 1) {
        printf("Out of bounds error: idx: %d size: %d.\n", idx, arr->size);
        ct_stacktrace_push(ct_stacktrace, 98, 205);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
    }
    arr->arr[idx] = *value;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_mfunc_PathFinder_set_path_PathFinderPtr_GamePtr_MapPtr_UnitPtr_SDL_PointPtr_SDL_PointPtr_bool(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, PathFinder* self, Game* game, Map* map, Unit* acting_unit, SDL_Point* p1, SDL_Point* p2, bool check_unit_collissions) {
    int neighbor_g = 0;
    int new_g_cost = 0;
    SDL_Point* n3 = NULL;
    SDL_Point* n2 = NULL;
    PathNode* g_node = NULL;
    SDL_Point* n1 = NULL;
    CameFrom* came_from_ptr = NULL;
    int came_from_handle = 0;
    PQNode current = {0};
    SDL_Point start = {0};
    SDL_Rect tile_point_hit_box_cpy = {0};
    int g_handle = 0;
    SDL_Point target = {0};
    int f = 0;
    int reconstruct_path_iters = 0;
    bool neighbor_g_contains_handle = false;
    SDL_Point* n0 = NULL;
    SDL_Point* n = NULL;
    int dist = 0;
    PathNode path_node = {0};
    int pq_last_idx = 0;
    int i = 0;
    int max_iters = 0;
    PathNode* neighbor_g_node = NULL;
    int iters = 0;
    Array_SDL_Point_4 neighbors = {0};
    PQNode pq_node = {0};
    CameFrom came_from = {0};
    int neighbor_g_handle = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->call_number += 1;
    if (self->call_number == 0) {
        memset(&self->g_arr, 0, sizeof(Array_PathNode_640000) * 1);
        memset(&self->came_from, 0, sizeof(Array_CameFrom_640000) * 1);
        self->g_arr.size = 640000;
        self->came_from.size = 640000;
        self->call_number = 1;
}
    void_mfunc_PathFinder_clear_prev_path_data_PathFinderPtr(ct_stacktrace, 102, 76, self);
    start = *p1;
    target = *p2;
    self->closest_point_to_target = start;
    self->closest_dist_to_target = int_manhattan_distance_SDL_PointPtr_SDL_PointPtr(ct_stacktrace, 102, 82, &start, &target);
    tile_point_hit_box_cpy = acting_unit->tile_point_hit_box;
    if (!(bool_mfunc_Map_in_bounds_move_grid_MapPtr_SDL_PointPtr(ct_stacktrace, 102, 85, map, &target))) {
        printf("%s\n", "PathFinder.set path - target_point is not in bounds.");
        ct_stacktrace_push(ct_stacktrace, 102, 87);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    if (bool_points_are_equal_SDL_PointPtr_SDL_PointPtr(ct_stacktrace, 102, 88, &start, &target)) {
        printf("%s\n", "Pathfinder.set_path - start and target points are equal.");
                ct_stacktrace_pop(ct_stacktrace);
return;
}
    iters = 0;
    reconstruct_path_iters = 0;
    max_iters = 2000;
    if (max_iters > 2000) {
        printf("%s\n", "PathFinder.set_path max_iters must be <= path capacity");
        ct_stacktrace_push(ct_stacktrace, 102, 101);
        ct_stacktrace_print(ct_stacktrace);
        exit(1);
}
    neighbors.size = 4;
    path_node.p = start;
    path_node.g = 0;
    void_insert_point_Array_PathNode_640000Ptr_SDL_PointPtr_PathNodePtr_int_Uint32(ct_stacktrace, 102, 109, &self->g_arr, &path_node.p, &path_node, map->rows, self->call_number);
    pq_node.p = start;
    pq_node.f = int_manhattan_distance_SDL_PointPtr_SDL_PointPtr(ct_stacktrace, 102, 112, &start, &target);
    void_push_Array_PQNode_2000Ptr_PQNodePtr(ct_stacktrace, 102, 113, &self->pq_arr, &pq_node);
    while ((iters < max_iters && self->pq_arr.size > 0)) {
        iters += 1;
        pq_last_idx = (self->pq_arr.size - 1);
        if (pq_last_idx < 0 || pq_last_idx > self->pq_arr.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", pq_last_idx, self->pq_arr.size);
                ct_stacktrace_push(ct_stacktrace, 102, 124);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            current = self->pq_arr.arr[pq_last_idx];
        self->pq_arr.size -= 1;
        if (bool_points_are_equal_SDL_PointPtr_SDL_PointPtr(ct_stacktrace, 102, 127, &current.p, &target)) {
            void_push_Array_SDL_Point_2000Ptr_SDL_PointPtr(ct_stacktrace, 102, 129, &self->path, &target);
            while (bool_arr_contains_key_Array_CameFrom_640000Ptr_SDL_PointPtr_int_Uint32(ct_stacktrace, 102, 130, &self->came_from, &current.p, map->rows, self->call_number)) {
                reconstruct_path_iters += 1;
                if (reconstruct_path_iters > max_iters) {
                    printf("%s\n", "PathFinder.set_path - reconstruct_path iters > max_iters.");
                    ct_stacktrace_push(ct_stacktrace, 102, 134);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
}
                came_from_handle = int_get_1d_from_2d_idx_SDL_PointPtr_int(ct_stacktrace, 102, 135, &current.p, map->rows);
                if (came_from_handle < 0 || came_from_handle > self->came_from.size - 1) {
                        printf("Out of bounds error: idx: %d size: %d.\n", came_from_handle, self->came_from.size);
                        ct_stacktrace_push(ct_stacktrace, 102, 136);
                        ct_stacktrace_print(ct_stacktrace);
                        exit(1);
                    }
                    came_from_ptr = &self->came_from.arr[came_from_handle];
                current.p = came_from_ptr->to_point;
                if (!(bool_points_are_equal_SDL_PointPtr_SDL_PointPtr(ct_stacktrace, 102, 138, &current.p, &start))) {
                    void_push_Array_SDL_Point_2000Ptr_SDL_PointPtr(ct_stacktrace, 102, 139, &self->path, &current.p);
    }
}
            void_reverse_Array_SDL_Point_2000Ptr(ct_stacktrace, 102, 142, &self->path);
                        ct_stacktrace_pop(ct_stacktrace);
return;
}
        if (0 < 0 || 0 > neighbors.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", 0, neighbors.size);
                ct_stacktrace_push(ct_stacktrace, 102, 145);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            n0 = &neighbors.arr[0];
        if (1 < 0 || 1 > neighbors.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", 1, neighbors.size);
                ct_stacktrace_push(ct_stacktrace, 102, 146);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            n1 = &neighbors.arr[1];
        if (2 < 0 || 2 > neighbors.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", 2, neighbors.size);
                ct_stacktrace_push(ct_stacktrace, 102, 147);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            n2 = &neighbors.arr[2];
        if (3 < 0 || 3 > neighbors.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", 3, neighbors.size);
                ct_stacktrace_push(ct_stacktrace, 102, 148);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            n3 = &neighbors.arr[3];
        n0->x = (current.p.x + 1);
        n0->y = current.p.y;
        n1->x = (current.p.x - 1);
        n1->y = current.p.y;
        n2->x = current.p.x;
        n2->y = (current.p.y + 1);
        n3->x = current.p.x;
        n3->y = (current.p.y - 1);
        for (i = 0; i < neighbors.size; i++) {
            n = &neighbors.arr[i];
            if (!(bool_mfunc_Map_in_bounds_move_grid_MapPtr_SDL_PointPtr(ct_stacktrace, 102, 159, map, n))) {
                continue;
}
            tile_point_hit_box_cpy.x = n->x;
            tile_point_hit_box_cpy.y = n->y;
            if ((check_unit_collissions && bool_mfunc_Map_unit_occupies_tile_point_move_grid_MapPtr_GamePtr_SDL_RectPtr_int(ct_stacktrace, 102, 163, map, game, &tile_point_hit_box_cpy, acting_unit->handle))) {
                continue;
}
            g_handle = int_get_1d_from_2d_idx_SDL_PointPtr_int(ct_stacktrace, 102, 165, &current.p, map->rows);
            if (g_handle < 0 || g_handle > self->g_arr.size - 1) {
                    printf("Out of bounds error: idx: %d size: %d.\n", g_handle, self->g_arr.size);
                    ct_stacktrace_push(ct_stacktrace, 102, 166);
                    ct_stacktrace_print(ct_stacktrace);
                    exit(1);
                }
                g_node = &self->g_arr.arr[g_handle];
            new_g_cost = (g_node->g + 1);
            neighbor_g_contains_handle = bool_arr_contains_key_Array_PathNode_640000Ptr_SDL_PointPtr_int_Uint32(ct_stacktrace, 102, 168, &self->g_arr, n, map->rows, self->call_number);
            neighbor_g_handle = int_get_1d_from_2d_idx_SDL_PointPtr_int(ct_stacktrace, 102, 169, n, map->rows);
            neighbor_g = -1;
            if (neighbor_g_contains_handle) {
                if (neighbor_g_handle < 0 || neighbor_g_handle > self->g_arr.size - 1) {
                        printf("Out of bounds error: idx: %d size: %d.\n", neighbor_g_handle, self->g_arr.size);
                        ct_stacktrace_push(ct_stacktrace, 102, 172);
                        ct_stacktrace_print(ct_stacktrace);
                        exit(1);
                    }
                    neighbor_g_node = &self->g_arr.arr[neighbor_g_handle];
                neighbor_g = neighbor_g_node->g;
}
            if ((!(neighbor_g_contains_handle) || new_g_cost < neighbor_g)) {
                f = int_manhattan_distance_SDL_PointPtr_SDL_PointPtr(ct_stacktrace, 102, 175, n, &target);
                path_node.g = new_g_cost;
                path_node.p = *n;
                void_insert_point_Array_PathNode_640000Ptr_SDL_PointPtr_PathNodePtr_int_Uint32(ct_stacktrace, 102, 180, &self->g_arr, &path_node.p, &path_node, map->rows, self->call_number);
                pq_node.f = f;
                pq_node.p = *n;
                void_push_Array_PQNode_2000Ptr_PQNodePtr(ct_stacktrace, 102, 185, &self->pq_arr, &pq_node);
                void_pq_insertion_sort_Array_PQNode_2000Ptr(ct_stacktrace, 102, 186, &self->pq_arr);
                came_from.from_point = *n;
                came_from.to_point = current.p;
                void_insert_point_Array_CameFrom_640000Ptr_SDL_PointPtr_CameFromPtr_int_Uint32(ct_stacktrace, 102, 191, &self->came_from, n, &came_from, map->rows, self->call_number);
                dist = int_manhattan_distance_SDL_PointPtr_SDL_PointPtr(ct_stacktrace, 102, 194, &current.p, &target);
                if ((dist > 0 && dist < self->closest_dist_to_target)) {
                    self->closest_dist_to_target = dist;
                    self->closest_point_to_target = current.p;
                }
            }
        }
    }
    ct_stacktrace_pop(ct_stacktrace);
}

