from typing import Any, TypeVar, Generic, List, Iterable,  Callable, Generator, Coroutine
from ct.src.unit_sprite import UnitSprite
from ct.src.utils import SDL_Rect, SDL_Point
from ct.src.ability import Ability
from ct.src.item import Item
from ct.src.shared_sprite import SpriteSrcs
from ct.src.ui import UIRect
from ct.src.text import TextLG
from ct.src.ui_sprite import UISprite
from ct.src.sprite import Sprite

T = TypeVar('T')
N = TypeVar('N')
Vector = List[int]
VectorPtr = List[int]
Uint8 = int
Uint32 = int
Uint64 = int
SDL_PointPtr = SDL_Point
SDL_RectPtr = SDL_Rect
AbilityPtr = Ability
ItemPtr = Item
SpriteSrcsPtr = SpriteSrcs
UIRectPtr = UIRect
UISpritePtr = UISprite
TextLGPtr = TextLG
SpritePtr = Sprite
UnitSpritePtr = UnitSprite


def addr(value: T) -> T:
    return value


def deref(value: T) -> T:
    return value


def rev_range(start, end=0, step=1):
    pass


def set(var, value):
    return var


def mod(val1, val2) -> int:
    return 0


def last_enum_int(enum_literal_value) -> int:
    return 0

# type_string must be a string.
# Example: a = cast(ImageName.Abilities, "int")


def cast(value, type_string):
    pass


def memset(value_ptr, value_to_set_to, mul_size_by):
    pass


def malloc(value: T, size: int) -> T:
    return value


def free(value):
    pass


def sizeof(value) -> int:
    return 0


def array_capacity(array_val):
    pass


def array_get_buffer(array_val):
    pass


def strcpy(dst, src):
    pass


def strcat(dst, src):
    pass


def strlen(str) -> int:
    return 0


def sprintf(array_of_char, format_string, *args):
    pass


class macro():
    def __init__(self):
        pass


class char():
    def __init__(self):
        pass


class MTRand():
    def __init__(self):
        pass


class SDL_WindowPtr():
    def __init__(self):
        pass


class SDL_RendererPtr():
    def __init__(self):
        pass


class SDL_TexturePtr():
    def __init__(self):
        pass


class FontPtr():
    def __init__(self):
        pass


class Mix_MusicPtr():
    def __init__(self):
        pass


class Mix_ChunkPtr():
    def __init__(self):
        pass


class Array(Generic[T]):
    def __init__(self, _capacity: int) -> None:
        # Create an empty list with items of type T
        self.items: List[T] = []
        self.size: int = 0
        self.capacity: int = _capacity

    # these methods are just for intellisense. They are actually
    # implemented in ct_array. I am not doing generic classes yet.
    def push(self, value_ptr: T) -> None:
        pass

    def push_value(self, value: T) -> None:
        pass

    def at(self, index: int) -> T:
        pass

    def remove_at(arr, idx: int):
        pass

    def clear(self) -> None:
        pass

    def next(self) -> T:
        pass

    def next_handle(self) -> int:
        pass

    def pop(self) -> T:
        return self.items.pop()

    def empty(self) -> bool:
        return not self.items

    def string_set_literal(arr, string_literal):
        pass

    def string_set(arr1, arr2):
        pass

    def string_cat_literal(arr, string_literal):
        pass

    def string_cat(arr1, arr2):
        pass

    def pool_get_handle(arr) -> int:
        return 0

    def pool_release_handle(arr, handle: int):
        pass

    def pool_last_in_use_handle(arr) -> int:
        return 0

    def __getitem__(self, idx: int) -> T:
        self.size = 0
        return self.items[idx]

    def __setitem__(self, idx: int, value: T):
        return self

    def __iter__(self) -> Generator[T, None, None]:
        for elem in self.items:
            yield elem

    def __next__(self) -> T:
        return self.items[0]


class Array2D(Generic[T]):
    def __init__(self, _container_capacity: int, _element_capacity: int) -> None:
        # Create an empty list with items of type T
        self.items: Array[Array[T]] = Array[Array[T]](_container_capacity)
        self.size: int = 0

    def push(self, item: Array[T]) -> None:
        self.items.push(item)

    def pop(self) -> Array[T]:
        return self.items.pop()

    def empty(self) -> bool:
        return not self.items

    def __getitem__(self, idx: int) -> Array[T]:
        self.size = 0
        return self.items[idx]

    def __setitem__(self, idx: int, value: T):
        self.size = 0


class Array3D(Generic[T]):
    def __init__(self, _3d_capacity: int, _2d_capacity: int, _1d_capacity: int) -> None:
        # Create an empty list with items of type T
        self.items: Array[Array[Array[T]]] = Array[Array[Array[T]]](
            _3d_capacity)
        self.size: int = 0

    def push(self, item: Array[Array[T]]) -> None:
        self.items.push(item)

    def pop(self) -> Array[Array[T]]:
        return self.items.pop()

    def empty(self) -> bool:
        return not self.items

    def __getitem__(self, idx: int) -> Array[Array[T]]:
        self.size = 0
        return self.items[idx]

    def __setitem__(self, idx: int, value: T):
        self.size = 0
