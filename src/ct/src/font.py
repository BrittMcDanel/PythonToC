from ct.src.ct_array import *
from ct.src.constants import *
from ct.src.utils import SDL_Rect
from ct.src.base_types import Array


class CharInfo:
    def __init__(self):
        self.rect: SDL_Rect = None
        self.minx: int = 0
        self.maxx: int = 0
        self.miny: int = 0
        self.maxy: int = 0
        self.advance: int = 0


class Font:
    def __init__(self):
        self.stb_font: STBTTF_FontPtr = None
        self.texture: SDL_TexturePtr = None
        self.font_style: FontStyle = None
        self.font_size: int = 0
        self.color: SDL_Color = None
        self.outline: int = 0
        self.outline_color: SDL_Color = None
        self.font_height: int = 0
        self.use_drop_shadow: bool = 0
        self.char_infos: Array[CharInfo] = Array[CharInfo](322)
