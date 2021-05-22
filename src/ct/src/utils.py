from ct.src.base_types import deref, Uint64, mod, cast
from ct.src.constants import AbilityName, Faction, StatName, UIEventName, UnitName


class SDL_Rect:
    def __init__(self):
        self.x: int = 0
        self.y: int = 0
        self.w: int = 0
        self.h: int = 0


class SDL_Point:
    def __init__(self):
        self.x: int = 0
        self.y: int = 0


class SDL_Color:
    def __init__(self):
        self.r: int = 0
        self.g: int = 0
        self.b: int = 0
        self.a: int = 0


class DoublePoint:
    def __init__(self):
        self.x: float = 0
        self.y: float = 0

    def init(self, x: float, y: float):
        self.x = x
        self.y = y


class Range:
    def __init__(self):
        self.min: Uint64 = None
        self.value_before_buffs: Uint64 = None
        self.value: Uint64 = None
        self.max: Uint64 = None
        self.upper_bound: Uint64 = None

    def set(self, min: Uint64, value: Uint64, upper_bound: Uint64):
        self.min = min
        self.value_before_buffs = value
        self.value = value
        # max is only useful for hp I think
        self.max = value
        self.upper_bound = upper_bound

    def set_with_max_to_upper_bound(self, min: Uint64, value: Uint64, upper_bound: Uint64):
        self.min = min
        self.value_before_buffs = value
        self.value = value
        # max is only useful for hp I think
        self.max = upper_bound
        self.upper_bound = upper_bound

    def inc(self, value: Uint64):
        # prevent overflow, if the diff between max and value is 10
        # and the value to inc is 20, then it will always be > max so set it to
        # max. If max is the max Uin64 value, then value won't overflow.
        diff = self.max - self.value
        if value > diff:
            self.value = self.max
        else:
            self.value += value

    def dec(self, value: Uint64):
        # prevent underflow by checking if it would underflow first.
        # if my value is <= the value to be decremented, then the result
        # will be <= 0, so just set to it 0. A subtraction would cause an underflow,
        # as it is a result < 0.
        if self.value <= value:
            self.value = self.min
        else:
            self.value -= value

    def value_is_at_min(self) -> bool:
        return self.value <= self.min

    def value_is_at_max(self) -> bool:
        return self.value >= self.max

    def set_to_min(self):
        self.value = self.min

    def set_to_max(self):
        self.value = self.max

    def value_pct_of_max(self) -> float:
        value_as_double = cast(self.value, "double")
        max_as_double = cast(self.max, "double")
        return value_as_double / max_as_double


class RenderDst:
    def __init__(self):
        self.dst: SDL_Rect = None
        self.scaled_dst: SDL_Rect = None
        self.is_camera_rendered: bool = None

    def update(self, camera_dst: SDL_Point, engine_scale: int):
        self.scaled_dst = self.dst
        if self.is_camera_rendered:
            set_scaled_rect_with_camera(
                self.scaled_dst, camera_dst, engine_scale)
        else:
            set_scaled_rect(self.scaled_dst, engine_scale)


class UIEvent:
    def __init__(self):
        self.event_name: UIEventName = None
        self.handle: int = None
        self.guild_handle: int = None
        self.unit_name: UnitName = None
        self.ability_name: AbilityName = None
        self.stat_name: StatName = None


class MoveOptions:
    def __init__(self):
        self.warp_point_handle: int = None
        self.check_unit_collissions: bool = None
        self.merchant_unit_handle: int = None


def create_point(x, y) -> SDL_Point:
    p = SDL_Point()
    p.x = x
    p.y = y
    return p


def create_rect(x, y, w, h) -> SDL_Rect:
    r = SDL_Rect()
    r.x = x
    r.y = y
    r.w = w
    r.h = h
    return r


def create_color(r, g, b, a) -> SDL_Color:
    c = SDL_Color()
    c.r = r
    c.g = g
    c.b = b
    c.a = a
    return c


def add_points(p1: SDL_Point, p2: SDL_Point) -> SDL_Point:
    return create_point(p1.x + p2.x, p1.y + p2.y)


def subtract_points(p1: SDL_Point, p2: SDL_Point) -> SDL_Point:
    return create_point(p1.x - p2.x, p1.y - p2.y)


def points_are_equal(p1: SDL_Point, p2: SDL_Point) -> bool:
    return p1.x == p2.x and p1.y == p2.y


def rects_are_equal(r1: SDL_Rect, r2: SDL_Rect) -> bool:
    return r1.x == r2.x and r1.y == r2.y and r1.w == r2.w and r1.h == r2.h


def colors_are_equal(c1: SDL_Color, c2: SDL_Color) -> bool:
    return c1.r == c2.r and c1.g == c2.g and c1.b == c2.b and c1.a == c2.a


def manhattan_distance(p1: SDL_Point, p2: SDL_Point) -> int:
    return abs(p1.x - p2.x) + abs(p1.y - p2.y)


def rect_contains_point(r: SDL_Rect, p: SDL_Point) -> bool:
    return p.x >= r.x and p.x <= r.x + r.w and p.y >= r.y and p.y <= r.y + r.h


def rect_contains_rect(r1: SDL_Rect, r2: SDL_Rect) -> bool:
    return r1.x < r2.x + r2.w and r1.x + r1.w > r2.x and r1.y < r2.y + r2.h and r1.y + r1.h > r2.y


def set_scaled_rect(rect: SDL_Rect, scale: int):
    rect.x *= scale
    rect.y *= scale
    rect.w *= scale
    rect.h *= scale


def set_scaled_rect_with_camera(rect: SDL_Rect, camera_dst: SDL_Point, scale: int):
    p = create_point(rect.x, rect.y)
    p.x -= camera_dst.x
    p.y -= camera_dst.y
    p.x *= scale
    p.y *= scale
    rect.x = p.x
    rect.y = p.y
    rect.w *= scale
    rect.h *= scale


def iso_tile_point_to_world_point(p: SDL_Point, tile_half_dims: SDL_Point) -> SDL_Point:
    x = (p.x - p.y) * tile_half_dims.x
    y = (p.x + p.y) * tile_half_dims.y
    return create_point(x, y)


def iso_world_point_to_tile_point(world_point: SDL_Point, tile_half_dims: SDL_Point) -> SDL_Point:
    # MUST BE FLOATS OR THERE IS NOT ENOUGH PRECISION
    screen_x = 0.0 + world_point.x
    screen_y = 0.0 + world_point.y
    tile_width_half_float = 0.0 + tile_half_dims.x
    tile_height_half_float = 0.0 + tile_half_dims.y
    floor_x = (0.5 * ((screen_x - tile_width_half_float) / tile_width_half_float +
                      screen_y / tile_height_half_float))
    floor_y = (0.5 * (-(screen_x - tile_width_half_float) / tile_width_half_float +
                      screen_y / tile_height_half_float))
    return create_point(floor(floor_x), floor(floor_y))


def tile_point_to_world_point(idx: SDL_Point, tile_size: SDL_Point) -> SDL_Point:
    return create_point(idx.x * tile_size.x, idx.y * tile_size.y)


def world_point_to_tile_point(world_point: SDL_Point, tile_size: SDL_Point) -> SDL_Point:
    return create_point(world_point.x / tile_size.x, world_point.y / tile_size.y)


def world_point_to_index_with_camera(world_point: SDL_Point, camera_point: SDL_Point, tile_size: SDL_Point):
    p = deref(world_point)
    p.x += camera_point.x
    p.y += camera_point.y
    return world_point_to_tile_point(p, tile_size)


def get_1d_from_2d_idx(p: SDL_Point, rows: int) -> int:
    return p.x * rows + p.y


def get_move_grid_size_dims(w: int, h: int, move_grid_tile_size: SDL_Point) -> SDL_Point:
    move_grid_w = w / move_grid_tile_size.x
    move_grid_h = h / move_grid_tile_size.y
    return create_point(move_grid_w, move_grid_h)


def get_faction_color(faction: Faction) -> SDL_Color:
    if faction == Faction.Ally:
        return create_color(255, 255, 255, 255)
    elif faction == Faction.Guild:
        return create_color(89, 129, 255, 255)
    elif faction == Faction.Enemy:
        return create_color(255, 44, 83, 255)
    elif faction == Faction.Neutral:
        return create_color(255, 205, 117, 255)

    return create_color(255, 255, 255, 255)


def get_unit_name_job_tier(unit_name: UnitName) -> int:
    if unit_name == UnitName.Explorer:
        return 0
    elif unit_name == UnitName.Mage:
        return 1
    else:
        return 2


def unit_can_job_change(unit_name: UnitName, job_level: int) -> bool:
    job_tier = get_unit_name_job_tier(unit_name)
    if job_tier == 0 and job_level == 10:
        return True
    elif job_tier == 1 and job_level == 40:
        return True
    return False


def get_stat_points_for_level(level: int):
    level_div = level / 5.0
    value = floor(level_div) + 3
    value_as_int = cast(value, "int")
    return value_as_int


def get_stat_cost(stat_value: Uint64):
    stat_value -= 1
    stat_div = stat_value / 10.0
    value = floor(stat_div) + 2
    value_as_int = cast(value, "int")
    return value_as_int


def get_guild_color(guild_handle: int):
    if guild_handle == 0:
        return create_color(255, 255, 255, 255)
    elif guild_handle == 1:
        return create_color(200, 225, 255, 255)
    elif guild_handle == 2:
        return create_color(125, 155, 255, 255)
    elif guild_handle == 3:
        return create_color(115, 35, 125, 255)
    elif guild_handle == 4:
        return create_color(55, 89, 125, 255)
    elif guild_handle == 5:
        return create_color(38, 64, 255, 255)
    elif guild_handle == 6:
        return create_color(79, 235, 255, 255)
    elif guild_handle == 7:
        return create_color(100, 105, 155, 255)
    elif guild_handle == 8:
        return create_color(157, 125, 35, 255)
    return create_color(255, 255, 255, 255)


'''<c_library_funcs>
double floor(double val);
int abs(int val);
</c_library_funcs>'''

'''<c_func>
Uint32 get_max_uint32() {
  /* return SDL's max uint 32 because it looks like they check for portability */
  return SDL_MAX_UINT32;
}
</c_func>'''

'''<c_func>
Uint64 get_max_uint64() {
  /* return SDL's max uint 64 because it looks like they check for portability */
  return SDL_MAX_UINT64;
}
</c_func>'''


def floor(val: float) -> float:
    return val
