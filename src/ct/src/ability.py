from ct.src.engine import SDL_RenderCopy
from ct.src.image import *
from ct.src.utils import SDL_Point, SDL_Rect, Range, create_point, create_rect, set_scaled_rect, set_scaled_rect_with_camera
from ct.src.image import Image
from ct.src.ct_array import Array
from ct.src.base_types import Uint32, addr, Uint64, cast
from ct.src.sprite import Sprite
from ct.src.constants import AbilityName, ImageName
# weak imports
from ct.src.game import Game


class AbilityStats:
    def __init__(self):
        self.damage: Uint64 = None
        self.range: int = None
        self.max_skill_points: int = None


class Ability:
    def __init__(self):
        self.ability_name: AbilityName = None
        self.stats: AbilityStats = None
        self.sprite: Sprite = None
        self.portrait: Sprite = None
        self.is_projectile: bool = None
        self.projectile_speed: float = None
        self.start_offset: SDL_Point = None
        self.delay: Uint32 = None
        self.handle: int = None
        self.in_use_in_pool: bool = None

    def init(self, game: Game, handle: int):
        self.handle = handle
        self.in_use_in_pool = False

    def update(self, game: Game):
        self.sprite.update(game)

    def draw(self, game: Game):
        self.sprite.draw(game)

    def set_to(self, game: Game, ability_name: AbilityName):
        # clear previous ability data
        self.sprite.srcs.clear()
        self.portrait.srcs.clear()
        # set new data
        self.ability_name = ability_name
        self.sprite.spawn_time = game.engine.current_time
        self.sprite.render_dst.is_camera_rendered = True
        self.sprite.image = game.engine.get_image(ImageName.Abilities)
        self.portrait.image = game.engine.get_image(ImageName.Items)

        if ability_name == AbilityName.NA:
            print("Ability.set_to - attempted to call with AbilityName.NA.")
            exit(1)
        elif ability_name == AbilityName.MeleeAttack:
            self.sprite.anim_speed = 60
            self.is_projectile = False
            self.stats.damage = 20
            self.stats.range = 30
            self.stats.max_skill_points = 10
            portrait_src = create_rect(20, 20, 20, 20)
            self.portrait.srcs.push(portrait_src)
            x = 0
            w = 30
            for i in range(8):
                src = create_rect(x, 32, w, 30)
                self.sprite.srcs.push(src)
                x += w
        elif ability_name == AbilityName.Fire:
            self.sprite.anim_speed = 100
            self.is_projectile = True
            self.projectile_speed = 2.0
            self.start_offset = create_point(0, -30)
            self.delay = 500
            self.stats.damage = 20
            self.stats.range = 100
            self.stats.max_skill_points = 10
            portrait_src = create_rect(0, 20, 20, 20)
            self.portrait.srcs.push(portrait_src)
            src0 = create_rect(64, 0, 16, 21)
            src1 = create_rect(80, 0, 16, 21)
            src2 = create_rect(96, 0, 16, 21)
            self.sprite.srcs.push(src0)
            self.sprite.srcs.push(src1)
            self.sprite.srcs.push(src2)
        else:
            ability_name_as_int = cast(ability_name, "int")
            print("Ability.set_to. Ability name not handled. AbilityName:",
                  ability_name_as_int)
            exit(1)
