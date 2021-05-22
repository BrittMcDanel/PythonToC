#ifndef GAME_INPUT_EVENTS
#define GAME_INPUT_EVENTS

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "stbttf_sdl.h"
#include "engine.h"
#include "image.h"
#include "utils.h"
#include "image.h"
#include "ct_array.h"

struct CT_StackTrace;
struct Game;

typedef struct InputEvents {
  bool is_mouse_enter;
  bool is_mouse_exit;
  bool is_mouse_over;
  bool is_mouse_down;
  bool is_mouse_held_down;
  bool is_mouse_up;
  bool is_right_mouse_down;
  bool is_right_mouse_held_down;
  bool is_right_mouse_up;
  bool is_click;
  bool is_right_click;
  bool was_mouse_down_when_mouse_over;
  bool was_right_mouse_down_when_mouse_over;
} InputEvents;

void void_mfunc_InputEvents_update_InputEventsPtr_GamePtr_bool(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, InputEvents* self, struct Game* game, bool _is_mouse_over);
void void_mfunc_InputEvents_clear_InputEventsPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, InputEvents* self);

#endif // GAME_INPUT_EVENTS
