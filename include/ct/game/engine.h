#ifndef GAME_ENGINE
#define GAME_ENGINE

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "stbttf_sdl.h"
#include "mtwister.h"
#include "constants.h"
#include "font.h"
#include "image.h"
#include "audio.h"
#include "utils.h"
#include "ct_array.h"

struct CT_StackTrace;

typedef struct Camera {
  SDL_Point dst;
} Camera;

typedef struct Engine {
  Camera camera;
  SDL_Window* window;
  SDL_Renderer* renderer;
  Array_Font_50 fonts;
  Array_Image_50 images;
  Array_BGMAudio_50 bgm_audio;
  Array_SEAudio_100 se_audio;
  MTRand rand;
  SDL_Point base_resolution;
  SDL_Point window_resolution;
  int scale;
  SDL_Point mouse_point;
  SDL_Point mouse_point_scaled;
  SDL_Point mouse_point_with_camera;
  SDL_Point mouse_point_scaled_with_camera;
  bool is_mouse_down;
  bool is_mouse_held_down;
  bool is_mouse_up;
  bool is_right_mouse_down;
  bool is_right_mouse_held_down;
  bool is_right_mouse_up;
  bool is_mouse_wheel_up;
  bool is_mouse_wheel_down;
  Array_bool_322 keys_down;
  Array_bool_322 keys_held_down;
  Array_bool_322 keys_up;
  int bgm_audio_volume;
  int se_audio_volume;
  bool is_bgm_paused;
  BGMAudio current_bgm_audio;
  SEAudio current_se_audio;
  Uint32 current_time;
  Uint32 prev_frame_time;
  Uint32 delta_time;
  int fps;
  bool quit;
} Engine;

bool engine_colors_are_equal(struct SDL_Color* c1, struct SDL_Color* c2);
SDL_Rect engine_create_rect(int x, int y, int w, int h);
void engine_clear(struct Engine* engine);
void engine_present(struct Engine* engine);
void engine_start(struct Engine* engine);
void engine_get_input(struct Engine* engine);
void engine_load_image(struct Engine* engine, ImageName image_name, char* image_file_path);
void engine_load_images(struct Engine* engine);
void engine_load_bgm_audio(struct Engine* engine, BGMAudioName bgm_audio_name, char* audio_file_path);
void engine_load_se_audio(struct Engine* engine, SEAudioName se_audio_name, char* audio_file_path);
void engine_load_audio(struct Engine* engine);
struct Font* engine_get_font(struct Engine* engine, FontStyle font_style, int font_size, struct SDL_Color* color, int outline, struct SDL_Color* outline_color, bool use_drop_shadow);
CharInfo create_char_info(SDL_Rect _rect, int _minx, int _maxx, int _miny, int _maxy, int _advance);
void font_init(struct Font* font, struct SDL_Renderer* renderer, FontStyle _font_style, int _font_size, struct SDL_Color* _color, int _outline, struct SDL_Color* _outline_color, bool _use_drop_shadow);
void engine_free(struct Engine* engine);
void void_mfunc_Engine_init_EnginePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Engine* self);
Image Image_mfunc_Engine_get_image_EnginePtr_ImageName(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Engine* self, ImageName image_name);
int int_mfunc_Engine_get_rand_int_EnginePtr_int_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Engine* self, int min, int max);
void void_mfunc_Engine_update_EnginePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Engine* self);

#endif // GAME_ENGINE
