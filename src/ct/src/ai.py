from ct.src.engine import SDL_RenderCopy
from ct.src.utils import SDL_Rect, RenderDst, UIEvent, rect_contains_point, set_scaled_rect, set_scaled_rect_with_camera
from ct.src.ct_array import Array
from ct.src.base_types import addr, Uint32, mod, SpriteSrcsPtr
from ct.src.constants import AIAbilityCondition
# weak imports
from ct.src.game import Game


class AIAbility:
    def __init__(self):
        self.unit_ability_handle: int = None
        self.condition: AIAbilityCondition = None
        self.is_empty: bool = None

    def set(self, unit_ability_handle: int, condition: AIAbilityCondition):
        self.unit_ability_handle = unit_ability_handle
        self.condition = condition
        self.is_empty = False

    def clear(self):
        self.is_empty = True
