from ct.src.utils import SDL_Rect, SDL_Point, create_point, get_1d_from_2d_idx, manhattan_distance, points_are_equal
from ct.src.base_types import Array, array_capacity, char, deref, memset, addr, Uint32
from ct.src.ct_array import Array
# weak imports
from ct.src.game import Game
from ct.src.map import Map
from ct.src.unit import Unit


class PQNode:
    def __init__(self):
        self.p: SDL_Point = None
        self.f: int = None


class PathNode:
    def __init__(self):
        self.p: SDL_Point = None
        self.g: int = None
        self.contains_key: bool = None
        self.call_number: Uint32 = None


class CameFrom:
    def __init__(self):
        self.from_point: SDL_Point = None
        self.to_point: SDL_Point = None
        self.contains_key: bool = None
        self.call_number: Uint32 = None


class PathFinder:
    def __init__(self):
        self.path: Array[SDL_Point] = Array[SDL_Point](2000)
        self.pq_arr: Array[PQNode] = Array[PQNode](2000)
        self.g_arr: Array[PathNode] = Array[PathNode](640000)
        self.came_from: Array[CameFrom] = Array[CameFrom](640000)
        self.closest_point_to_target: SDL_Point = None
        self.closest_dist_to_target: int = None
        self.call_number: Uint32 = None

    def check_lookup_table_size(self, game: Game):
        # check to see if the pathfinder capacity on the lookup tables is large
        #  enough for the max map. path and pq_arr are not lookup tables, just regular arrays.
        map_row_ratio = game.max_map_size.x * game.move_grid_ratio
        map_col_ratio = game.max_map_size.y * game.move_grid_ratio
        map_max_capacity = map_row_ratio * map_col_ratio
        g_arr_capacity = array_capacity(self.g_arr)
        came_from_capacity = array_capacity(self.came_from)
        if g_arr_capacity < map_max_capacity or came_from_capacity < map_max_capacity:
            print(
                "PathFinder.check_lookup_table_size - path_finder g_arr capacity or came_from capacity is not large enough for the max size map.\nMax map size:", map_max_capacity, "\ng_arr capacity:", g_arr_capacity, "\ncame_from capacity:", came_from_capacity)
            exit(1)

    def clear_prev_path_data(self):
        # these work like traditional arrays
        self.path.clear()
        self.pq_arr.clear()
        # added call number to each cell in the lookup table so that when contain key is called
        # it checks the call number of the cell, even if contains_key prop is true, if the call number
        # is not the same as the current call number it knows its from a different call. set sets
        # the call number. Because of this memset is not needed.
        self.g_arr.size = array_capacity(self.g_arr)
        self.came_from.size = array_capacity(self.came_from)

    def set_path(self, game: Game, map: Map, acting_unit: Unit, p1: SDL_Point, p2: SDL_Point, check_unit_collissions: bool):
        # inc call number, doens't matter if it overflows just needs to be unique for each call
        self.call_number += 1
        # if the call number if 0 it means it overflowed, clear the tables so that previous
        # call numbers won't be treated as valid. Imagine call number 5 is set in a cell from the
        # previous 0 - MAX_SIZE iteration, if the current call number is 5 it will treat it as valid,
        # even though it is from the previous 0 - MAX_SIZE iteration
        if self.call_number == 0:
            memset(addr(self.g_arr), 0, 1)
            memset(addr(self.came_from), 0, 1)
            # reset size as it was just zero'd out
            self.g_arr.size = array_capacity(self.g_arr)
            self.came_from.size = array_capacity(self.came_from)
            # finally inc call number to 1 so that 0 call number values from memset are not
            # treated as valid from this call number (that would mean every cell was valid)
            self.call_number = 1
        # clear previous path data
        self.clear_prev_path_data()
        # make copies of p1 and p2 because there was a weird mutation bug
        start = deref(p1)
        target = deref(p2)
        # closest point to target - is only valid if find_closest_target param is true
        self.closest_point_to_target = start
        self.closest_dist_to_target = manhattan_distance(start, target)
        tile_point_hit_box_cpy = acting_unit.tile_point_hit_box

        if not(map.in_bounds_move_grid(target)):
            print("PathFinder.set path - target_point is not in bounds.")
            exit(1)
        if points_are_equal(start, target):
            print("Pathfinder.set_path - start and target points are equal.")
            return

        iters = 0
        reconstruct_path_iters = 0
        # max iters for now is the path capacity, though iters can be greater than
        # the number of tiles in the map if it gets stuck and needs go around obstacles.
        # a good starting point though, change later if people struggle to find paths.
        max_iters = array_capacity(self.path)
        # not sure if this is true but keeping it for now
        if max_iters > array_capacity(self.path):
            print("PathFinder.set_path max_iters must be <= path capacity")
            exit(1)
        neighbors = Array[SDL_Point](4)
        # set size directly because it will be manipulated with random access below
        neighbors.size = 4
        path_node = PathNode()
        path_node.p = start
        path_node.g = 0
        # self.g_arr.push(path_node)
        insert_point(self.g_arr, path_node.p, path_node,
                     map.rows, self.call_number)
        pq_node = PQNode()
        pq_node.p = start
        pq_node.f = manhattan_distance(start, target)
        self.pq_arr.push(pq_node)
        came_from = CameFrom()

        # don't exit if iters fails, it just means a path couldn't be found.
        # it is not likely an error condition (althought it could be)
        while iters < max_iters and self.pq_arr.size > 0:
            iters += 1

            # pop last idx from pq_arr. It is sorted so it is the
            # node with the min f value.
            pq_last_idx = self.pq_arr.size - 1
            current = self.pq_arr[pq_last_idx]
            self.pq_arr.size -= 1

            if points_are_equal(current.p, target):
                # print("Found target in", iters, "iters")
                self.path.push(target)
                while arr_contains_key(self.came_from, current.p, map.rows, self.call_number):
                    reconstruct_path_iters += 1
                    if reconstruct_path_iters > max_iters:
                        print(
                            "PathFinder.set_path - reconstruct_path iters > max_iters.")
                        exit(1)
                    came_from_handle = get_1d_from_2d_idx(current.p, map.rows)
                    came_from_ptr = self.came_from.at(came_from_handle)
                    current.p = came_from_ptr.to_point
                    if not(points_are_equal(current.p, start)):
                        self.path.push(current.p)

                # reverse the array as it is currently backwards
                self.path.reverse()
                return

            n0 = neighbors.at(0)
            n1 = neighbors.at(1)
            n2 = neighbors.at(2)
            n3 = neighbors.at(3)
            n0.x = current.p.x + 1
            n0.y = current.p.y
            n1.x = current.p.x - 1
            n1.y = current.p.y
            n2.x = current.p.x
            n2.y = current.p.y + 1
            n3.x = current.p.x
            n3.y = current.p.y - 1

            for n in neighbors:
                if not(map.in_bounds_move_grid(n)):
                    continue
                tile_point_hit_box_cpy.x = n.x
                tile_point_hit_box_cpy.y = n.y
                if check_unit_collissions and map.unit_occupies_tile_point_move_grid(game, tile_point_hit_box_cpy, acting_unit.handle):
                    continue
                g_handle = get_1d_from_2d_idx(current.p, map.rows)
                g_node = self.g_arr.at(g_handle)
                new_g_cost = g_node.g + 1
                neighbor_g_contains_handle = arr_contains_key(
                    self.g_arr, n, map.rows, self.call_number)
                neighbor_g_handle = get_1d_from_2d_idx(n, map.rows)
                neighbor_g = -1
                if neighbor_g_contains_handle:
                    neighbor_g_node = self.g_arr.at(neighbor_g_handle)
                    neighbor_g = neighbor_g_node.g
                if not(neighbor_g_contains_handle) or new_g_cost < neighbor_g:
                    f = manhattan_distance(n, target)

                    # update or push g_arr for the neighbor
                    path_node.g = new_g_cost
                    path_node.p = deref(n)
                    insert_point(self.g_arr, path_node.p,
                                 path_node, map.rows, self.call_number)

                    # push pq node and sort the pq
                    pq_node.f = f
                    pq_node.p = deref(n)
                    self.pq_arr.push(pq_node)
                    pq_insertion_sort(self.pq_arr)

                    # update or push a new came from to came from arr
                    came_from.from_point = deref(n)
                    came_from.to_point = current.p
                    insert_point(self.came_from, n, came_from,
                                 map.rows, self.call_number)

                    # possibly update closest point to target
                    dist = manhattan_distance(current.p, target)
                    if dist > 0 and dist < self.closest_dist_to_target:
                        self.closest_dist_to_target = dist
                        self.closest_point_to_target = current.p


def insert_point(arr, point: SDL_Point, value, rows: int, call_number: Uint32):
    idx = get_1d_from_2d_idx(point, rows)
    value.contains_key = True
    # set call number to this call so that contains key will treat the cell as valid
    value.call_number = call_number
    arr[idx] = deref(value)


def arr_contains_key(arr, point: SDL_Point, rows: int, call_number: Uint32) -> bool:
    idx = get_1d_from_2d_idx(point, rows)
    v = arr.at(idx)
    # if this was set in a different call then it isn't from this path.set call
    # return false.
    if v.call_number != call_number:
        return False
    return v.contains_key


def find_handle_of_point_in_came_from(came_from, target_point: SDL_Point) -> int:
    for i, p in enumerate(came_from):
        if points_are_equal(p.from_point, target_point):
            return i
    return -1


def find_handle_of_point(arr, target_point: SDL_Point) -> int:
    for i, p in enumerate(arr):
        if points_are_equal(p.p, target_point):
            return i
    return -1


def pq_insertion_sort(pq_arr):
    for i in range(1, pq_arr.size, 1):
        key = pq_arr[i]
        j = i - 1
        key_j = pq_arr[j]
        # Move elements of arr[0..i-1], that are
        # greater than key, to one position ahead
        # of their current position
        while j >= 0 and key_j.f < key.f:
            next_idx = j + 1
            pq_arr[next_idx] = pq_arr[j]
            j -= 1
            # check if j is a valid index, i.e >= 0 as it can be less than 0 here.
            if j >= 0:
                key_j = pq_arr[j]

        next_idx = j + 1
        pq_arr[next_idx] = key
