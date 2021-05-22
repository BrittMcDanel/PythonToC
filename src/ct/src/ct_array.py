from ct.src.base_types import Array, array_capacity, array_get_buffer, addr, deref, set, macro, strlen, strcpy, strcat
from typing import TypeVar
# weak imports
from ct.src.tile import Tile
from ct.src.unit import Unit
from ct.src.map import Map
from ct.src.tween import TweenXY
from ct.src.guild import Guild
from ct.src.path_finder import PathFinder
from ct.src.game import Game
from ct.src.ability import Ability
from ct.src.text import TextSM, TextLG
from ct.src.building import Building
from ct.src.shared_sprite import SharedSprite
from ct.src.item import Item
from ct.src.shared_item import SharedItem
from ct.src.shared_ability import SharedAbility
from ct.src.ui import UI
from ct.src.ui_containers import UIRenderable
from ct.src.ai import AIAbility
from ct.src.warp_point import WarpPoint

T = TypeVar('T')

# ^ must weak import all files that will call this as they are all going into
#   ct_array!

# IMPORTANT - MAKE SURE TO UPDATE CT_COMPILER WITH ANY ARRAY FUNCTION
# THAT INDEXES BASED ON arr.size. CT_COMPILER HAS A HACKY CONDITION
# THAT MUST BE ADDED TO SO THAT THESE FUNCTIONS ARE IGNORED BY BOUNDS
# CHECKING!


def push(arr, value_ptr):
    capacity = array_capacity(arr)
    if arr.size > capacity - 1:
        print("push - array size is > than capacity - 1.",
              "size:", arr.size, "capacity:", capacity)
        exit(1)
    arr[arr.size] = deref(value_ptr)
    arr.size += 1


def push_value(arr, value):
    capacity = array_capacity(arr)
    if arr.size > capacity - 1:
        print("push_value - array size is > than capacity - 1.",
              "size:", arr.size, "capacity:", capacity)
        exit(1)
    arr[arr.size] = value
    arr.size += 1


def reverse(arr):
    # reverses the array
    start = 0
    end = arr.size - 1
    while start < end:
        temp = arr[start]
        arr[start] = arr[end]
        arr[end] = temp
        start += 1
        end -= 1


def next(arr):
    capacity = array_capacity(arr)
    if arr.size > capacity - 1:
        print("next - array size is > than capacity - 1.",
              "size:", arr.size, "capacity:", capacity)
        exit(1)
    value = addr(arr[arr.size])
    arr.size += 1
    return value


def next_handle(arr):
    capacity = array_capacity(arr)
    if arr.size > capacity - 1:
        print("next_handle - array size is > than capacity - 1.",
              "size:", arr.size, "capacity:", capacity)
        exit(1)
    handle = arr.size
    arr.size += 1
    return handle


def remove_at(arr, idx: int):
    if idx < 0 or idx > arr.size - 1:
        print("remove_at - idx is out of bounds", idx, arr.size)
        exit(1)
    arr.size -= 1
    for i in range(idx, arr.size):
        next_idx = i + 1
        # have to store i + 1 in a var because the py compiler can't parse
        # i + 1 in brackets due to the spaces. Bracket notation needs no
        # spaces to be parsed.
        arr[i] = arr[next_idx]


def clear(arr):
    arr.size = 0


def string_set_literal(arr, string_literal):
    # arr is of type Array of char, string literal is of type char*
    capacity = array_capacity(arr)
    length = strlen(string_literal)
    buffer = array_get_buffer(arr)

    if length > capacity - 1:
        print("string_set_literal - string literal length is > then the capacity of arr.",
              "\nstring literal length:", length, "\narr capacity:",
              capacity, "\narr str:", buffer, "\nstring_literal:", string_literal)
        exit(1)
    strcpy(buffer, string_literal)
    arr.size = length


def string_set(arr1, arr2):
    # arr1 and arr2 are both of type Array of char
    capacity = array_capacity(arr1)
    buffer1 = array_get_buffer(arr1)
    buffer2 = array_get_buffer(arr2)

    if arr2.size > capacity - 1:
        print("string_set - arr2.size > then the capacity of arr1",
              "\narr2.size:", arr2.size, "\narr1 capacity:", capacity,
              "\narr1 str:", buffer1, "\narr2 str:", buffer2)
        exit(1)
    strcpy(buffer1, buffer2)
    arr1.size = arr2.size


def string_cat_literal(arr, string_literal):
    # arr is of type Array of char, string literal is of type char*
    capacity = array_capacity(arr)
    length = strlen(string_literal)
    buffer = array_get_buffer(arr)

    # nothing to cat
    if length == 0:
        return
    # if arr1 size is 0 make sure it has a null terminator by doing a strcpy of an empty string.
    # a size of 0 might mean its unitialized.
    if arr.size == 0:
        string_set_literal(arr, "")
    if arr.size + length > capacity - 1:
        print("string_cat_literal - arr.size + string literal length is > then the capacity of arr.",
              "\narr size:", arr.size, "\nstring literal length:", length,
              "\narr capacity:", capacity, "\narr str:", buffer,
              "\nstring_literal:", string_literal)
        exit(1)
    strcat(buffer, string_literal)
    arr.size += length


def string_cat(arr1, arr2):
    # arr1 and arr2 are both of type Array of char
    capacity = array_capacity(arr1)
    buffer1 = array_get_buffer(arr1)
    buffer2 = array_get_buffer(arr2)

    # nothing to cat
    if arr2.size == 0:
        return
    # if arr1 size is 0 make sure it has a null terminator by doing a strcpy of an empty string.
    # a size of 0 might mean its unitialized.
    if arr1.size == 0:
        string_set_literal(arr1, "")
    if arr1.size + arr2.size > capacity - 1:
        print("string_cat - arr1.size + arr2.size is > then the capacity of arr.",
              "\narr1 size:", arr1.size, "\narr2 size:", arr2.size,
              "\narr capacity:", capacity, "\narr1 str:", buffer1, "\narr2 str:", buffer2)
        exit(1)
    strcat(buffer1, buffer2)
    arr1.size += arr2.size


def find_and_remove_handle(arr, handle_to_remove: int):
    # does not work for pools - arr must be an array of int
    handle_to_remove_idx = -1
    for i in range(arr.size):
        handle = arr[i]
        if handle == handle_to_remove:
            handle_to_remove_idx = i
            break
    if handle_to_remove_idx != -1:
        arr.remove_at(handle_to_remove_idx)


def pool_init(game: Game, arr, last_in_use_handle_ptr: int):
    arr.size = array_capacity(arr)
    set(deref(last_in_use_handle_ptr), -1)
    for i, item in enumerate(arr):
        item.init(game, i)


def pool_of_text_init(game: Game, arr, last_in_use_handle_ptr: int):
    # text uses text_init because there are many texts for each string size.
    arr.size = array_capacity(arr)
    set(deref(last_in_use_handle_ptr), -1)
    for i, item in enumerate(arr):
        item.text_init(game, i)


def pool_get_handle(arr, last_in_use_handle_ptr: int, debug_pool_name_char_ptr) -> int:
    last_in_use_handle = deref(last_in_use_handle_ptr)
    for i, item in enumerate(arr):
        if not(item.in_use_in_pool):
            item.in_use_in_pool = True
            # update last_in_use_handle_ptr if the handle returned
            # is greater than the last_in_use_handle_ptr value
            if i > last_in_use_handle:
                set(deref(last_in_use_handle_ptr), i)
            return i
    capacity = array_capacity(arr)
    print("pool_get_handle - all elements are in use.")
    print("pool name:", debug_pool_name_char_ptr, "\npool size: ",
          arr.size, "\npool capacity:", capacity)
    exit(1)


def pool_release_handle(arr, handle: int, last_in_use_handle_ptr: int):
    last_in_use_handle = deref(last_in_use_handle_ptr)
    item = arr.at(handle)
    if not(item.in_use_in_pool):
        print("pool_release_handle - tried to release an inactive item. Item must be active to be released.")
        exit(1)
    item.in_use_in_pool = False
    # if the handle released is the last in use handle, then find the new last in use
    # handle. If you do a batch release, make sure the indices are in ascending order so that
    # only the last delete triggers this scan, i.e indices [0, 1, 2, 3, 4, 5] if 5 is the last
    # in use handle it only triggers this branch on the last index in the list.
    # unit_handles in map for enemies follows this pattern.
    if handle == last_in_use_handle:
        set(deref(last_in_use_handle_ptr), pool_get_last_in_use_handle(arr))


def pool_get_last_in_use_handle(arr) -> int:
    # this function does a linear scan through the array for the last
    # in_use_in_pool item. This is thus somewhat slow and should be used
    # sparingly.
    max_handle = -1
    for i, item in enumerate(arr):
        if item.in_use_in_pool:
            max_handle = i
    return max_handle


def pool_get_next_in_use_handle(arr, last_in_use_handle: int, start_handle: int) -> int:
    # look for the next in use handle after start handle, wrapping to 0 if going over the
    # last in use handle. If it gets to the start_handle then none were found.
    iters = 0
    max_iters = arr.size
    i = start_handle + 1
    while i != start_handle:
        if i > last_in_use_handle + 1:
            i = 0
        item = arr.at(i)
        if item.in_use_in_pool:
            return i
        i += 1
        iters += 1
        if iters > max_iters:
            return -1
    return -1
