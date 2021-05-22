from ct.src.constants import *
from ct.src.base_types import SDL_TexturePtr, SDL_RectPtr, Uint32, cast, set
from ct.src.utils import DoublePoint, SDL_Rect, SDL_Point, deref
# weak imports
from ct.src.game import Game


class TweenCompletion:
    def __init__(self):
        self.initial_has_started: bool = None
        self.completed: bool = None


class TweenCallback:
    def __init__(self):
        self.tween_higher_level_type: TweenHigherLevelType = None
        self.tween_type: TweenType = None
        self.handle_type: HandleType = None
        self.handle: int = None
        self.tile_point: SDL_Point = None
        self.warp_point_handle: int = None
        self.is_final_point_in_path: bool = None
        self.acting_unit_handle: int = None
        self.receiving_unit_handle: int = None
        self.merchant_unit_handle: int = None
        self.map_handle: int = None


class TweenXY:
    def __init__(self):
        self.start_val: SDL_Rect = None
        self.val: SDL_RectPtr = None
        self.target_val: SDL_Rect = None
        self.target_val_ptr: SDL_RectPtr = None
        self.speed: float = None
        self.is_constant_speed: bool = None
        self.spawn_time: Uint32 = None
        self.duration: Uint32 = None
        self.delay: Uint32 = None
        self.has_started: bool = None
        self.double_point: DoublePoint = None
        self.callback: TweenCallback = None
        self.remove_in_update: bool = None
        self.handle: int = None
        self.in_use_in_pool: bool = None

    def init(self, game: Game, handle: int):
        self.handle = handle
        self.in_use_in_pool = False

    def set(self, game: Game, start_val: SDL_Rect, val: SDL_Rect, target_val: SDL_Rect, is_constant_speed: bool,
            speed: float, duration: Uint32, delay: Uint32, callback: TweenCallback):
        self.start_val = deref(start_val)
        self.val = val
        self.target_val = deref(target_val)
        # for constant speed tweens where it needs to go to the target point even if it changes
        # after this call.
        self.target_val_ptr = target_val
        self.speed = speed
        self.is_constant_speed = is_constant_speed
        self.duration = duration
        self.delay = delay
        self.spawn_time = game.engine.current_time
        x_as_double = cast(start_val.x, "double")
        y_as_double = cast(start_val.y, "double")
        self.double_point.init(x_as_double, y_as_double)
        self.callback = deref(callback)
        self.remove_in_update = False
        self.has_started = False

    def update(self, game: Game) -> TweenCompletion:
        tween_completion = TweenCompletion()
        tween_completion.initial_has_started = False
        tween_completion.completed = False

        current_time = game.engine.current_time
        # set value to start value outside of update, as the update call order
        # is not guaranteed and a later tween that has not started can reset
        # the value to the start value after a previous tween has updated it.
        # i.e can't do self.val = self.start_val here.
        if current_time < self.spawn_time + self.delay:
            return tween_completion
        if not(self.has_started):
            self.has_started = True
            tween_completion.initial_has_started = True
        if self.is_constant_speed:
            delta_x = self.target_val_ptr.x - self.double_point.x
            delta_y = self.target_val_ptr.y - self.double_point.y
            delta_dist = sqrt(delta_x * delta_x + delta_y * delta_y)
            frac = self.speed / delta_dist
            x = frac * delta_x
            y = frac * delta_y
            self.double_point.x += x
            self.double_point.y += y
            self.val.x = cast(self.double_point.x, "int")
            self.val.y = cast(self.double_point.y, "int")
            # some min dist to check for
            if delta_dist < 4.0:
                tween_completion.completed = True
                return tween_completion
        else:
            duration_as_double = cast(self.duration, "double")
            total_delay = self.spawn_time + self.delay
            elapsed = current_time - total_delay
            frac = elapsed / duration_as_double
            if frac > 1.0:
                frac = 1.0
            diff_x = self.target_val.x - self.start_val.x
            diff_y = self.target_val.y - self.start_val.y
            x = diff_x * frac
            y = diff_y * frac
            x_as_int = cast(x, "int")
            y_as_int = cast(y, "int")
            self.val.x = self.start_val.x + x_as_int
            self.val.y = self.start_val.y + y_as_int
            if current_time >= self.spawn_time + self.delay + self.duration:
                tween_completion.completed = True
                return tween_completion

        return tween_completion


'''<c_library_funcs>
double sqrt(double x);
</c_library_funcs>'''


def sqrt(a: float) -> float:
    return 0
