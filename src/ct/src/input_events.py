from ct.src.engine import SDL_RenderCopy
from ct.src.image import *
from ct.src.utils import SDL_Rect, RenderDst, set_scaled_rect, set_scaled_rect_with_camera
from ct.src.image import Image
from ct.src.ct_array import Array
from ct.src.base_types import addr, Uint32, mod
# weak imports
from ct.src.game import Game


class InputEvents:
    def __init__(self):
        self.is_mouse_enter: bool = None
        self.is_mouse_exit: bool = None
        self.is_mouse_over: bool = None
        self.is_mouse_down: bool = None
        self.is_mouse_held_down: bool = None
        self.is_mouse_up: bool = None
        self.is_right_mouse_down: bool = None
        self.is_right_mouse_held_down: bool = None
        self.is_right_mouse_up: bool = None
        self.is_click: bool = None
        self.is_right_click: bool = None
        self.was_mouse_down_when_mouse_over: bool = None
        self.was_right_mouse_down_when_mouse_over: bool = None

    def clear(self):
        self.is_mouse_enter = False
        self.is_mouse_exit = False
        self.is_mouse_over = False
        self.is_mouse_down = False
        self.is_mouse_held_down = False
        self.is_mouse_up = False
        self.is_right_mouse_down = False
        self.is_right_mouse_held_down = False
        self.is_right_mouse_up = False
        self.is_click = False
        self.is_right_click = False
        self.was_mouse_down_when_mouse_over = False
        self.was_right_mouse_down_when_mouse_over = False

    def update(self, game: Game, _is_mouse_over: bool):
        self.is_click = False
        if _is_mouse_over:
            # call onMouseEnter once by calling it before the isMouseOver flag is set
            if not(self.is_mouse_over):
                self.is_mouse_enter = True
            self.is_mouse_over = True
        else:
            # call only once before flag is set
            if self.is_mouse_over:
                self.is_mouse_exit = False
            self.is_mouse_over = False
        # events that require mouse enter status
        # mouse down
        if game.engine.is_mouse_down:
            if self.is_mouse_over:
                self.was_mouse_down_when_mouse_over = True
                self.is_mouse_down = True
            else:
                self.was_mouse_down_when_mouse_over = False
        # mouse up
        if game.engine.is_mouse_up:
            if self.is_mouse_over:
                self.is_mouse_up = True
                if self.was_mouse_down_when_mouse_over:
                    self.is_click = True
            # always set to False on mouse up
            self.was_mouse_down_when_mouse_over = False
        # mouse held down
        if game.engine.is_mouse_held_down:
            if self.is_mouse_over:
                self.is_mouse_held_down = True
        # right mouse down
        if game.engine.is_right_mouse_down:
            if self.is_mouse_over:
                self.was_right_mouse_down_when_mouse_over = True
                self.is_right_mouse_down = True
            else:
                self.was_right_mouse_down_when_mouse_over = False
        # right mouse up
        if game.engine.is_right_mouse_up:
            if self.is_mouse_over:
                self.is_right_mouse_up = True
                if self.was_right_mouse_down_when_mouse_over:
                    self.is_right_click = True
            # always set to False on mouse up
            self.was_right_mouse_down_when_mouse_over = False
        # right mouse held down
        if game.engine.is_right_mouse_held_down:
            if self.is_mouse_over:
                self.is_right_mouse_held_down = True
