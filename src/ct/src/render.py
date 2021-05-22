from ct.src.engine import SDL_RenderCopy
from ct.src.image import *
from ct.src.utils import SDL_Rect
from ct.src.image import Image
from ct.src.ct_array import Array
from ct.src.base_types import addr, SDL_TexturePtr
# weak imports
from ct.src.game import Game


class RenderSprite:
    def __init__(self):
        self.texture: SDL_TexturePtr = None
        self.src: SDL_Rect = None
        self.dst: SDL_Rect = None
        self.layer: int = None
        self.is_hidden: bool = None


def create_render_sprite(texture: SDL_TexturePtr, src: SDL_Rect,
                         dst: SDL_Rect, layer: int, is_hidden: bool) -> RenderSprite:
    s = RenderSprite()
    s.texture = texture
    s.src = src
    s.dst = dst
    s.layer = layer
    s.is_hidden = is_hidden
    return s


def render_sprite_draw(game: Game, render_sprite: RenderSprite):
    SDL_RenderCopy(game.engine.renderer, render_sprite.texture,
                   render_sprite.src, render_sprite.dst)
