from ct.src.engine import SDL_RenderCopy
from ct.src.image import *
from ct.src.utils import SDL_Point, SDL_Rect, create_point, tile_point_to_world_point, create_rect, get_move_grid_size_dims, set_scaled_rect, set_scaled_rect_with_camera
from ct.src.image import Image
from ct.src.ct_array import Array
from ct.src.base_types import Uint32, addr, Uint64, cast, last_enum_int
from ct.src.sprite import Sprite
from ct.src.constants import BuildingName, ImageName, ItemName, ItemType
# weak imports
from ct.src.game import Game


class Item:
    def __init__(self):
        self.item_name: ItemName = None
        self.item_type: ItemType = None
        self.sprite: Sprite = None
        self.cost: Uint64 = None

    def update(self, game: Game):
        self.sprite.update(game)

    def draw(self, game: Game):
        self.sprite.draw(game)

    def set_to(self, game: Game, item_name: ItemName):
        # clear previous data
        self.sprite.srcs.clear()
        # set new data
        self.item_name = item_name
        self.sprite.spawn_time = game.engine.current_time
        self.sprite.render_dst.is_camera_rendered = True
        self.item_type = ItemType.Misc

        if item_name == ItemName.NA:
            print("Item.set_to - attempted to call with ItemName.NA.")
            exit(1)
        elif item_name == ItemName.Jelly:
            self.sprite.image = game.engine.get_image(ImageName.Items)
            self.sprite.anim_speed = 100
            src0 = create_rect(20, 0, 20, 20)
            self.sprite.srcs.push(src0)
            self.cost = 17
        elif item_name == ItemName.FurPelt:
            self.sprite.image = game.engine.get_image(ImageName.Items)
            self.sprite.anim_speed = 100
            src0 = create_rect(40, 0, 20, 20)
            self.sprite.srcs.push(src0)
            self.cost = 32
        elif item_name == ItemName.Branch:
            self.sprite.image = game.engine.get_image(ImageName.Items)
            self.sprite.anim_speed = 100
            src0 = create_rect(60, 0, 20, 20)
            self.sprite.srcs.push(src0)
            self.cost = 44
        elif item_name == ItemName.Mushroom:
            self.sprite.image = game.engine.get_image(ImageName.Items)
            self.sprite.anim_speed = 100
            src0 = create_rect(80, 0, 20, 20)
            self.sprite.srcs.push(src0)
            self.cost = 38
        elif item_name == ItemName.BatWing:
            self.sprite.image = game.engine.get_image(ImageName.Items)
            self.sprite.anim_speed = 100
            src0 = create_rect(100, 0, 20, 20)
            self.sprite.srcs.push(src0)
            self.cost = 27
        elif item_name == ItemName.Apple:
            self.item_type = ItemType.Useable
            self.sprite.image = game.engine.get_image(ImageName.Items)
            self.sprite.anim_speed = 100
            src0 = create_rect(120, 0, 20, 20)
            self.sprite.srcs.push(src0)
            self.cost = 50
        else:
            item_name_as_int = cast(item_name, "int")
            print("Item.set_to. Item name not handled. ItemName:", item_name_as_int)
            exit(1)
