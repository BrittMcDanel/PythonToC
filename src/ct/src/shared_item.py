from ct.src.engine import SDL_RenderCopy, Engine
from ct.src.image import *
from ct.src.utils import SDL_Rect, RenderDst, create_rect, rects_are_equal, set_scaled_rect, set_scaled_rect_with_camera
from ct.src.image import Image
from ct.src.ct_array import Array
from ct.src.base_types import addr, Uint32, array_capacity, mod, ItemPtr, last_enum_int, cast
from ct.src.constants import ItemName
from ct.src.item import Item
# weak imports
from ct.src.game import Game


class ItemDB:
    def __init__(self):
        self.items: Array[Item] = Array[Item](200)

    def init(self, game: Game):
        self.items.size = array_capacity(self.items)
        last_enum_idx = last_enum_int(ItemName)
        if last_enum_idx > self.items.size - 1:
            print(
                "ItemDB.init - ItemName's last enum idx is > items capacity.")
            exit(1)
        # skip NA by starting at 1
        for i in range(1, last_enum_idx):
            item_name = cast(i, "ItemName")
            game.temp_item.set_to(game, item_name)
            self.items[i] = game.temp_item


class SharedItem:
    def __init__(self):
        self.item: ItemPtr = None
        self.render_dst: RenderDst = None
        self.quantity: int = None
        self.drop_chance: int = None
        self.current_frame_idx: int = 0
        self.spawn_time: Uint32 = None
        self.handle: int = None
        self.in_use_in_pool: bool = None

    def init(self, game: Game, handle: int):
        self.handle = handle
        self.in_use_in_pool = False

    def update(self, game: Game):
        if self.item == None:
            print("Item.update - item is None.")
            exit(1)
        self.current_frame_idx = game.get_current_frame(
            self.item.sprite.srcs.size, self.item.sprite.anim_speed, self.spawn_time)
        src = self.item.sprite.srcs.at(self.current_frame_idx)
        self.render_dst.dst.w = src.w
        self.render_dst.dst.h = src.h
        self.render_dst.update(game.engine.camera.dst, game.engine.scale)

    def draw(self, game: Game):
        src = self.item.sprite.srcs.at(self.current_frame_idx)
        SDL_RenderCopy(game.engine.renderer, self.item.sprite.image.texture,
                       src, self.render_dst.scaled_dst)

    def set_to(self, game: Game, item_name: ItemName, quantity: int, drop_chance: int):
        if item_name == ItemName.NA:
            print("SharedItem.set_to. Cannot set to ItemName.NA.")
            exit(1)
        if drop_chance < 0 or drop_chance > 100:
            print(
                "SharedItem.set_to. Item drop chance must be >= 0 and <= 100, found drop chance:", drop_chance)
            exit(1)
        item_name_as_int = cast(item_name, "int")
        self.item = game.item_db.items.at(item_name_as_int)
        self.quantity = quantity
        self.drop_chance = drop_chance
        self.render_dst.is_camera_rendered = True
        self.current_frame_idx = 0
        self.spawn_time = game.engine.current_time
