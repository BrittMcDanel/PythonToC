from ct.src.components import CPosition, CSprite
from ct.src.ct_array import arr_next, arr_next_handle
from ct.src.game_object import GameObject
from ct.src.image import *
from ct.src.base_types import Array
from ct.src.base_types import addr
# weak imports
from ct.src.game import Game
from ct.src.engine import SDL_RenderCopy


class GameDatabase:
    def __init__(self):
        self.game_objects: Array[GameObject] = Array[GameObject](5000)
        self.c_positions: Array[CPosition] = Array[CPosition](3000)
        self.c_sprites: Array[CSprite] = Array[CSprite](3000)
        self.render_sprite_table: Array[GameObject] = Array[GameObject](5000)


def render_system(game: Game, game_database: GameDatabase):
    for go in game_database.render_sprite_table:
        position = addr(game_database.c_positions[go.c_position_idx])
        sprite = addr(game_database.c_sprites[go.c_sprite_idx])
        SDL_RenderCopy(game.engine.renderer, sprite.src, position.dst)


def add_position_component(db: GameDatabase, go: GameObject):
    if go.c_position_idx != -1:
        exit(1)
    position_idx = arr_next_handle(db.c_positions)
    position = addr(db.c_positions[position_idx])
    position.go_idx = go.go_idx
    go.c_position_idx = position_idx
    return position_idx


def add_sprite_component(db: GameDatabase, go: GameObject):
    if go.c_sprite_idx != -1:
        exit(1)
    sprite_idx = arr_next_handle(db.c_sprites)
    sprite = addr(db.c_sprites[sprite_idx])
    sprite.go_idx = go.go_idx
    go.c_sprite_idx = sprite_idx
    return sprite_idx
