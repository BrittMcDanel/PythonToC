from ct.src.constants import *
from ct.src.base_types import SDL_TexturePtr


class Image:
    def __init__(self):
        self.image_name: ImageName = None
        self.texture: SDL_TexturePtr = None


def image_create(image_name, texture):
    image = Image
    image.image_name = image_name
    image.texture = texture
    return image
