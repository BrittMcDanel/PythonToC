from ct.src.engine import SDL_RenderCopy
from ct.src.image import *
from ct.src.utils import SDL_Rect, RenderDst, set_scaled_rect, set_scaled_rect_with_camera
from ct.src.image import Image
from ct.src.ct_array import Array
from ct.src.base_types import addr, Uint32, mod
# weak imports
from ct.src.game import Game


class Sprite:
    def __init__(self):
        self.image: Image = None
        self.render_dst: RenderDst = None
        self.srcs: Array[SDL_Rect] = Array[SDL_Rect](10)
        self.current_frame_idx: int = 0
        self.anim_speed: Uint32 = None
        self.spawn_time: Uint32 = None

    def update(self, game: Game):
        if self.srcs.size == 0:
            print("Sprite.get_current_frame - srcs.size is 0.")
            exit(1)
        if self.anim_speed == 0:
            print("Sprite.get_current_frame - anim_speed is 0.")
            exit(1)
        self.current_frame_idx = game.get_current_frame(
            self.srcs.size, self.anim_speed, self.spawn_time)
        src = self.srcs.at(self.current_frame_idx)
        self.render_dst.dst.w = src.w
        self.render_dst.dst.h = src.h
        self.render_dst.update(game.engine.camera.dst, game.engine.scale)

    def draw(self, game: Game):
        src = self.srcs.at(self.current_frame_idx)
        SDL_RenderCopy(game.engine.renderer, self.image.texture,
                       src, self.render_dst.scaled_dst)

    def draw_at(self, game: Game, unscaled_dst: SDL_Rect):
        # for when ui wants to draw the sprite somewhere
        src = self.srcs.at(0)
        unscaled_dst.w = src.w
        unscaled_dst.h = src.h
        set_scaled_rect(unscaled_dst, game.engine.scale)
        SDL_RenderCopy(game.engine.renderer, self.image.texture,
                       src, unscaled_dst)
