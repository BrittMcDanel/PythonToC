#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "ct_stacktrace.h"
#include "text.h"
#include "ct_array.h"
#include "constants.h"
#include "utils.h"
#include "font.h"
#include "game.h"
#include "engine.h"

SDL_Point text_draw_string(Game* game, Font* font, char* str, int len, SDL_Rect* dst,                         bool perform_draw) {  int x = 0;  int y = 0;  char c;  int char_as_int;  CharInfo *char_info;  stbtt_packedchar *info;  SDL_Rect *src_rect;  SDL_Rect dst_rect;  for (int i = 0; i < len; i++) {    c = str[i];    char_as_int = (int)c;    if (!(char_as_int >= 32 || char_as_int <= 127)) {      continue;    }    if (char_as_int < 0 || char_as_int > 322 - 1) {        printf("Text - text_draw. char_as_int is out of bounds\n");        exit(1);    }    char_info = &font->char_infos.arr[char_as_int];    src_rect = &char_info->rect;    info = &font->stb_font->chars[(int)c - 32];    dst_rect = *src_rect;    dst_rect.x = dst->x + x + info->xoff;    dst_rect.y = dst->y + y + info->yoff + font->stb_font->baseline;    if (perform_draw) {      /* culling improves performance. */      if (!(dst_rect.x < -dst_rect.w ||          dst_rect.x > game->engine.window_resolution.x ||          dst_rect.y < -dst_rect.h ||          dst_rect.y > game->engine.window_resolution.y)) {         SDL_RenderCopy(game->engine.renderer, font->texture, src_rect,                     &dst_rect);      }    }    x += char_info->advance;  }    SDL_Point text_dims;  text_dims.x = x;  text_dims.y = 0;  return text_dims;}

void void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, TextLG* self, Game* game, char* text_str, SDL_Point* dst, FontStyle font_style, TextAlignment _text_alignment, TextWordWrap _text_word_wrap, int _width, int font_size, SDL_Color* color, int outline, SDL_Color* outline_color, bool use_drop_shadow) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->render_dst.dst = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 18, 52, dst->x, dst->y, 0, 0);
    self->render_dst.scaled_dst = self->render_dst.dst;
    self->font_style = font_style;
    self->text_alignment = _text_alignment;
    self->text_word_wrap = _text_word_wrap;
    self->width = _width;
    self->font_size = (font_size * game->engine.scale);
    self->color = *color;
    self->outline = outline;
    self->outline_color = *outline_color;
    self->use_drop_shadow = use_drop_shadow;
    void_string_set_literal_Array_char_200Ptr_charPtr(ct_stacktrace, 18, 63, &self->str, text_str);
    self->font = engine_get_font(&game->engine, self->font_style, self->font_size, &self->color, self->outline, &self->outline_color, self->use_drop_shadow);
    self->render_dst.is_camera_rendered = false;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_text_set_color_TextLGPtr_GamePtr_SDL_ColorPtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, TextLG* self, Game* game, SDL_Color* color) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->color = *color;
    self->font = engine_get_font(&game->engine, self->font_style, self->font_size, &self->color, self->outline, &self->outline_color, self->use_drop_shadow);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_text_init_TextSMPtr_GamePtr_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, TextSM* self, Game* game, int handle) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->handle = handle;
    self->in_use_in_pool = false;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_text_set_without_str_TextSMPtr_GamePtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, TextSM* self, Game* game, SDL_Point* dst, FontStyle font_style, TextAlignment _text_alignment, TextWordWrap _text_word_wrap, int _width, int font_size, SDL_Color* color, int outline, SDL_Color* outline_color, bool use_drop_shadow) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->render_dst.dst = SDL_Rect_create_rect_int_int_int_int(ct_stacktrace, 129, 70, dst->x, dst->y, 0, 0);
    self->render_dst.scaled_dst = self->render_dst.dst;
    self->font_style = font_style;
    self->text_alignment = _text_alignment;
    self->text_word_wrap = _text_word_wrap;
    self->width = _width;
    self->font_size = (font_size * game->engine.scale);
    self->color = *color;
    self->outline = outline;
    self->outline_color = *outline_color;
    self->use_drop_shadow = use_drop_shadow;
    self->font = engine_get_font(&game->engine, self->font_style, self->font_size, &self->color, self->outline, &self->outline_color, self->use_drop_shadow);
    self->render_dst.is_camera_rendered = false;
    ct_stacktrace_pop(ct_stacktrace);
}

void void_text_update_TextLGPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, TextLG* self, Game* game) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    void_mfunc_RenderDst_update_RenderDstPtr_SDL_PointPtr_int(ct_stacktrace, 153, 91, &self->render_dst, &game->engine.camera.dst, game->engine.scale);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_text_update_TextSMPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, TextSM* self, Game* game) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    void_mfunc_RenderDst_update_RenderDstPtr_SDL_PointPtr_int(ct_stacktrace, 153, 91, &self->render_dst, &game->engine.camera.dst, game->engine.scale);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_text_draw_TextLGPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, TextLG* self, Game* game) {
    char* str_buffer = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    str_buffer = self->str.arr;
    text_draw_string(game, self->font, str_buffer, self->str.size, &self->render_dst.scaled_dst, true);
    ct_stacktrace_pop(ct_stacktrace);
}

void void_text_draw_TextSMPtr_GamePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, TextSM* self, Game* game) {
    char* str_buffer = NULL;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    str_buffer = self->str.arr;
    text_draw_string(game, self->font, str_buffer, self->str.size, &self->render_dst.scaled_dst, true);
    ct_stacktrace_pop(ct_stacktrace);
}

