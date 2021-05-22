from ct.src.engine import SDL_RenderCopy, Engine
from ct.src.image import *
from ct.src.utils import SDL_Rect, RenderDst, create_rect, rects_are_equal, set_scaled_rect, set_scaled_rect_with_camera
from ct.src.image import Image
from ct.src.ct_array import Array
from ct.src.base_types import addr, Uint32, array_capacity, mod, ItemPtr, last_enum_int, cast, AbilityPtr
from ct.src.constants import AbilityName
from ct.src.ability import Ability
# weak imports
from ct.src.game import Game


class AbilityDB:
    def __init__(self):
        self.abilities: Array[Ability] = Array[Ability](200)

    def init(self, game: Game):
        self.abilities.size = array_capacity(self.abilities)
        last_enum_idx = last_enum_int(AbilityName)
        if last_enum_idx > self.abilities.size - 1:
            print("AbilityDB.init - AbilityName's last enum idx is > abilities capacity.")
            exit(1)
        # skip NA by starting at 1
        for i in range(1, last_enum_idx):
            ability_name = cast(i, "AbilityName")
            game.temp_ability.set_to(game, ability_name)
            self.abilities[i] = game.temp_ability


class SharedAbility:
    def __init__(self):
        self.ability: AbilityPtr = None
        self.render_dst: RenderDst = None
        self.current_frame_idx: int = 0
        self.spawn_time: Uint32 = None
        self.skill_points: int = None
        self.handle: int = None
        self.in_use_in_pool: bool = None

    def init(self, game: Game, handle: int):
        self.handle = handle
        self.in_use_in_pool = False

    def update(self, game: Game):
        if self.ability == None:
            print("Item.update - item is None.")
            exit(1)
        self.current_frame_idx = game.get_current_frame(
            self.ability.sprite.srcs.size, self.ability.sprite.anim_speed, self.spawn_time)
        src = self.ability.sprite.srcs.at(self.current_frame_idx)
        self.render_dst.dst.w = src.w
        self.render_dst.dst.h = src.h
        self.render_dst.update(game.engine.camera.dst, game.engine.scale)

    def draw(self, game: Game):
        src = self.ability.sprite.srcs.at(self.current_frame_idx)
        SDL_RenderCopy(game.engine.renderer, self.ability.sprite.image.texture,
                       src, self.render_dst.scaled_dst)

    def set_to(self, game: Game, ability_name: AbilityName):
        if ability_name == AbilityName.NA:
            print("SharedAbility.set_to. Cannot set to AbilityName.NA.")
            exit(1)
        ability_name_as_int = cast(ability_name, "int")
        self.ability = game.ability_db.abilities.at(ability_name_as_int)
        self.render_dst.is_camera_rendered = True
        self.current_frame_idx = 0
        self.spawn_time = game.engine.current_time
