from ct.src.engine import SDL_RenderCopy
from ct.src.image import *
from ct.src.utils import SDL_Point, SDL_Rect, create_point, rect_contains_point, tile_point_to_world_point, create_rect, get_move_grid_size_dims, set_scaled_rect, set_scaled_rect_with_camera
from ct.src.image import Image
from ct.src.ct_array import Array
from ct.src.base_types import Uint32, addr, Uint64, cast, deref
from ct.src.sprite import Sprite
from ct.src.constants import BuildingName, BuildingType, ImageName
from ct.src.input_events import InputEvents
# weak imports
from ct.src.game import Game


class Building:
    def __init__(self):
        self.building_name: BuildingName = None
        self.building_type: BuildingType = None
        self.tile_point_hit_box: SDL_Rect = None
        self.door_tile_point: SDL_Point = None
        self.sprite: Sprite = None
        self.is_shop: bool = None
        self.input_events: InputEvents = None
        self.handle: int = None
        self.in_use_in_pool: bool = None

    def init(self, game: Game, handle: int):
        self.handle = handle
        self.in_use_in_pool = False

    def update(self, game: Game):
        self.sprite.update(game)
        # update input events if mouse isn't over ui
        if not(game.world.ui.is_mouse_over_ui):
            # use camera scaled mouse point as the building is camera rendered
            is_mouse_over = rect_contains_point(
                self.sprite.render_dst.dst, game.engine.mouse_point_scaled_with_camera)
            self.input_events.update(game, is_mouse_over)
            if self.input_events.is_click:
                self.on_click(game)

    def draw(self, game: Game):
        self.sprite.draw(game)

    def on_click(self, game: Game):
        if self.building_name == BuildingName.RecruitmentCenter0:
            game.world.ui.recruit_novice_modal.set_visible(True)

    def set_to(self, game: Game, building_name: BuildingName, move_grid_tile_point: SDL_Point):
        self.tile_point_hit_box.x = move_grid_tile_point.x
        self.tile_point_hit_box.y = move_grid_tile_point.y
        world_point = tile_point_to_world_point(
            move_grid_tile_point, game.move_grid_tile_size)
        self.sprite.render_dst.dst.x = world_point.x
        self.sprite.render_dst.dst.y = world_point.y
        # clear previous ability data
        self.sprite.srcs.clear()
        # set new data
        self.building_name = building_name
        self.sprite.spawn_time = game.engine.current_time
        self.sprite.render_dst.is_camera_rendered = True
        self.is_shop = False
        self.building_type = BuildingType.NA
        self.door_tile_point = deref(move_grid_tile_point)

        if building_name == BuildingName.NA:
            print("Building.set_to - attempted to call with AbilityName.NA.")
            exit(1)
        elif building_name == BuildingName.PlayerLeague:
            self.building_type = BuildingType.League
            self.sprite.image = game.engine.get_image(ImageName.Buildings)
            self.sprite.anim_speed = 100
            src_w = 140
            src_h = 200
            move_grid_hit_box_size_dims = get_move_grid_size_dims(
                src_w, src_h, game.move_grid_tile_size)
            self.tile_point_hit_box.w = move_grid_hit_box_size_dims.x
            self.tile_point_hit_box.h = move_grid_hit_box_size_dims.y
            src0 = create_rect(0, 0, src_w, src_h)
            self.sprite.srcs.push(src0)
            self.door_tile_point.x = move_grid_tile_point.x + 30
            self.door_tile_point.y = move_grid_tile_point.y + 80
        elif building_name == BuildingName.Shop0:
            self.building_type = BuildingType.PotionShop
            self.is_shop = True
            self.sprite.image = game.engine.get_image(ImageName.Buildings)
            self.sprite.anim_speed = 100
            src_w = 140
            src_h = 200
            move_grid_hit_box_size_dims = get_move_grid_size_dims(
                src_w, src_h, game.move_grid_tile_size)
            self.tile_point_hit_box.w = move_grid_hit_box_size_dims.x
            self.tile_point_hit_box.h = move_grid_hit_box_size_dims.y
            src0 = create_rect(140, 0, src_w, src_h)
            self.sprite.srcs.push(src0)
            self.door_tile_point.x = move_grid_tile_point.x + 30
            self.door_tile_point.y = move_grid_tile_point.y + 80
        elif building_name == BuildingName.RecruitmentCenter0:
            self.building_type = BuildingType.RecruitmentShop
            self.sprite.image = game.engine.get_image(ImageName.Buildings)
            self.sprite.anim_speed = 100
            src_w = 140
            src_h = 200
            move_grid_hit_box_size_dims = get_move_grid_size_dims(
                src_w, src_h, game.move_grid_tile_size)
            self.tile_point_hit_box.w = move_grid_hit_box_size_dims.x
            self.tile_point_hit_box.h = move_grid_hit_box_size_dims.y
            src0 = create_rect(280, 0, src_w, src_h)
            self.sprite.srcs.push(src0)
            self.door_tile_point.x = move_grid_tile_point.x + 30
            self.door_tile_point.y = move_grid_tile_point.y + 80
        elif building_name == BuildingName.TeleportationStone:
            self.sprite.image = game.engine.get_image(ImageName.Buildings)
            self.sprite.anim_speed = 150
            src_w = 80
            src_h = 160
            move_grid_hit_box_size_dims = get_move_grid_size_dims(
                src_w, src_h, game.move_grid_tile_size)
            self.tile_point_hit_box.w = move_grid_hit_box_size_dims.x
            self.tile_point_hit_box.h = move_grid_hit_box_size_dims.y
            src = create_rect(0, 864, src_w, src_h)
            self.sprite.srcs.push(src)
            for i in range(6):
                src = create_rect(i * src_w, 864, src_w, src_h)
                self.sprite.srcs.push(src)
        else:
            building_name_as_int = cast(building_name, "int")
            print("Building.set_to. Building name not handled. BulidingName:",
                  building_name_as_int)
            exit(1)
