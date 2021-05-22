from typing import Any
from ct.src.engine import Engine, engine_init, engine_test
from ct.src.ct_array import *
from ct.src.base_types import Array
from ct.src.constants import *
from ct.src.game_database import *
from typing import Any


class SceneMap:
    def __init__(self):
        self.game_database: GameDatabase = None
