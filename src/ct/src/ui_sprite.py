from ct.src.engine import SDL_RenderCopy
from ct.src.image import *
from ct.src.utils import SDL_Rect, RenderDst, UIEvent, rect_contains_point, set_scaled_rect, set_scaled_rect_with_camera
from ct.src.image import Image
from ct.src.ct_array import Array
from ct.src.base_types import addr, Uint32, mod, SpriteSrcsPtr
from ct.src.input_events import InputEvents
from ct.src.shared_sprite import SpriteSrcs
# weak imports
from ct.src.game import Game


class UISprite:
    def __init__(self):
        self.image: Image = None
        self.render_dst: RenderDst = None
        self.shared_srcs: SpriteSrcsPtr = None
        self.current_frame_idx: int = 0
        self.anim_speed: Uint32 = None
        self.spawn_time: Uint32 = None
        self.ui_event: UIEvent = None
        self.input_events: InputEvents = None

    def update(self, game: Game):
        if self.shared_srcs == None:
            print("Sprite.update - shared srcs is NULL.")
            exit(1)
        if self.shared_srcs.srcs.size == 0:
            print("Sprite.update - srcs.size is 0.")
            exit(1)
        if self.anim_speed == 0:
            print("Sprite.update - anim_speed is 0.")
            exit(1)
        self.current_frame_idx = game.get_current_frame(
            self.shared_srcs.srcs.size, self.anim_speed, self.spawn_time)
        src = self.shared_srcs.srcs.at(self.current_frame_idx)
        self.render_dst.dst.w = src.w
        self.render_dst.dst.h = src.h
        self.render_dst.update(game.engine.camera.dst, game.engine.scale)

        # update input events
        is_mouse_over = rect_contains_point(
            self.render_dst.dst, game.engine.mouse_point_scaled)
        self.input_events.update(game, is_mouse_over)

    def draw(self, game: Game):
        src = self.shared_srcs.srcs.at(self.current_frame_idx)
        SDL_RenderCopy(game.engine.renderer, self.shared_srcs.image.texture,
                       src, self.render_dst.scaled_dst)
