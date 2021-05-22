from ct.src.engine import SDL_RenderCopy
from ct.src.utils import SDL_Point, SDL_Rect, RenderDst, create_point, create_rect, set_scaled_rect, set_scaled_rect_with_camera
from ct.src.constants import UnitAnimState, UnitName, ImageName
from ct.src.image import Image
from ct.src.ct_array import Array
from ct.src.base_types import addr, Uint32, mod, cast
# weak imports
from ct.src.game import Game


class UnitSprite:
    def __init__(self):
        self.image: Image = None
        self.current_src: SDL_Rect = None
        self.render_dst: RenderDst = None
        self.anim_state: UnitAnimState = None
        self.hit_box_size: SDL_Point = None
        self.idle_down: Array[SDL_Rect] = Array[SDL_Rect](10)
        self.cast_down: Array[SDL_Rect] = Array[SDL_Rect](10)
        self.sit_down: Array[SDL_Rect] = Array[SDL_Rect](3)
        self.overworld_idle_down: Array[SDL_Rect] = Array[SDL_Rect](10)
        self.idle_anim_speed: Uint32 = None
        self.cast_anim_speed: Uint32 = None
        self.sit_anim_speed: Uint32 = None
        self.overworld_idle_anim_speed: Uint32 = None
        self.spawn_time: Uint32 = None
        self.anim_finish_time: Uint32 = None
        self.playing_one_shot_anim: bool = None

    def update(self, game: Game, on_overworld_map: bool):
        # anim is over, go back to idle
        if self.playing_one_shot_anim and game.engine.current_time > self.anim_finish_time:
            self.playing_one_shot_anim = False
            self.anim_state = UnitAnimState.Idle
        self.set_current_src(game, on_overworld_map)
        self.render_dst.dst.w = self.current_src.w
        self.render_dst.dst.h = self.current_src.h
        self.render_dst.update(game.engine.camera.dst, game.engine.scale)

    def draw(self, game: Game):
        SDL_RenderCopy(game.engine.renderer, self.image.texture,
                       self.current_src, self.render_dst.scaled_dst)

    def draw_idle_at(self, game: Game, unscaled_dst: SDL_Rect):
        # for when ui wants to draw as unit somewhere
        idle_src_0 = self.idle_down.at(0)
        unscaled_dst.w = idle_src_0.w
        unscaled_dst.h = idle_src_0.h
        set_scaled_rect(unscaled_dst, game.engine.scale)
        SDL_RenderCopy(game.engine.renderer, self.image.texture,
                       idle_src_0, unscaled_dst)

    def play_animation(self, game: Game, anim_state: UnitAnimState):
        # one shot anims will go back to idle automatically, so you don't need to set them again.
        self.anim_state = anim_state
        if self.anim_state == UnitAnimState.NA:
            print("UnitSprite.play_animation. Animation is NA.")
            exit(1)
        elif self.anim_state == UnitAnimState.Cast:
            self.playing_one_shot_anim = True
            anim_duration = cast(self.cast_down.size *
                                 self.cast_anim_speed, "Uint32")
            self.anim_finish_time = game.engine.current_time + anim_duration

    def set_current_src(self, game: Game, on_overworld_map: bool):
        if self.idle_anim_speed == 0 or self.cast_anim_speed == 0 or self.sit_anim_speed == 0 or self.overworld_idle_anim_speed == 0:
            print("Unitsprite.set_current_src - an anim speed is 0.")
            exit(1)
        alive_time = game.engine.current_time - self.spawn_time
        if self.anim_state == UnitAnimState.NA:
            print("UnitSprite.set_current_src - AnimState is NA.")
            exit(1)
        elif self.anim_state == UnitAnimState.Idle:
            if self.idle_down.size == 0:
                exit(1)
            if on_overworld_map:
                current_frame = mod(
                    alive_time / self.overworld_idle_anim_speed, self.overworld_idle_down.size)
                self.current_src = self.overworld_idle_down[current_frame]
            else:
                current_frame = mod(
                    alive_time / self.idle_anim_speed, self.idle_down.size)
                self.current_src = self.idle_down[current_frame]
        elif self.anim_state == UnitAnimState.Cast:
            if self.cast_down.size == 0:
                exit(1)
            current_frame = mod(
                alive_time / self.cast_anim_speed, self.cast_down.size)
            self.current_src = self.cast_down[current_frame]
        elif self.anim_state == UnitAnimState.Sit:
            if self.sit_down.size == 0:
                exit(1)
            current_frame = mod(
                alive_time / self.sit_anim_speed, self.sit_down.size)
            self.current_src = self.sit_down[current_frame]

    def set_to(self, game: Game, unit_name: UnitName):
        self.anim_state = UnitAnimState.Idle
        self.idle_down.clear()
        self.cast_down.clear()
        self.sit_down.clear()
        self.overworld_idle_down.clear()
        self.render_dst.is_camera_rendered = True
        # should this be set this here, should be fine I think.
        self.spawn_time = game.engine.current_time
        self.idle_anim_speed = 1
        self.cast_anim_speed = 1
        self.sit_anim_speed = 1
        self.overworld_idle_anim_speed = 1

        # hit_boxes need to be multiples of game.move_tile_grid_size
        if unit_name == UnitName.RandomTownsPerson0:
            self.image = game.engine.get_image(ImageName.Units)
            self.idle_anim_speed = 130
            self.cast_anim_speed = 240
            self.sit_anim_speed = 100
            self.overworld_idle_anim_speed = 130
            self.hit_box_size = create_point(20, 40)
            idle_down_src0 = create_rect(260, 0, 20, 40)
            self.idle_down.push(idle_down_src0)
        elif unit_name == UnitName.Merchant:
            self.image = game.engine.get_image(ImageName.Units)
            self.idle_anim_speed = 130
            self.cast_anim_speed = 240
            self.sit_anim_speed = 100
            self.overworld_idle_anim_speed = 130
            self.hit_box_size = create_point(20, 40)
            idle_down_src0 = create_rect(220, 0, 20, 40)
            self.idle_down.push(idle_down_src0)
            cast_down_src0 = create_rect(80, 0, 20, 40)
            self.cast_down.push(cast_down_src0)
            sit_down_src0 = create_rect(240, 0, 20, 40)
            self.sit_down.push(sit_down_src0)
            overworld_idle_down_src0 = create_rect(20, 40, 20, 20)
            overworld_idle_down_src1 = create_rect(40, 40, 20, 20)
            overworld_idle_down_src2 = create_rect(60, 40, 20, 20)
            self.overworld_idle_down.push(overworld_idle_down_src0)
            self.overworld_idle_down.push(overworld_idle_down_src1)
            self.overworld_idle_down.push(overworld_idle_down_src0)
            self.overworld_idle_down.push(overworld_idle_down_src2)
        elif unit_name == UnitName.Explorer:
            self.image = game.engine.get_image(ImageName.Units)
            self.idle_anim_speed = 130
            self.cast_anim_speed = 240
            self.sit_anim_speed = 100
            self.overworld_idle_anim_speed = 130
            self.hit_box_size = create_point(20, 40)
            idle_down_src0 = create_rect(0, 0, 20, 40)
            idle_down_src1 = create_rect(40, 0, 20, 40)
            idle_down_src2 = create_rect(0, 0, 20, 40)
            idle_down_src3 = create_rect(60, 0, 20, 40)
            self.idle_down.push(idle_down_src0)
            self.idle_down.push(idle_down_src1)
            self.idle_down.push(idle_down_src2)
            self.idle_down.push(idle_down_src3)
            cast_down_src0 = create_rect(80, 0, 20, 40)
            self.cast_down.push(cast_down_src0)
            sit_down_src0 = create_rect(200, 0, 20, 40)
            self.sit_down.push(sit_down_src0)
            overworld_idle_down_src0 = create_rect(20, 40, 20, 20)
            overworld_idle_down_src1 = create_rect(40, 40, 20, 20)
            overworld_idle_down_src2 = create_rect(60, 40, 20, 20)
            self.overworld_idle_down.push(overworld_idle_down_src0)
            self.overworld_idle_down.push(overworld_idle_down_src1)
            self.overworld_idle_down.push(overworld_idle_down_src0)
            self.overworld_idle_down.push(overworld_idle_down_src2)
        elif unit_name == UnitName.Mage:
            self.image = game.engine.get_image(ImageName.Units)
            self.idle_anim_speed = 100
            self.cast_anim_speed = 240
            self.sit_anim_speed = 100
            self.overworld_idle_anim_speed = 130
            self.hit_box_size = create_point(20, 40)
            idle_down_src0 = create_rect(20, 0, 20, 40)
            self.idle_down.push(idle_down_src0)
            cast_down_src0 = create_rect(100, 0, 20, 40)
            self.cast_down.push(cast_down_src0)
            sit_down_src0 = create_rect(200, 0, 20, 40)
            self.sit_down.push(sit_down_src0)
            overworld_idle_down_src0 = create_rect(80, 40, 20, 20)
            overworld_idle_down_src1 = create_rect(100, 40, 20, 20)
            overworld_idle_down_src2 = create_rect(120, 40, 20, 20)
            self.overworld_idle_down.push(overworld_idle_down_src0)
            self.overworld_idle_down.push(overworld_idle_down_src1)
            self.overworld_idle_down.push(overworld_idle_down_src0)
            self.overworld_idle_down.push(overworld_idle_down_src2)
        elif unit_name == UnitName.Wizard:
            self.image = game.engine.get_image(ImageName.Units)
            self.idle_anim_speed = 100
            self.cast_anim_speed = 240
            self.sit_anim_speed = 100
            self.overworld_idle_anim_speed = 130
            self.hit_box_size = create_point(20, 40)
            idle_down_src0 = create_rect(120, 0, 20, 40)
            self.idle_down.push(idle_down_src0)
            cast_down_src0 = create_rect(160, 0, 20, 40)
            self.cast_down.push(cast_down_src0)
            sit_down_src0 = create_rect(200, 0, 20, 40)
            self.sit_down.push(sit_down_src0)
            overworld_idle_down_src0 = create_rect(20, 40, 20, 20)
            overworld_idle_down_src1 = create_rect(40, 40, 20, 20)
            overworld_idle_down_src2 = create_rect(60, 40, 20, 20)
            self.overworld_idle_down.push(overworld_idle_down_src0)
            self.overworld_idle_down.push(overworld_idle_down_src1)
            self.overworld_idle_down.push(overworld_idle_down_src0)
            self.overworld_idle_down.push(overworld_idle_down_src2)
        elif unit_name == UnitName.Scholar:
            self.image = game.engine.get_image(ImageName.Units)
            self.idle_anim_speed = 100
            self.cast_anim_speed = 240
            self.sit_anim_speed = 100
            self.overworld_idle_anim_speed = 130
            self.hit_box_size = create_point(20, 40)
            idle_down_src0 = create_rect(140, 0, 20, 40)
            self.idle_down.push(idle_down_src0)
            cast_down_src0 = create_rect(180, 0, 20, 40)
            self.cast_down.push(cast_down_src0)
            sit_down_src0 = create_rect(200, 0, 20, 40)
            self.sit_down.push(sit_down_src0)
            overworld_idle_down_src0 = create_rect(20, 40, 20, 20)
            overworld_idle_down_src1 = create_rect(40, 40, 20, 20)
            overworld_idle_down_src2 = create_rect(60, 40, 20, 20)
            self.overworld_idle_down.push(overworld_idle_down_src0)
            self.overworld_idle_down.push(overworld_idle_down_src1)
            self.overworld_idle_down.push(overworld_idle_down_src0)
            self.overworld_idle_down.push(overworld_idle_down_src2)
        elif unit_name == UnitName.Slime:
            self.image = game.engine.get_image(ImageName.Units)
            self.idle_anim_speed = 100
            self.cast_anim_speed = 300
            self.sit_anim_speed = 100
            self.hit_box_size = create_point(20, 18)
            idle_down_src0 = create_rect(0, 40, 20, 18)
            self.idle_down.push(idle_down_src0)
            self.cast_down.push(idle_down_src0)
        elif unit_name == UnitName.Bunny:
            self.image = game.engine.get_image(ImageName.Units)
            self.idle_anim_speed = 100
            self.cast_anim_speed = 300
            self.sit_anim_speed = 100
            self.hit_box_size = create_point(20, 28)
            idle_down_src0 = create_rect(0, 64, 20, 28)
            self.idle_down.push(idle_down_src0)
            self.cast_down.push(idle_down_src0)
        elif unit_name == UnitName.Bat:
            self.image = game.engine.get_image(ImageName.Units)
            self.idle_anim_speed = 100
            self.cast_anim_speed = 300
            self.sit_anim_speed = 100
            self.hit_box_size = create_point(20, 26)
            idle_down_src0 = create_rect(0, 96, 20, 26)
            self.idle_down.push(idle_down_src0)
            self.cast_down.push(idle_down_src0)
        elif unit_name == UnitName.Stump:
            self.image = game.engine.get_image(ImageName.Units)
            self.idle_anim_speed = 100
            self.cast_anim_speed = 300
            self.sit_anim_speed = 100
            self.hit_box_size = create_point(28, 38)
            idle_down_src0 = create_rect(0, 128, 28, 37)
            self.idle_down.push(idle_down_src0)
            self.cast_down.push(idle_down_src0)
        elif unit_name == UnitName.Shroomed:
            self.image = game.engine.get_image(ImageName.Units)
            self.idle_anim_speed = 100
            self.cast_anim_speed = 300
            self.sit_anim_speed = 100
            self.hit_box_size = create_point(26, 34)
            idle_down_src0 = create_rect(0, 165, 26, 33)
            self.idle_down.push(idle_down_src0)
            self.cast_down.push(idle_down_src0)
        else:
            unit_name_as_int = cast(unit_name, "int")
            print("UnitSprite.set_to. Unit name not handled. UnitName:",
                  unit_name_as_int)
            exit(1)
