from ct.src.image import *
from ct.src.utils import SDL_Rect
from ct.src.image import Image
# weak imports
from ct.src.game import Game


class CPosition:
    def __init__(self):
        self.go_handle: int = None
        self.dst: SDL_Rect = None


class CSprite:
    def __init__(self):
        self.go_handle: int = None
        self.image: Image = None
        self.src: SDL_Rect = None
