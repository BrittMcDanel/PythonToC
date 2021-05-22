from ct.src.engine import SDL_RenderCopy, Engine
from ct.src.image import *
from ct.src.utils import SDL_Rect, RenderDst, create_rect, rects_are_equal, set_scaled_rect, set_scaled_rect_with_camera
from ct.src.image import Image
from ct.src.ct_array import Array
from ct.src.base_types import addr, Uint32, array_capacity, mod, ItemPtr, last_enum_int, cast, AbilityPtr
from ct.src.constants import UnitName, Faction
from ct.src.unit import Unit
# weak imports
from ct.src.game import Game


class UnitDB:
    def __init__(self):
        self.units: Array[Unit] = Array[Unit](200)

    def init(self, game: Game):
        self.units.size = array_capacity(self.units)
        last_enum_idx = last_enum_int(UnitName)
        if last_enum_idx > self.units.size - 1:
            print("UnitDB.init - UnitName's last enum idx is > units capacity.")
            exit(1)
        # skip NA by starting at 1
        for i in range(1, last_enum_idx):
            unit_name = cast(i, "UnitName")
            game.temp_unit.init(game, 0)
            game.temp_unit.set_to(game, unit_name, Faction.Ally)
            self.units[i] = game.temp_unit

    def get_unit(self, unit_name: UnitName) -> Unit:
        unit_name_as_int = cast(unit_name, "int")
        return self.units.at(unit_name_as_int)
