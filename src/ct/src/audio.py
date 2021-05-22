from ct.src.ct_array import *
from ct.src.constants import *
from ct.src.utils import SDL_Rect
from ct.src.base_types import Array, Mix_MusicPtr, Mix_ChunkPtr


class BGMAudio:
    def __init__(self):
        self.audio_name: BGMAudioName = None
        self.audio: Mix_MusicPtr = None


class SEAudio:
    def __init__(self):
        self.audio_name: SEAudioName = None
        self.audio: Mix_ChunkPtr = None
