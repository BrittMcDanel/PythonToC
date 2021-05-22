from ct.src.utils import SDL_Rect
from ct.src.base_types import Array, Uint64, char
from ct.src.ct_array import Array
from ct.src.inventory import Inventory
# weak imports
from ct.src.game import Game


class Guild:
    def __init__(self):
        self.display_name: Array[char] = Array[char](100)
        self.unit_handles: Array[int] = Array[int](30)
        self.merchant_handles: Array[int] = Array[int](30)
        self.inventory: Inventory = None
        self.current_money: Uint64 = None
        self.total_money_earned: Uint64 = None
        self.is_anonymous: bool = None
        self.handle: int = None
        self.in_use_in_pool: bool = None

    def init(self, game: Game, handle: int):
        self.handle = handle
        self.in_use_in_pool = False

        # init values
        self.current_money = 500
        self.inventory.init()

    def set_to(self, display_name_str):
        # this func might do more later
        self.display_name.string_set_literal(display_name_str)
