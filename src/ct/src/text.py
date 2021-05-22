from ct.src.ct_array import *
from ct.src.constants import FontStyle, TextAlignment, TextWordWrap
from ct.src.utils import SDL_Color, SDL_Point, SDL_Rect, RenderDst, colors_are_equal, create_rect, create_point, set_scaled_rect, set_scaled_rect_with_camera
from ct.src.base_types import Array, char, FontPtr, cast, addr, deref, array_get_buffer
from ct.src.font import Font
# weak imports
from ct.src.game import Game
from ct.src.engine import SDL_RenderCopy, engine_get_font

# Uint64 max value is 18,446,744,073,709,551,615 or 20 chars without commas.
# TextSM is size 21 so that it can hold Uint64 plus the null terminator char.


class TextSM:
    def __init__(self):
        self.font: FontPtr = None
        self.render_dst: RenderDst = None
        self.str: Array[char] = Array[char](21)
        self.width: int = None
        self.font_size: int = None
        self.text_alignment: TextAlignment = None
        self.text_word_wrap: TextWordWrap = None
        self.font_style: FontStyle = None
        self.outline: int = None
        self.color: SDL_Color = None
        self.outline_color: SDL_Color = None
        self.use_drop_shadow: bool = None
        self.handle: int = None
        self.in_use_in_pool: bool = None


class TextLG:
    def __init__(self):
        self.font: FontPtr = None
        self.render_dst: RenderDst = None
        self.str: Array[char] = Array[char](200)
        self.width: int = None
        self.font_size: int = None
        self.text_alignment: TextAlignment = None
        self.text_word_wrap: TextWordWrap = None
        self.font_style: FontStyle = None
        self.outline: int = None
        self.color: SDL_Color = None
        self.outline_color: SDL_Color = None
        self.use_drop_shadow: bool = None
        self.handle: int = None
        self.in_use_in_pool: bool = None


def text_init(self, game: Game, handle: int):
    self.handle = handle
    self.in_use_in_pool = False


def text_set(self, game: Game, text_str, dst: SDL_Point,
             font_style: FontStyle, _text_alignment: TextAlignment,
             _text_word_wrap: TextWordWrap, _width: int, font_size: int,
             color: SDL_Color, outline: int, outline_color: SDL_Color,
             use_drop_shadow: bool):
    self.render_dst.dst = create_rect(dst.x, dst.y, 0, 0)
    self.render_dst.scaled_dst = self.render_dst.dst
    self.font_style = font_style
    self.text_alignment = _text_alignment
    self.text_word_wrap = _text_word_wrap
    self.width = _width
    self.font_size = font_size * game.engine.scale
    self.color = deref(color)
    self.outline = outline
    self.outline_color = deref(outline_color)
    self.use_drop_shadow = use_drop_shadow
    self.str.string_set_literal(text_str)
    self.font = engine_get_font(game.engine, self.font_style, self.font_size, self.color,
                                self.outline, self.outline_color, self.use_drop_shadow)
    self.render_dst.is_camera_rendered = False


def text_set_without_str(self, game: Game, dst: SDL_Point,
                         font_style: FontStyle, _text_alignment: TextAlignment,
                         _text_word_wrap: TextWordWrap, _width: int, font_size: int,
                         color: SDL_Color, outline: int, outline_color: SDL_Color,
                         use_drop_shadow: bool):
    # if the str was set before calling this function (such as in the case of damage text in world)
    self.render_dst.dst = create_rect(dst.x, dst.y, 0, 0)
    self.render_dst.scaled_dst = self.render_dst.dst
    self.font_style = font_style
    self.text_alignment = _text_alignment
    self.text_word_wrap = _text_word_wrap
    self.width = _width
    self.font_size = font_size * game.engine.scale
    self.color = deref(color)
    self.outline = outline
    self.outline_color = deref(outline_color)
    self.use_drop_shadow = use_drop_shadow
    self.font = engine_get_font(game.engine, self.font_style, self.font_size, self.color,
                                self.outline, self.outline_color, self.use_drop_shadow)
    self.render_dst.is_camera_rendered = False


def text_set_color(self, game: Game, color: SDL_Color):
    self.color = deref(color)
    self.font = engine_get_font(game.engine, self.font_style, self.font_size, self.color,
                                self.outline, self.outline_color, self.use_drop_shadow)


def text_update(self, game: Game):
    self.render_dst.update(game.engine.camera.dst, game.engine.scale)


def text_draw(self, game: Game):
    str_buffer = array_get_buffer(self.str)
    text_draw_string(game, self.font, str_buffer,
                     self.str.size, self.render_dst.scaled_dst, True)


'''<c_func>
SDL_Point text_draw_string(Game* game, Font* font, char* str, int len, SDL_Rect* dst,
                         bool perform_draw) {
  int x = 0;
  int y = 0;
  char c;
  int char_as_int;
  CharInfo *char_info;
  stbtt_packedchar *info;
  SDL_Rect *src_rect;
  SDL_Rect dst_rect;

  for (int i = 0; i < len; i++) {
    c = str[i];
    char_as_int = (int)c;
    if (!(char_as_int >= 32 || char_as_int <= 127)) {
      continue;
    }
    if (char_as_int < 0 || char_as_int > 322 - 1) {
        printf("Text - text_draw. char_as_int is out of bounds\n");
        exit(1);
    }
    char_info = &font->char_infos.arr[char_as_int];
    src_rect = &char_info->rect;
    info = &font->stb_font->chars[(int)c - 32];
    dst_rect = *src_rect;
    dst_rect.x = dst->x + x + info->xoff;
    dst_rect.y = dst->y + y + info->yoff + font->stb_font->baseline;
    if (perform_draw) {
      /* culling improves performance. */
      if (!(dst_rect.x < -dst_rect.w ||
          dst_rect.x > game->engine.window_resolution.x ||
          dst_rect.y < -dst_rect.h ||
          dst_rect.y > game->engine.window_resolution.y)) {
         SDL_RenderCopy(game->engine.renderer, font->texture, src_rect,
                     &dst_rect);
      }
    }
    x += char_info->advance;
  }
  
  SDL_Point text_dims;
  text_dims.x = x;
  text_dims.y = 0;
  return text_dims;
}
</c_func>'''


def text_draw_string(game: Game, text: TextLG, str, len: int, dst: SDL_Rect, perform_draw: bool) -> SDL_Point:
    return create_point(0, 0)
