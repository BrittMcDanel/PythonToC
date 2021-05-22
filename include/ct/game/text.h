#ifndef GAME_TEXT
#define GAME_TEXT

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "stbttf_sdl.h"
#include "ct_array.h"
#include "constants.h"
#include "utils.h"
#include "font.h"

struct CT_StackTrace;
struct Game;

typedef struct TextSM {
  Font* font;
  RenderDst render_dst;
  Array_char_21 str;
  int width;
  int font_size;
  TextAlignment text_alignment;
  TextWordWrap text_word_wrap;
  FontStyle font_style;
  int outline;
  SDL_Color color;
  SDL_Color outline_color;
  bool use_drop_shadow;
  int handle;
  bool in_use_in_pool;
} TextSM;

typedef struct Array_TextSM_5000 {
  TextSM arr[5000];
  int size;
  int capacity;
} Array_TextSM_5000;

typedef struct TextLG {
  Font* font;
  RenderDst render_dst;
  Array_char_200 str;
  int width;
  int font_size;
  TextAlignment text_alignment;
  TextWordWrap text_word_wrap;
  FontStyle font_style;
  int outline;
  SDL_Color color;
  SDL_Color outline_color;
  bool use_drop_shadow;
  int handle;
  bool in_use_in_pool;
} TextLG;

typedef struct Array_TextLG_2 {
  TextLG arr[2];
  int size;
  int capacity;
} Array_TextLG_2;

typedef struct Array_TextLG_6 {
  TextLG arr[6];
  int size;
  int capacity;
} Array_TextLG_6;

typedef struct Array_TextLG_12 {
  TextLG arr[12];
  int size;
  int capacity;
} Array_TextLG_12;

typedef struct Array_TextLG_50 {
  TextLG arr[50];
  int size;
  int capacity;
} Array_TextLG_50;

typedef struct Array_TextLG_10 {
  TextLG arr[10];
  int size;
  int capacity;
} Array_TextLG_10;

SDL_Point text_draw_string(struct Game* game, struct Font* font, char* str, int len, struct SDL_Rect* dst, bool perform_draw);
void void_text_set_TextLGPtr_GamePtr_charPtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, TextLG* self, struct Game* game, char* text_str, struct SDL_Point* dst, FontStyle font_style, TextAlignment _text_alignment, TextWordWrap _text_word_wrap, int _width, int font_size, struct SDL_Color* color, int outline, struct SDL_Color* outline_color, bool use_drop_shadow);
void void_text_set_color_TextLGPtr_GamePtr_SDL_ColorPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, TextLG* self, struct Game* game, struct SDL_Color* color);
void void_text_init_TextSMPtr_GamePtr_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, TextSM* self, struct Game* game, int handle);
void void_text_set_without_str_TextSMPtr_GamePtr_SDL_PointPtr_FontStyle_TextAlignment_TextWordWrap_int_int_SDL_ColorPtr_int_SDL_ColorPtr_bool(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, TextSM* self, struct Game* game, struct SDL_Point* dst, FontStyle font_style, TextAlignment _text_alignment, TextWordWrap _text_word_wrap, int _width, int font_size, struct SDL_Color* color, int outline, struct SDL_Color* outline_color, bool use_drop_shadow);
void void_text_update_TextLGPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, TextLG* self, struct Game* game);
void void_text_update_TextSMPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, TextSM* self, struct Game* game);
void void_text_draw_TextLGPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, TextLG* self, struct Game* game);
void void_text_draw_TextSMPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, TextSM* self, struct Game* game);

#endif // GAME_TEXT
