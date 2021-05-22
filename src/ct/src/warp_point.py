from ct.src.engine import SDL_RenderCopy, Engine
from ct.src.image import *
from ct.src.utils import SDL_Rect, RenderDst, SDL_Point, create_rect, tile_point_to_world_point, rects_are_equal, set_scaled_rect, set_scaled_rect_with_camera
from ct.src.image import Image
from ct.src.ct_array import Array
from ct.src.base_types import addr, Uint32, deref, array_capacity, mod, ItemPtr, last_enum_int, cast, AbilityPtr
from ct.src.constants import UnitName, Faction, WarpPointName, ImageName
from ct.src.shared_sprite import SharedSprite
# weak imports
from ct.src.game import Game


class WarpPoint:
    def __init__(self):
        self.warp_point_name: WarpPointName = None
        self.tile_point: SDL_Point = None
        self.tile_point_move_grid: SDL_Point = None
        self.warp_to_tile_point: SDL_Point = None
        self.warp_to_tile_point_move_grid: SDL_Point = None
        self.warp_to_map_handle: int = None
        self.sprite: SharedSprite = None

    def set(self, game: Game, warp_point_name: WarpPointName, tile_point: SDL_Point, warp_to_tile_point: SDL_Point, warp_to_map_handle: int):
        self.warp_point_name = warp_point_name
        self.tile_point = deref(tile_point)
        self.tile_point_move_grid.x = self.tile_point.x * game.move_grid_ratio
        self.tile_point_move_grid.y = self.tile_point.y * game.move_grid_ratio
        self.warp_to_tile_point = deref(warp_to_tile_point)
        self.warp_to_tile_point_move_grid.x = self.warp_to_tile_point.x
        self.warp_to_tile_point_move_grid.y = self.warp_to_tile_point.y
        self.warp_to_tile_point_move_grid.x *= game.move_grid_ratio
        self.warp_to_tile_point_move_grid.y *= game.move_grid_ratio
        self.warp_to_map_handle = warp_to_map_handle
        world_point = tile_point_to_world_point(
            self.tile_point_move_grid, game.move_grid_tile_size)
        self.sprite.render_dst.dst.x = world_point.x
        self.sprite.render_dst.dst.y = world_point.y

        if warp_point_name == WarpPointName.Standard:
            src = create_rect(0, 20, 40, 40)
            self.sprite.shared_srcs = game.sprite_db.find(
                game, ImageName.Tiles, src)
            self.sprite.anim_speed = 100
            self.sprite.render_dst.is_camera_rendered = True
        elif warp_point_name == WarpPointName.Town:
            src = create_rect(20, 0, 20, 20)
            self.sprite.shared_srcs = game.sprite_db.find(
                game, ImageName.Tiles, src)
            self.sprite.anim_speed = 100
            self.sprite.render_dst.is_camera_rendered = True
        elif warp_point_name == WarpPointName.Forest:
            src = create_rect(40, 0, 20, 20)
            self.sprite.shared_srcs = game.sprite_db.find(
                game, ImageName.Tiles, src)
            self.sprite.anim_speed = 100
            self.sprite.render_dst.is_camera_rendered = True
