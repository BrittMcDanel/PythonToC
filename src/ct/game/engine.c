#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "ct_stacktrace.h"
#include <time.h>
#include "engine.h"
#include "constants.h"
#include "font.h"
#include "image.h"
#include "audio.h"
#include "utils.h"
#include "ct_array.h"
#include "game.h"

bool engine_colors_are_equal(SDL_Color* c1, SDL_Color* c2) {  return c1->r == c2->r && c1->g == c2->g && c1->b == c2->b && c1->a == c2->a;}

SDL_Rect engine_create_rect(int x, int y, int w, int h) {  SDL_Rect r;  r.x = x;  r.y = y;  r.w = w;  r.h = h;  return r;}

void engine_clear(Engine* engine) {  SDL_SetRenderDrawColor(engine->renderer, 255, 255, 255, 255);  SDL_RenderClear(engine->renderer);}

void engine_present(Engine* engine) {  SDL_RenderPresent(engine->renderer);  SDL_Delay(1000 / 70);}

void engine_start(Engine* engine) {    /* Initialize SDL_video */  if (SDL_Init(SDL_INIT_VIDEO) < 0) {    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s",                 SDL_GetError());    exit(1);  }  /* Initialize SDL_image */  int imgFlags = IMG_INIT_PNG;  if (!(IMG_Init(imgFlags) & imgFlags)) {    printf("SDL_image could not initialize! SDL_image Error: %s\n",           IMG_GetError());  }  /* Initialize SDL_ttf */  if (TTF_Init() == -1) {    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());    exit(1);  }  /* Initialize SDL_mixer */  if (Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {    printf("SDL_mixer could not initialize!\n");    exit(1);  }  engine->window =      SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,                       engine->window_resolution.x, engine->window_resolution.y,                       SDL_WINDOW_RESIZABLE);  /* turning off batching for now until it is statically linked     SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1"); */  engine->renderer =      SDL_CreateRenderer(engine->window, -1, SDL_RENDERER_ACCELERATED);  SDL_SetRenderDrawBlendMode(engine->renderer, SDL_BLENDMODE_BLEND);  /* SDL_SetWindowBordered(engine->window, SDL_FALSE); */  /* SDL_SetWindowFullscreen(engine->window, SDL_WINDOW_FULLSCREEN_DESKTOP); */  /* load assets */  engine_load_images(engine);  engine_load_audio(engine);  /* init rand */  engine->rand = seedRand(time(NULL));  /* set custom cursor */  /* store and free this surface in engine later */  SDL_Surface *cursor_surface = IMG_Load("../assets/ui/cursor.png");  if (!cursor_surface) {    printf("set cursor error");    exit(1);  }  SDL_Cursor *cursor = SDL_CreateColorCursor(cursor_surface, 0, 0);  if (!cursor) {    printf("set cursor error");    exit(1);  }  SDL_SetCursor(cursor);}

void engine_get_input(Engine* engine) {SDL_Event e;int key_idx = 0;int num_keys = 322;while (SDL_PollEvent(&e)) {  switch (e.type) {    case SDL_QUIT: {      engine->quit = true;      break;    }    case SDL_MOUSEBUTTONDOWN: {      if (e.button.button == SDL_BUTTON_LEFT) {        engine->is_mouse_down = true;        engine->is_mouse_held_down = true;      }      if (e.button.button == SDL_BUTTON_RIGHT) {        engine->is_right_mouse_down = true;        engine->is_right_mouse_held_down = true;      }      break;    }    case SDL_MOUSEBUTTONUP: {      if (e.button.button == SDL_BUTTON_LEFT) {        engine->is_mouse_held_down = false;        engine->is_mouse_up = true;      }      if (e.button.button == SDL_BUTTON_RIGHT) {        engine->is_right_mouse_held_down = false;        engine->is_right_mouse_up = true;      }      break;    }    case SDL_MOUSEWHEEL: {      if (e.wheel.y == -1) {        engine->is_mouse_wheel_down = true;      } else if (e.wheel.y == 1) {        engine->is_mouse_wheel_up = true;      }    }    case SDL_TEXTINPUT: {      /* text_input_this_frame += e.text.text; */      break;    }    case SDL_KEYDOWN: {      key_idx = (int)e.key.keysym.sym;      if (key_idx < 0 || key_idx > num_keys - 1) {        break;      }      engine->keys_down.arr[e.key.keysym.sym] = true;      engine->keys_held_down.arr[e.key.keysym.sym] = true;      break;    }    case SDL_KEYUP: {      key_idx = (int)e.key.keysym.sym;      if (key_idx < 0 || key_idx > num_keys - 1) {        break;      }      engine->keys_held_down.arr[e.key.keysym.sym] = false;      engine->keys_up.arr[e.key.keysym.sym] = true;      break;    }    }}}

void engine_load_image(Engine* engine, ImageName image_name, char* image_file_path) {  if (engine->images.size > 49) {    printf("engine_load_image - images.size > capacity");    exit(1);  }  SDL_Surface *image_surface = IMG_Load(image_file_path);  if (image_surface == NULL) {      printf("Engine::load_image. Image file path not found.\n");      exit(1);  }  SDL_Texture *image_texture =      SDL_CreateTextureFromSurface(engine->renderer, image_surface);  SDL_FreeSurface(image_surface);  Image image;  image.image_name = image_name;  image.texture = image_texture;  engine->images.arr[engine->images.size] = image;  engine->images.size += 1;}

void engine_load_images(Engine* engine) {  engine_load_image(engine, ImageName_UI, "../assets/ui/ui.png");  engine_load_image(engine, ImageName_Tiles, "../assets/tiles/tiles.png");  engine_load_image(engine, ImageName_Units, "../assets/units/units.png");  engine_load_image(engine, ImageName_Abilities,                    "../assets/abilities/abilities.png");  engine_load_image(engine, ImageName_Buildings,                    "../assets/buildings/buildings.png");  engine_load_image(engine, ImageName_Misc, "../assets/misc/misc.png");  engine_load_image(engine, ImageName_Items, "../assets/items/items.png");  engine_load_image(engine, ImageName_Monsters,                    "../assets/units/monsters.png");}

void engine_load_bgm_audio(Engine* engine, BGMAudioName bgm_audio_name, char* audio_file_path) {  if (engine->bgm_audio.size > 49) {    printf("engine_load_bgm_audio - bgm_audio.size > capacity");    exit(1);  }  Mix_Music *bgm_audio = Mix_LoadMUS(audio_file_path);  if (bgm_audio == NULL) {      printf("Engine::load_bgm_audio. Audio file path not found. Audio file: '%s'\n", audio_file_path);      exit(1);  }  BGMAudio audio;  audio.audio_name = bgm_audio_name;  audio.audio = bgm_audio;  engine->bgm_audio.arr[engine->bgm_audio.size] = audio;  engine->bgm_audio.size += 1;}

void engine_load_se_audio(Engine* engine, SEAudioName se_audio_name, char* audio_file_path) {  if (engine->se_audio.size > 99) {    printf("engine_load_se_audio - se_audio.size > capacity");    exit(1);  }  Mix_Chunk *se_audio = Mix_LoadWAV(audio_file_path);  if (se_audio == NULL) {      printf("Engine::load_se_audio. Audio file path not found. Audio file: '%s'\n", audio_file_path);      exit(1);  }  SEAudio audio;  audio.audio_name = se_audio_name;  audio.audio = se_audio;  engine->se_audio.arr[engine->se_audio.size] = audio;  engine->se_audio.size += 1;}

void engine_load_audio(Engine* engine) {  /* bgm audio */  engine_load_bgm_audio(engine, BGMAudioName_Forest, "../assets/audio/bgm/rostreamside.mp3");  /* sound effect audio */  engine_load_se_audio(engine, SEAudioName_Sword, "../assets/audio/soundeffects/ff7sword.wav");}

Font* engine_get_font(Engine* engine, FontStyle font_style, int font_size,                      SDL_Color* color, int outline, SDL_Color* outline_color, bool use_drop_shadow) {  int i;  Font *font;  for (i = 0; i < engine->fonts.size; i++) {    font = &engine->fonts.arr[i];    if (font->font_style == font_style && font->font_size == font_size &&        engine_colors_are_equal(&font->color, color) && font->outline == outline &&        engine_colors_are_equal(&font->outline_color, outline_color) &&        font->use_drop_shadow == use_drop_shadow) {      return font;    }  }  if (engine->fonts.size > 49) {    printf("engine_get_font - fonts.size > capacity");    exit(1);  }  font = &engine->fonts.arr[engine->fonts.size];  engine->fonts.size += 1;  /* font for this font size and color does not exist, create it */  font_init(font, engine->renderer, font_style, font_size, color, outline,            outline_color, use_drop_shadow);  printf("created new font - fonts vec is now of size %d.\n",         engine->fonts.size);  return font;}

CharInfo create_char_info(SDL_Rect _rect, int _minx, int _maxx, int _miny, int _maxy, int _advance) {  CharInfo char_info;  char_info.rect = _rect;  char_info.minx = _minx;  char_info.maxx = _maxx;  char_info.miny = _miny;  char_info.maxy = _maxy;  char_info.advance = _advance;  return char_info;}

void font_init(Font* font, SDL_Renderer* renderer, FontStyle _font_style,                int _font_size, SDL_Color* _color, int _outline, SDL_Color* _outline_color,               bool _use_drop_shadow) {  font->font_style = _font_style;  font->font_size = _font_size;  font->color = *_color;  font->outline = _outline;  font->outline_color = *_outline_color;  font->use_drop_shadow = _use_drop_shadow;  font->texture = NULL;  font->stb_font = NULL;  if (font->font_style == FontStyle_Normal) {    font->stb_font = STBTTF_OpenFont(        renderer, "../assets/fonts/Cantarell/Cantarell-Regular.ttf",        font->font_size, font->color, font->outline_color);  } else if (font->font_style == FontStyle_Bold) {    font->stb_font = STBTTF_OpenFont(        renderer, "../assets/fonts/rainyhearts.ttf",        font->font_size, font->color, font->outline_color);  } else if (font->font_style == FontStyle_Italic) {    font->stb_font = STBTTF_OpenFont(        renderer, "../assets/fonts/Cantarell/Cantarell-Italic.ttf",        font->font_size, font->color, font->outline_color);  }  if (font->stb_font == NULL) {    printf("Font - init_font - stb_font is NULL.\n");    exit(1);  }  /*string bmp_file_name      = string("../assets/fonts/atlas") + to_string(font_size) +     string(".bmp");*/  if (font->font_size == 16) {    SDL_SaveBMP(font->stb_font->atlas_surf, "../assets/fonts/stb_atlas.bmp");  }  font->font_height = (int)(font->stb_font->baseline * 1.25);  int atlas_surface_w = 2048;  int atlas_surface_h = 2048;  SDL_Surface *atlas_surface =      create_w_h_surface(atlas_surface_w, atlas_surface_h);  int atlas_x = 0;  int atlas_y = 0;  int outline_width = (font->outline * 2) + 1;  printf("font size %d outline %d outline width %d\n", font->font_size,         font->outline, outline_width);  for (int i = 32; i < 128; i++) {    char c = (char)i;    stbtt_packedchar *info = &font->stb_font->chars[(int)c - 32];    SDL_Rect char_src_rect =        STBTTF_get_src_rect_for_char(renderer, font->stb_font, c);    /* check if the character will overflow the atlas_w, if so move to a new line. */    if (atlas_x + char_src_rect.w + outline_width > atlas_surface_w) {      atlas_x = 0;      atlas_y += font->stb_font->baseline * 2;      if (atlas_y >= atlas_surface_h) {        printf("Font - constructor. Atlas_y is >= the Atlas_h.\n");        exit(1);      }    }    SDL_Rect dst_rect =        engine_create_rect(atlas_x, atlas_y, char_src_rect.w, char_src_rect.h);    dst_rect.y += font->stb_font->baseline;    /* outline    SDL_SetTextureColorMod(font->texture, 255, 0, 0); */    int outline_start_point = 0;    if (font->use_drop_shadow) {      outline_start_point = font->outline + 1;    }    for (int i = outline_start_point; i < outline_width; i++) {      for (int j = outline_start_point; j < outline_width; j++) {        SDL_Rect outline_dst_rect = dst_rect;        outline_dst_rect.x += i;        outline_dst_rect.y += j;        SDL_BlitSurface(font->stb_font->outline_surf, &char_src_rect,                        atlas_surface, &outline_dst_rect);      }    }    /* non outlined text */    SDL_Rect non_outlined_dst_rect = dst_rect;    non_outlined_dst_rect.x += font->outline;    non_outlined_dst_rect.y += font->outline;    SDL_BlitSurface(font->stb_font->atlas_surf, &char_src_rect, atlas_surface,                    &non_outlined_dst_rect);    SDL_Rect dst_rect_including_outline = dst_rect;    dst_rect_including_outline.w += outline_width;    dst_rect_including_outline.h += outline_width;    /*printf("dst\n");    print_rect(&dst_rect);    printf("non outlined dst\n");    print_rect(&non_outlined_dst_rect);    printf("including outline\n");    print_rect(&dst_rect_including_outline);    printf("---\n");*/    font->char_infos.arr[(int)c] = create_char_info(dst_rect_including_outline, 0,                                                0, 0, 0, (int)info->xadvance);    atlas_x += (int)info->xadvance * 5;  }  /* string bmp_file_name =      string("../assets/fonts/atlas") + to_string(font_size) + string(".bmp");  SDL_SaveBMP(stb_font->outline_surf, bmp_file_name.c_str());*/  font->texture = SDL_CreateTextureFromSurface(renderer, atlas_surface);}

void engine_free(Engine* engine) {  return;}

void void_mfunc_Engine_init_EnginePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Engine* self) {
    int i = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    self->base_resolution = SDL_Point_create_point_int_int(ct_stacktrace, 3, 53, 640, 360);
    self->window_resolution = SDL_Point_create_point_int_int(ct_stacktrace, 3, 54, (self->base_resolution.x * 2), (self->base_resolution.y * 2));
    self->scale = (self->window_resolution.x / self->base_resolution.x);
    self->mouse_point = SDL_Point_create_point_int_int(ct_stacktrace, 3, 56, 0, 0);
    self->mouse_point_scaled = SDL_Point_create_point_int_int(ct_stacktrace, 3, 57, 0, 0);
    self->is_mouse_down = false;
    self->is_mouse_held_down = false;
    self->is_mouse_up = false;
    self->is_right_mouse_down = false;
    self->is_right_mouse_held_down = false;
    self->is_right_mouse_up = false;
    self->is_mouse_wheel_up = false;
    self->is_mouse_wheel_down = false;
    self->bgm_audio_volume = (128 / 2);
    self->se_audio_volume = (128 / 2);
    self->is_bgm_paused = false;
    self->current_time = 0;
    self->prev_frame_time = 0;
    self->delta_time = 0;
    self->fps = 0;
    self->quit = false;
    for (i = 0; i < 322; i += 1) {
        void_push_value_Array_bool_322Ptr_bool(ct_stacktrace, 3, 78, &self->keys_down, false);
        void_push_value_Array_bool_322Ptr_bool(ct_stacktrace, 3, 79, &self->keys_held_down, false);
        void_push_value_Array_bool_322Ptr_bool(ct_stacktrace, 3, 80, &self->keys_up, false);
    }
    ct_stacktrace_pop(ct_stacktrace);
}

Image Image_mfunc_Engine_get_image_EnginePtr_ImageName(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Engine* self, ImageName image_name) {
    Image* image = NULL;
    int i = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    for (i = 0; i < self->images.size; i++) {
        image = &self->images.arr[i];
        if (image->image_name == image_name) {
                        ct_stacktrace_pop(ct_stacktrace);
return *image;
    }
}
    ct_stacktrace_push(ct_stacktrace, 4, 119);
    ct_stacktrace_print(ct_stacktrace);
    exit(1);
    if (0 < 0 || 0 > self->images.size - 1) {
            printf("Out of bounds error: idx: %d size: %d.\n", 0, self->images.size);
            ct_stacktrace_push(ct_stacktrace, 4, 120);
            ct_stacktrace_print(ct_stacktrace);
            exit(1);
        }
            ct_stacktrace_pop(ct_stacktrace);
return self->images.arr[0];
}

int int_mfunc_Engine_get_rand_int_EnginePtr_int_int(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Engine* self, int min, int max) {
    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
        ct_stacktrace_pop(ct_stacktrace);
return rand_int(&self->rand, min, max);
}

void void_mfunc_Engine_update_EnginePtr(CT_StackTrace* ct_stacktrace, int func_idx_of_call, int line_number_of_call, Engine* self) {
    int i = 0;
    Uint32 prev_current_time = 0;

    ct_stacktrace_push(ct_stacktrace, func_idx_of_call, line_number_of_call);
    prev_current_time = self->current_time;
    self->fps += 1;
    self->current_time = SDL_GetTicks();
    self->delta_time = (self->current_time - prev_current_time);
    if ((self->current_time - self->prev_frame_time) >= 1000) {
        self->prev_frame_time = self->current_time;
        printf("%s %d\n", "fps", self->fps);
        self->fps = 0;
}
    SDL_GetMouseState(&self->mouse_point.x, &self->mouse_point.y);
    self->mouse_point_scaled = self->mouse_point;
    self->mouse_point_scaled.x = (self->mouse_point.x / self->scale);
    self->mouse_point_scaled.y = (self->mouse_point.y / self->scale);
    self->mouse_point_scaled_with_camera = self->mouse_point_scaled;
    self->mouse_point_scaled_with_camera.x += self->camera.dst.x;
    self->mouse_point_scaled_with_camera.y += self->camera.dst.y;
    self->mouse_point_with_camera = self->mouse_point_scaled_with_camera;
    self->mouse_point_with_camera.x *= self->scale;
    self->mouse_point_with_camera.y *= self->scale;
    self->is_mouse_down = false;
    self->is_mouse_up = false;
    self->is_right_mouse_down = false;
    self->is_right_mouse_up = false;
    self->is_mouse_wheel_up = false;
    self->is_mouse_wheel_down = false;
    for (i = 0; i < 322; i += 1) {
        if (i < 0 || i > self->keys_down.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->keys_down.size);
                ct_stacktrace_push(ct_stacktrace, 74, 109);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            self->keys_down.arr[i] = false;
        if (i < 0 || i > self->keys_up.size - 1) {
                printf("Out of bounds error: idx: %d size: %d.\n", i, self->keys_up.size);
                ct_stacktrace_push(ct_stacktrace, 74, 110);
                ct_stacktrace_print(ct_stacktrace);
                exit(1);
            }
            self->keys_up.arr[i] = false;
}
    engine_get_input(self);
    ct_stacktrace_pop(ct_stacktrace);
}

