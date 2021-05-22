#include "game/stbttf_sdl.h"

void STBTTF_CloseFont(STBTTF_Font *font) {
  if (font->atlas) SDL_DestroyTexture(font->atlas);
  if (font->info) free(font->info);
  if (font->chars) free(font->chars);
  free(font);
}

SDL_Surface *create_w_h_surface(int w, int h) {
  int rmask = 0;
  int gmask = 0;
  int bmask = 0;
  int amask = 0;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  rmask = 0xff000000;
  gmask = 0x00ff0000;
  bmask = 0x0000ff00;
  amask = 0x000000ff;
#else
  rmask = 0x000000ff;
  gmask = 0x0000ff00;
  bmask = 0x00ff0000;
  amask = 0xff000000;
#endif
  return SDL_CreateRGBSurface(0, w, h, 32, rmask, gmask, bmask, amask);
}

SDL_Surface *create_sdl_surface(void *pixels, int w, int h) {
  int rmask = 0;
  int gmask = 0;
  int bmask = 0;
  int amask = 0;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  rmask = 0xff000000;
  gmask = 0x00ff0000;
  bmask = 0x0000ff00;
  amask = 0x000000ff;
#else
  rmask = 0x000000ff;
  gmask = 0x0000ff00;
  bmask = 0x00ff0000;
  amask = 0xff000000;
#endif
  SDL_Surface *atlas_surface = SDL_CreateRGBSurfaceFrom(
      pixels, w, h, 32, 4 * w, rmask, gmask, bmask, amask);
  SDL_SetSurfaceBlendMode(atlas_surface, SDL_BLENDMODE_BLEND);
  return atlas_surface;
}

STBTTF_Font *STBTTF_OpenFontRW(SDL_Renderer *renderer, SDL_RWops *rw,
                               float size, SDL_Color color,
                               SDL_Color outline_color) {
  Sint64 file_size = SDL_RWsize(rw);
  unsigned char *buffer = (unsigned char *)malloc(file_size);
  if (SDL_RWread(rw, buffer, file_size, 1) != 1) return NULL;
  SDL_RWclose(rw);

  STBTTF_Font *font = (STBTTF_Font *)calloc(sizeof(STBTTF_Font), 1);
  font->info = (stbtt_fontinfo *)malloc(sizeof(stbtt_fontinfo));
  font->chars = (stbtt_packedchar *)malloc(sizeof(stbtt_packedchar) * 96);

  if (stbtt_InitFont(font->info, buffer, 0) == 0) {
    free(buffer);
    STBTTF_CloseFont(font);
    return NULL;
  }

  // fill bitmap atlas with packed characters
  unsigned char *bitmap = NULL;
  font->texture_size = 32;
  while (1) {
    bitmap = (unsigned char *)malloc(font->texture_size * font->texture_size);
    stbtt_pack_context pack_context;
    stbtt_PackBegin(&pack_context, bitmap, font->texture_size,
                    font->texture_size, 0, 1, 0);
    stbtt_PackSetOversampling(&pack_context, 1, 1);
    if (!stbtt_PackFontRange(&pack_context, buffer, 0, size, 32, 95,
                             font->chars)) {
      // too small
      free(bitmap);
      stbtt_PackEnd(&pack_context);
      font->texture_size *= 2;
    } else {
      stbtt_PackEnd(&pack_context);
      break;
    }
  }

  // convert bitmap to texture
  font->atlas = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
                                  SDL_TEXTUREACCESS_STATIC, font->texture_size,
                                  font->texture_size);
  SDL_SetTextureBlendMode(font->atlas, SDL_BLENDMODE_BLEND);

  Uint32 *pixels = (Uint32 *)malloc(font->texture_size * font->texture_size *
                                    sizeof(Uint32));
  Uint32 *outline_pixels = (Uint32 *)malloc(
      font->texture_size * font->texture_size * sizeof(Uint32));
  static SDL_PixelFormat *format = NULL;
  if (format == NULL) format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
  for (int i = 0; i < font->texture_size * font->texture_size; i++) {
    pixels[i] = SDL_MapRGBA(format, color.r, color.g, color.b, bitmap[i]);
  }
  SDL_UpdateTexture(font->atlas, NULL, pixels,
                    font->texture_size * sizeof(Uint32));
  font->atlas_surf = create_sdl_surface((void *)pixels, font->texture_size,
                                        font->texture_size);
  for (int i = 0; i < font->texture_size * font->texture_size; i++) {
    outline_pixels[i] = SDL_MapRGBA(format, outline_color.r, outline_color.g,
                                    outline_color.b, bitmap[i]);
  }
  font->outline_surf = create_sdl_surface(
      (void *)outline_pixels, font->texture_size, font->texture_size);
  // these frees corrupt the surface for some reason, maybe store them and
  // free later, or dont even worry about it because the font atlases will
  // be turned into pngs anyway and stored. Fonts ultimately will never
  // be created at runtime.
  // free(pixels);
  // free(bitmap);
  // free(outline_pixels);

  // setup additional info
  font->scale = stbtt_ScaleForPixelHeight(font->info, size);
  stbtt_GetFontVMetrics(font->info, &font->ascent, 0, 0);
  font->baseline = (int)(font->ascent * font->scale);

  // this free corrupts the surface.
  // free(buffer);

  return font;
}

STBTTF_Font *STBTTF_OpenFont(SDL_Renderer *renderer, const char *filename,
                             float size, SDL_Color color,
                             SDL_Color outline_color) {
  SDL_RWops *rw = SDL_RWFromFile(filename, "rb");
  if (rw == NULL) return NULL;
  return STBTTF_OpenFontRW(renderer, rw, size, color, outline_color);
}

void STBTTF_RenderText(SDL_Renderer *renderer, STBTTF_Font *font, float x,
                       float y, const char *text) {
  Uint8 r, g, b, a;
  SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
  SDL_SetTextureColorMod(font->atlas, r, g, b);
  SDL_SetTextureAlphaMod(font->atlas, a);
  for (int i = 0; text[i]; i++) {
    if (text[i] >= 32 && text[i] < 128) {
      // if(i > 0) x += stbtt_GetCodepointKernAdvance(font->info, text[i - 1],
      // text[i]) * font->scale;

      stbtt_packedchar *info = &font->chars[text[i] - 32];
      SDL_Rect src_rect = {info->x0, info->y0, info->x1 - info->x0,
                           info->y1 - info->y0};
      SDL_Rect dst_rect = {(int)(x + info->xoff), (int)(y + info->yoff),
                           info->x1 - info->x0, info->y1 - info->y0};

      SDL_RenderCopy(renderer, font->atlas, &src_rect, &dst_rect);
      x += info->xadvance;
    }
  }
}

SDL_Rect STBTTF_get_src_rect_for_char(SDL_Renderer *renderer, STBTTF_Font *font,
                                      char c) {
  stbtt_packedchar *info = &font->chars[(int)c - 32];
  SDL_Rect src_rect = {info->x0, info->y0, info->x1 - info->x0,
                       info->y1 - info->y0};
  return src_rect;
}

SDL_Rect STBTTF_get_dst_rect_for_char(SDL_Renderer *renderer, STBTTF_Font *font,
                                      float x, float y, char c) {
  stbtt_packedchar *info = &font->chars[(int)c - 32];
  SDL_Rect dst_rect = {(int)(x + info->xoff), (int)(y + info->yoff),
                       info->x1 - info->x0, info->y1 - info->y0};
  return dst_rect;
}

float STBTTF_MeasureText(STBTTF_Font *font, const char *text) {
  float width = 0;
  for (int i = 0; text[i]; i++) {
    if (text[i] >= 32 && text[i] < 128) {
      // if(i > 0) width += stbtt_GetCodepointKernAdvance(font->info, text[i -
      // 1], text[i]) * font->scale;

      stbtt_packedchar *info = &font->chars[text[i] - 32];
      width += info->xadvance;
    }
  }
  return width;
}

/*******************
 * Example program *
 *******************
#include <stdio.h>
#define STB_RECT_PACK_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION
#define STBTTF_IMPLEMENTATION
#include "stbttf.h"
int main(int argc, char** argv) {
        if(argc != 2) {
                fprintf(stderr, "usage: %s <font>\n", argv[0]);
                exit(1);
        }
        SDL_Init(SDL_INIT_VIDEO);
        SDL_Window* window = SDL_CreateWindow("stbttf", SDL_WINDOWPOS_UNDEFINED,
SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
SDL_RENDERER_ACCELERATED); SDL_RenderSetLogicalSize(renderer, 640, 480);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        STBTTF_Font* font = STBTTF_OpenFont(renderer, argv[1], 32);
        while(1) {
                SDL_Event event;
                while(SDL_PollEvent(&event)) {
                        if(event.type == SDL_QUIT) exit(0);
                }
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);
                // set color and render some text
                SDL_SetRenderDrawColor(renderer, 128, 0, 0, 255);
                STBTTF_RenderText(renderer, font, 50, 50, "This is a test");
                // render the atlas to check its content
                //SDL_Rect dest = {0, 0, font->texturesize, font->texturesize};
                //SDL_RenderCopy(renderer, font->atlas, &dest, &dest);
                SDL_RenderPresent(renderer);
                SDL_Delay(1000 / 60);
        }
        STBTTF_CloseFont(font);
        SDL_Quit();
}
*/