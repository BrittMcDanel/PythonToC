from ct.src.engine import SDL_RenderCopy
from ct.src.image import *
from ct.src.utils import SDL_Rect, create_rect, set_scaled_rect, set_scaled_rect_with_camera, Range
from ct.src.image import Image
from ct.src.ct_array import Array
from ct.src.base_types import Uint64, addr, Uint32, cast
from ct.src.sprite import Sprite
from ct.src.constants import AbilityName, ImageName
# weak imports
from ct.src.game import Game


class Stats:
    def __init__(self):
        self.level: int = None
        self.job_level: int = None
        self.experience_drop: Uint64 = None
        self.job_experience_drop: Uint64 = None
        self.experience: Range = None
        self.job_experience: Range = None
        self.strength: Range = None
        self.intelligence: Range = None
        self.dexterity: Range = None
        self.vitality: Range = None
        self.agility: Range = None
        self.luck: Range = None
        self.hp: Range = None
        self.attack_speed: Range = None
