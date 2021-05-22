#ifndef GAME_FONT
#define GAME_FONT

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "stbttf_sdl.h"
#include "ct_array.h"
#include "constants.h"
#include "utils.h"

struct CT_StackTrace;

typedef struct CharInfo {
  SDL_Rect rect;
  int minx;
  int maxx;
  int miny;
  int maxy;
  int advance;
} CharInfo;

typedef struct Array_CharInfo_322 {
  CharInfo arr[322];
  int size;
  int capacity;
} Array_CharInfo_322;

typedef struct Font {
  STBTTF_Font* stb_font;
  SDL_Texture* texture;
  FontStyle font_style;
  int font_size;
  SDL_Color color;
  int outline;
  SDL_Color outline_color;
  int font_height;
  bool use_drop_shadow;
  Array_CharInfo_322 char_infos;
} Font;

typedef struct Array_Font_50 {
  Font arr[50];
  int size;
  int capacity;
} Array_Font_50;


#endif // GAME_FONT
