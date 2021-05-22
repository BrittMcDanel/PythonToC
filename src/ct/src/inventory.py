from ct.src.engine import SDL_RenderCopy
from ct.src.image import *
from ct.src.utils import SDL_Point, SDL_Rect, create_point, tile_point_to_world_point, create_rect, get_move_grid_size_dims, set_scaled_rect, set_scaled_rect_with_camera
from ct.src.image import Image
from ct.src.ct_array import Array
from ct.src.base_types import Uint32, addr, Uint64, array_capacity, cast
from ct.src.sprite import Sprite
from ct.src.constants import ItemName, ItemType
from ct.src.shared_item import SharedItem
# weak imports
from ct.src.game import Game


class InventorySlot:
    def __init__(self):
        self.shared_item: SharedItem = None
        self.slot_is_empty: bool = None


class Inventory:
    def __init__(self):
        self.slots: Array[InventorySlot] = Array[InventorySlot](50)

    def init(self):
        self.slots.size = array_capacity(self.slots)
        # zero'd out memory will set slot is empty to false, it is initially true.
        for slot in self.slots:
            slot.slot_is_empty = True

    def update(self, game: Game):
        for slot in self.slots:
            if slot.slot_is_empty:
                continue
            slot.shared_item.update(game)

    def draw(self, game: Game):
        for slot in self.slots:
            if slot.slot_is_empty:
                continue
            slot.shared_item.draw(game)

    def next_empty_slot_handle(self) -> int:
        for i, slot in enumerate(self.slots):
            if slot.slot_is_empty:
                return i
        return -1

    def add_item(self, game: Game, item_name: ItemName, quantity: int):
        for slot in self.slots:
            if slot.slot_is_empty:
                continue
            if slot.shared_item.item.item_name == item_name:
                slot.shared_item.quantity += quantity
                return
        # item not found, add it
        empty_handle = self.next_empty_slot_handle()
        if empty_handle == -1:
            print("Inventory is full. cannot add item.")
        else:
            empty_slot = self.slots.at(empty_handle)
            empty_slot.shared_item.set_to(game, item_name, quantity, 0)
            empty_slot.slot_is_empty = False

    def remove_item(self, item_name: ItemName, quantity: int):
        for slot in self.slots:
            if slot.slot_is_empty:
                continue
            if slot.shared_item.item.item_name == item_name:
                slot.shared_item.quantity -= quantity
                if slot.quantity <= 0:
                    slot.slot_is_empty = True

    def clear_slot(self, slot_idx: int):
        slot = self.slots.at(slot_idx)
        slot.slot_is_empty = True

    def has_merchant_sellable_items(self) -> bool:
        for slot in self.slots:
            if slot.slot_is_empty:
                continue
            if slot.shared_item.item.item_type == ItemType.Useable:
                return True
        return False

    def inventory_is_empty(self) -> bool:
        for slot in self.slots:
            if slot.slot_is_empty:
                continue
            return False
        return True
