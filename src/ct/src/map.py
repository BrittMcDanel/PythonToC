from ct.src.audio import SEAudio
from ct.src.engine import *
from ct.src.image import *
from ct.src.utils import SDL_Point, SDL_Rect, create_color, create_point, create_rect, move_tile_point_to_world_point, rect_contains_rect_margin, tile_point_to_world_point, iso_tile_point_to_world_point, points_are_equal, rect_contains_point, rect_contains_rect
from ct.src.image import Image
from ct.src.ct_array import Array, arr_push, arr_push_value, clear, strcpyfunc, string_cat_literal, string_length, string_set_literal, string_cat
from ct.src.sprite import Sprite
from ct.src.tile import Tile, tile_update, tile_draw
from ct.src.render import RenderSprite
from ct.src.constants import ImageName, HandleType, WarpPointName, UnitName, Faction, SDLK, FontStyle, TextAlignment, TextWordWrap, BGMAudioName, SEAudioName
from ct.src.base_types import cast, char, array_get_buffer, deref
from ct.src.text import TextLG
from ct.src.unit import Unit
from ct.src.tween import TweenXY
from ct.src.ability import Ability
from ct.src.shared_sprite import SharedSprite
from ct.src.warp_point import WarpPoint
# weak imports
from ct.src.game import Game


class Map:
    def __init__(self):
        self.rows: int = None
        self.cols: int = None
        self.move_grid_rows: int = None
        self.move_grid_cols: int = None
        self.tiles: Array[Tile] = Array[Tile](10000)
        self.warp_points: Array[WarpPoint] = Array[WarpPoint](7)
        self.building_handles: Array[int] = Array[int](100)
        self.unit_handles: Array[int] = Array[int](300)
        self.ability_handles: Array[int] = Array[int](300)
        self.item_handles: Array[int] = Array[int](300)
        self.damage_text_handles: Array[int] = Array[int](300)
        self.unit_temporary: Unit = None
        self.is_town_map: bool = None
        self.handle: int = None
        self.in_use_in_pool: bool = None

    def init(self, game: Game, handle: int):
        self.handle = handle
        self.in_use_in_pool = False

    def create_initial(self, game: Game, rows: int, cols: int, is_town_map):
        if rows > game.max_map_size.x:
            print("Map.create_initial. rows is > game.max_map_size.x",
                  "\nrows:", rows, "\nmax_map_size.x", game.max_map_size.x)
            exit(1)
        if cols > game.max_map_size.y:
            print("Map.create_initial. cols is > game.max_map_size.y",
                  "\ncols:", cols, "\nmax_map_size.y", game.max_map_size.y)
            exit(1)
        self.is_town_map = is_town_map
        tile = Tile()
        warp_point = WarpPoint()
        self.rows = rows
        self.cols = cols
        self.move_grid_rows = rows * game.move_grid_ratio
        self.move_grid_cols = cols * game.move_grid_ratio

        for i in range(rows):
            for j in range(cols):
                tile_point = create_point(i, j)
                dst = tile_point_to_world_point(tile_point, game.tile_size)
                src = create_rect(0, 0, 20, 20)
                shared_srcs = game.sprite_db.find(
                    game, ImageName.Tiles, src)
                tile.sprite.shared_srcs = shared_srcs
                tile.sprite.render_dst.dst.x = dst.x
                tile.sprite.render_dst.dst.y = dst.y
                tile.sprite.anim_speed = 100
                tile.sprite.render_dst.is_camera_rendered = True
                self.tiles.push(tile)

        # create some warp points
        if self.handle == 1:
            tile_point = create_point(rows - 2, 15)
            warp_to_tile_point = create_point(10 + 1, 15)
            warp_point.set(game, WarpPointName.Standard,
                           tile_point, warp_to_tile_point, 0)
            self.warp_points.push(warp_point)
        elif self.handle == 2:
            tile_point = create_point(0, 20)
            warp_to_tile_point = create_point(22 - 1, 8)
            warp_point.set(game, WarpPointName.Standard,
                           tile_point, warp_to_tile_point, 0)
            self.warp_points.push(warp_point)
        elif self.handle == 3:
            tile_point = create_point(rows - 2, 15)
            warp_to_tile_point = create_point(32 - 1, 18)
            warp_point.set(game, WarpPointName.Standard,
                           tile_point, warp_to_tile_point, 0)
            self.warp_points.push(warp_point)

        # create some initial units
        if not(self.is_town_map):
            num_enemies = game.engine.get_rand_int(20, 40)
            for i in range(num_enemies):
                unit_handle = game.world.get_handle(HandleType.Unit)
                unit = game.world.units.at(unit_handle)
                rand_unit_enum_int = game.engine.get_rand_int(7, 11)
                rand_unit_name = cast(rand_unit_enum_int, "UnitName")
                unit.set_to(game, rand_unit_name, Faction.Enemy)
                unit.join_map(game, self)
                unit.set_random_spawn_point(game)

    def create_initial_overworld(self, game: Game, rows: int, cols: int):
        if rows > game.max_map_size.x:
            print("Map.create_initial. rows is > game.max_map_size.x",
                  "\nrows:", rows, "\nmax_map_size.x", game.max_map_size.x)
            exit(1)
        if cols > game.max_map_size.y:
            print("Map.create_initial. cols is > game.max_map_size.y",
                  "\ncols:", cols, "\nmax_map_size.y", game.max_map_size.y)
            exit(1)
        self.is_town_map = False
        tile = Tile()
        warp_point = WarpPoint()
        self.rows = rows
        self.cols = cols
        self.move_grid_rows = rows * game.move_grid_ratio
        self.move_grid_cols = cols * game.move_grid_ratio

        for i in range(rows):
            for j in range(cols):
                tile_point = create_point(i, j)
                dst = tile_point_to_world_point(tile_point, game.tile_size)
                src = create_rect(0, 0, 20, 20)
                shared_srcs = game.sprite_db.find(
                    game, ImageName.Tiles, src)
                tile.sprite.shared_srcs = shared_srcs
                tile.sprite.render_dst.dst.x = dst.x
                tile.sprite.render_dst.dst.y = dst.y
                tile.sprite.anim_speed = 100
                tile.sprite.render_dst.is_camera_rendered = True
                self.tiles.push(tile)

        # create warp points
        tile_point = create_point(10, 15)
        warp_to_tile_point = create_point(rows - 2, 15)
        warp_point.set(game, WarpPointName.Forest,
                       tile_point, warp_to_tile_point, 1)
        self.warp_points.push(warp_point)

        tile_point = create_point(22, 8)
        warp_to_tile_point = create_point(0, 20)
        warp_point.set(game, WarpPointName.Town,
                       tile_point, warp_to_tile_point, 2)
        self.warp_points.push(warp_point)

        tile_point = create_point(32, 18)
        warp_to_tile_point = create_point(rows - 2, 15)
        warp_point.set(game, WarpPointName.Forest,
                       tile_point, warp_to_tile_point, 3)
        self.warp_points.push(warp_point)

    def update(self, game: Game):
        # gets called for each map
        return 0

    def update_visible_map(self, game: Game):
        # only gets called for the visible map
        for tile in self.tiles:
            tile.update(game)
        for warp_point in self.warp_points:
            warp_point.sprite.update(game)
        # I don't think every building in world needs to update so I am putting this here for now.
        for i in range(self.building_handles.size):
            building_handle = self.building_handles[i]
            building = game.world.buildings.at(building_handle)
            building.update(game)

    def draw(self, game: Game):
        for tile in self.tiles:
            tile.draw(game)
        for warp_point in self.warp_points:
            warp_point.sprite.draw(game)
        for i in range(self.building_handles.size):
            building_handle = self.building_handles[i]
            building = game.world.buildings.at(building_handle)
            building.draw(game)
        # sort units first before drawing
        self.units_insertion_sort(game)
        for i in range(self.unit_handles.size):
            unit_handle = self.unit_handles[i]
            unit = game.world.units.at(unit_handle)
            # don't draw the unit if its dead
            if not(unit.stats.hp.value_is_at_min()):
                unit.draw(game)
        for i in range(self.item_handles.size):
            item_handle = self.item_handles[i]
            item = game.world.items.at(item_handle)
            item.draw(game)
        for i in range(self.ability_handles.size):
            ability_handle = self.ability_handles[i]
            ability = game.world.abilities.at(ability_handle)
            ability.draw(game)
        for i in range(self.damage_text_handles.size):
            damage_text_handle = self.damage_text_handles[i]
            damage_text = game.world.damage_texts.at(damage_text_handle)
            damage_text.text_draw(game)

    def units_insertion_sort(self, game: Game):
        for i in range(1, self.unit_handles.size, 1):
            key = self.unit_handles[i]
            j = i - 1
            key_j = self.unit_handles[j]
            unit_key = game.world.units.at(key)
            unit_key_j = game.world.units.at(key_j)
            # Move elements of arr[0..i-1], that are
            # greater than key, to one position ahead
            # of their current position
            while j >= 0 and unit_key_j.tile_point_hit_box.y > unit_key.tile_point_hit_box.y:
                next_idx = j + 1
                self.unit_handles[next_idx] = self.unit_handles[j]
                j -= 1
                # check if j is a valid index, i.e >= 0 as it can be less than 0 here.
                if j >= 0:
                    key_j = self.unit_handles[j]
                    unit_key_j = game.world.units.at(key_j)

            next_idx = j + 1
            self.unit_handles[next_idx] = key

    def get_random_merchant_shop_point(self, game: Game, tile_point_hit_box: SDL_Rect) -> SDL_Point:
        iters = 0
        max_iters = 500
        p = create_point(0, 0)
        self_tile_point = create_point(
            tile_point_hit_box.x, tile_point_hit_box.y)
        while iters < max_iters:
            iters += 1
            p.x = game.engine.get_rand_int(0, self.move_grid_rows - 1)
            p.y = game.engine.get_rand_int(0, self.move_grid_cols - 1)
            # always return p for now, maybe later check to see if the merchant shop would overlap
            if points_are_equal(self_tile_point, p):
                continue
            return p

        print("Could not find random unoccupied point.")
        return create_point(0, 0)

    def get_random_town_point(self, game: Game, tile_point_hit_box: SDL_Rect) -> SDL_Point:
        iters = 0
        max_iters = 500
        p = create_point(0, 0)
        self_tile_point = create_point(
            tile_point_hit_box.x, tile_point_hit_box.y)
        while iters < max_iters:
            iters += 1
            p.x = game.engine.get_rand_int(0, self.move_grid_rows - 1)
            p.y = game.engine.get_rand_int(0, self.move_grid_cols - 1)
            # always return p for now, maybe later check to see if the merchant shop would overlap
            if not(points_are_equal(self_tile_point, p)):
                return p

        print("Could not find random unoccupied point.")
        return create_point(0, 0)

    def get_random_unoccupied_move_grid_tile_point(self, game: Game, tile_point_hit_box: SDL_Rect) -> SDL_Point:
        iters = 0
        max_iters = 500
        hit_box_cpy = deref(tile_point_hit_box)
        p = create_point(hit_box_cpy.x, hit_box_cpy.y)
        while iters < max_iters:
            iters += 1
            p.x = game.engine.get_rand_int(0, self.move_grid_rows - 1)
            p.y = game.engine.get_rand_int(0, self.move_grid_cols - 1)
            hit_box_cpy.x = p.x
            hit_box_cpy.y = p.y
            if not(self.unit_occupies_tile_point_move_grid(game, hit_box_cpy, -1)):
                # print("Point found")
                return p

        print("Could not find random unoccupied point.")
        return create_point(0, 0)

    def unit_occupies_tile_point_move_grid(self, game: Game, tile_point_hit_box: SDL_Rect, skip_unit_handle: int) -> bool:
        for i in range(self.unit_handles.size):
            unit_handle = self.unit_handles[i]
            if unit_handle == skip_unit_handle:
                continue
            unit = game.world.units.at(unit_handle)
            if rect_contains_rect(tile_point_hit_box, unit.tile_point_hit_box):
                # print("collide", tile_point_hit_box.x, tile_point_hit_box.y, tile_point_hit_box.w, tile_point_hit_box.h, "-", unit.tile_point_hit_box.x, unit.tile_point_hit_box.y,
                #      unit.tile_point_hit_box.w, unit.tile_point_hit_box.h)
                return True
        return False

    def unit_occupies_tile_point_move_grid_point(self, game: Game, tile_point: SDL_Point, skip_unit_handle: int) -> bool:
        for i in range(self.unit_handles.size):
            unit_handle = self.unit_handles[i]
            if unit_handle == skip_unit_handle:
                continue
            unit = game.world.units.at(unit_handle)
            if rect_contains_point(unit.tile_point_hit_box, tile_point):
                return True
        return False

    def in_bounds(self, p: SDL_Point) -> bool:
        return p.x >= 0 and p.x <= self.rows - 1 and p.y >= 0 and p.y <= self.cols - 1

    def in_bounds_move_grid(self, p: SDL_Point) -> bool:
        return p.x >= 0 and p.x <= self.move_grid_rows - 1 and p.y >= 0 and p.y <= self.move_grid_cols - 1

    def cleanup_before_being_removed(self, game: Game):
        # called before the map is removed.
        # release all unit handles
        for i in range(self.unit_handles.size):
            unit_handle = self.unit_handles[i]
            game.world.release_handle(HandleType.Unit, unit_handle)
        # all unit handles removed, now clear the unit_handles arr
        self.unit_handles.clear()
        # reset map data
        self.rows = 0
        self.cols = 0
        self.tiles.clear()
