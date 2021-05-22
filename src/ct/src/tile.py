from ct.src.image import *
from ct.src.utils import SDL_Rect
from ct.src.image import Image
from ct.src.ct_array import Array
from ct.src.sprite import Sprite, sprite_draw, sprite_update
from ct.src.shared_sprite import SharedSprite
# weak imports
from ct.src.game import Game


class Tile:
    def __init__(self):
        self.sprite: SharedSprite = None

    def update(self, game: Game):
        self.sprite.update(game)

    def draw(self, game: Game):
        self.sprite.draw(game)
