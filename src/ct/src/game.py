from typing import Any
from ct.src.engine import Engine, engine_test, engine_start
from ct.src.world import World
from ct.src.scene_map import SceneMap
from ct.src.ct_array import *
from ct.src.base_types import Array, Uint32, addr, last_enum_int, sizeof, mod
from ct.src.constants import *
from ct.src.map import Map, map_create_initial, map_update, map_draw
from ct.src.utils import SDL_Point, SDL_Rect, create_point, create_rect
from ct.src.shared_sprite import SpriteDB
from ct.src.shared_item import ItemDB
from ct.src.unit_sprite import UnitSprite
from ct.src.item import Item
from ct.src.ability import Ability
from ct.src.inventory import Inventory
from ct.src.shared_ability import AbilityDB, SharedAbility
from ct.src.shared_unit import UnitDB
from ct.src.ui import UI
from typing import Any


class Game:
    def __init__(self):
        self.engine: Engine = None
        self.sprite_db: SpriteDB = None
        self.unit_db: UnitDB = None
        self.item_db: ItemDB = None
        self.ability_db: AbilityDB = None
        self.world: World = None
        self.tile_size: SDL_Point = None
        self.max_map_size: SDL_Point = None
        self.move_grid_tile_size: SDL_Point = None
        self.move_grid_ratio: int = None
        self.temp_ability: Ability = None
        self.temp_shared_ability: SharedAbility = None
        self.temp_item: Item = None
        self.temp_shared_item: SharedItem = None
        self.temp_unit: Unit = None

    def start(self):
        game_size = sizeof(Game())
        world_size = sizeof(World())
        pathfinder_size = sizeof(PathFinder())
        map_size = sizeof(Map())
        tile_size = sizeof(Tile())
        unit_size = sizeof(Unit())
        unit_sprite_size = sizeof(UnitSprite())
        ability_size = sizeof(Ability())
        inventory_size = sizeof(Inventory())
        ui_size = sizeof(UI())
        print("game size:", game_size)
        print("world size:", world_size)
        print("pathfinder size:", pathfinder_size)
        print("map size:", map_size)
        print("tile size:", tile_size)
        print("unit size:", unit_size)
        print("unit sprite size:", unit_sprite_size)
        print("ability size:", ability_size)
        print("inventory size:", inventory_size)
        print("ui size:", ui_size)
        self.tile_size = create_point(20, 20)
        self.max_map_size = create_point(80, 80)
        self.move_grid_tile_size = create_point(2, 2)
        self.move_grid_ratio = self.tile_size.x / self.move_grid_tile_size.x
        # check to see if the pathfinder capacity on the lookup tables
        # is large enough for the max map after setting move grid vars.
        self.world.path_finder.check_lookup_table_size(self)
        self.engine.init()
        # textures loaded here
        engine_start(self.engine)
        # init dbs for shared resources
        self.sprite_db.init(self)
        self.item_db.init(self)
        self.ability_db.init(self)
        self.unit_db.init(self)
        self.world.init(self)

    def update(self):
        self.world.update(self)

    def draw(self):
        self.world.draw(self)

    def get_current_frame(self, srcs_size: int, anim_speed: Uint32, spawn_time: Uint32) -> int:
        if anim_speed == 0:
            print("Game.get_current_frame - anim_speed is 0.")
            exit(1)
        if srcs_size == 0:
            print("Game.get_current_frame. srcs size is 0.")
            exit(1)
        alive_time = self.engine.current_time - spawn_time
        return mod(alive_time / anim_speed, srcs_size)
