from ct.src.engine import SDL_RenderCopy, Engine
from ct.src.image import *
from ct.src.utils import SDL_Rect, RenderDst, create_rect, rects_are_equal, set_scaled_rect, set_scaled_rect_with_camera
from ct.src.image import Image
from ct.src.ct_array import Array
from ct.src.base_types import addr, Uint32, array_capacity, mod, SpriteSrcsPtr, cast
from ct.src.constants import ImageName
# weak imports
from ct.src.game import Game


class SpriteSrcs:
    def __init__(self):
        self.image: Image = None
        self.srcs: Array[SDL_Rect] = Array[SDL_Rect](10)


class SpriteDB:
    def __init__(self):
        self.srcs: Array[SpriteSrcs] = Array[SpriteSrcs](200)

    def init(self, game: Game):
        # do lookup based on image name and first src in srcs to find the appropriate src arr
        #unit_image = game.engine.get_image(ImageName.Units)
        tile_image = game.engine.get_image(ImageName.Tiles)
        ui_image = game.engine.get_image(ImageName.UI)
        item_image = game.engine.get_image(ImageName.Items)
        # --- tiles ---
        # entry
        shared_srcs = self.srcs.next()
        shared_srcs.image = tile_image
        src0 = create_rect(0, 0, 20, 20)
        shared_srcs.srcs.push(src0)
        # entry
        shared_srcs = self.srcs.next()
        shared_srcs.image = tile_image
        src0 = create_rect(0, 20, 40, 40)
        shared_srcs.srcs.push(src0)
        src0 = create_rect(40, 20, 40, 40)
        shared_srcs.srcs.push(src0)
        # entry
        shared_srcs = self.srcs.next()
        shared_srcs.image = tile_image
        src0 = create_rect(20, 0, 20, 20)
        shared_srcs.srcs.push(src0)
        # entry
        shared_srcs = self.srcs.next()
        shared_srcs.image = tile_image
        src0 = create_rect(40, 0, 20, 20)
        shared_srcs.srcs.push(src0)
        # --- items ---
        # entry
        shared_srcs = self.srcs.next()
        shared_srcs.image = item_image
        src0 = create_rect(20, 40, 20, 20)
        shared_srcs.srcs.push(src0)
        # entry
        shared_srcs = self.srcs.next()
        shared_srcs.image = item_image
        src0 = create_rect(0, 60, 16, 16)
        shared_srcs.srcs.push(src0)
        # entry
        guild_capacity = array_capacity(game.world.guilds)
        icon_dims = 16
        for i in range(guild_capacity):
            shared_srcs = self.srcs.next()
            shared_srcs.image = item_image
            src0 = create_rect(i * icon_dims, 60, icon_dims, icon_dims)
            shared_srcs.srcs.push(src0)
        # --- ui ---
        # entry
        shared_srcs = self.srcs.next()
        shared_srcs.image = ui_image
        src0 = create_rect(0, 0, 60, 30)
        shared_srcs.srcs.push(src0)
        # entry
        shared_srcs = self.srcs.next()
        shared_srcs.image = ui_image
        src0 = create_rect(0, 32, 180, 165)
        shared_srcs.srcs.push(src0)
        # entry
        shared_srcs = self.srcs.next()
        shared_srcs.image = ui_image
        src0 = create_rect(0, 1688, 640, 360)
        shared_srcs.srcs.push(src0)
        # entry
        shared_srcs = self.srcs.next()
        shared_srcs.image = ui_image
        src0 = create_rect(640, 1786, 544, 262)
        shared_srcs.srcs.push(src0)
        # entry
        shared_srcs = self.srcs.next()
        shared_srcs.image = ui_image
        src0 = create_rect(0, 1664, 10, 10)
        shared_srcs.srcs.push(src0)
        # entry
        shared_srcs = self.srcs.next()
        shared_srcs.image = ui_image
        src0 = create_rect(10, 1664, 10, 10)
        shared_srcs.srcs.push(src0)
        # entry
        shared_srcs = self.srcs.next()
        shared_srcs.image = ui_image
        src0 = create_rect(0, 240, 80, 40)
        shared_srcs.srcs.push(src0)
        # entry
        shared_srcs = self.srcs.next()
        shared_srcs.image = ui_image
        src0 = create_rect(0, 288, 24, 24)
        shared_srcs.srcs.push(src0)
        # entry
        shared_srcs = self.srcs.next()
        shared_srcs.image = ui_image
        src0 = create_rect(24, 288, 24, 24)
        shared_srcs.srcs.push(src0)
        # entry
        shared_srcs = self.srcs.next()
        shared_srcs.image = ui_image
        src0 = create_rect(48, 288, 24, 24)
        shared_srcs.srcs.push(src0)
        # entry
        shared_srcs = self.srcs.next()
        shared_srcs.image = ui_image
        src0 = create_rect(0, 320, 24, 44)
        shared_srcs.srcs.push(src0)
        # entry
        shared_srcs = self.srcs.next()
        shared_srcs.image = ui_image
        src0 = create_rect(0, 364, 64, 25)
        shared_srcs.srcs.push(src0)
        # entry
        shared_srcs = self.srcs.next()
        shared_srcs.image = ui_image
        src0 = create_rect(0, 389, 24, 24)
        shared_srcs.srcs.push(src0)
        # entry
        shared_srcs = self.srcs.next()
        shared_srcs.image = ui_image
        src0 = create_rect(0, 413, 13, 12)
        shared_srcs.srcs.push(src0)
        # entry
        shared_srcs = self.srcs.next()
        shared_srcs.image = ui_image
        src0 = create_rect(0, 425, 9, 6)
        shared_srcs.srcs.push(src0)
        # entry
        shared_srcs = self.srcs.next()
        shared_srcs.image = ui_image
        src0 = create_rect(0, 431, 80, 80)
        shared_srcs.srcs.push(src0)
        # entry
        shared_srcs = self.srcs.next()
        shared_srcs.image = ui_image
        src0 = create_rect(0, 512, 80, 20)
        shared_srcs.srcs.push(src0)
        # entry
        shared_srcs = self.srcs.next()
        shared_srcs.image = ui_image
        src0 = create_rect(60, 0, 60, 24)
        shared_srcs.srcs.push(src0)

    def find(self, game: Game, image_name: ImageName, rect: SDL_Rect) -> SpriteSrcs:
        # do lookup based on image_name and first rect
        for shared_srcs in self.srcs:
            first_shared_src = shared_srcs.srcs.at(0)
            if shared_srcs.image.image_name == image_name and rects_are_equal(first_shared_src, rect):
                return shared_srcs

        image_name_as_int = cast(image_name, "int")
        print("SharedSpriteDB.find - rect not found. image_name:", image_name_as_int, "rect:",
              rect.x, rect.y, rect.w, rect.h)
        exit(1)
        return self.srcs.at(0)


class SharedSprite:
    def __init__(self):
        self.shared_srcs: SpriteSrcsPtr = None
        self.render_dst: RenderDst = None
        self.current_frame_idx: int = 0
        self.anim_speed: Uint32 = None
        self.spawn_time: Uint32 = None

    def update(self, game: Game):
        if self.shared_srcs == None:
            print("Sprite.update - shared srcs is NULL.")
            exit(1)
        if self.shared_srcs.srcs.size == 0:
            print("Sprite.update - srcs.size is 0.")
            exit(1)
        if self.anim_speed == 0:
            print("Sprite.update - anim_speed is 0.")
            exit(1)
        self.current_frame_idx = game.get_current_frame(
            self.shared_srcs.srcs.size, self.anim_speed, self.spawn_time)
        src = self.shared_srcs.srcs.at(self.current_frame_idx)
        self.render_dst.dst.w = src.w
        self.render_dst.dst.h = src.h
        self.render_dst.update(game.engine.camera.dst, game.engine.scale)

    def draw(self, game: Game):
        src = self.shared_srcs.srcs.at(self.current_frame_idx)
        SDL_RenderCopy(game.engine.renderer, self.shared_srcs.image.texture,
                       src, self.render_dst.scaled_dst)
