from typing import Any
from ct.src.engine import Engine, engine_clear, engine_free, engine_present
from ct.src.ct_array import *
from ct.src.base_types import Array, malloc, free
from ct.src.constants import *
from ct.src.game import *
from typing import Any


def main():
    game = malloc(Game(), 1)
    game.start()
    while (not(game.engine.quit)):
        engine_clear(game.engine)
        game.engine.update()
        game.update()
        game.draw()
        engine_present(game.engine)
    engine_free(game.engine)
    free(game)
