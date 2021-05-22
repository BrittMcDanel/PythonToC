#ifndef GAME_UI
#define GAME_UI

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "stbttf_sdl.h"
#include "engine.h"
#include "image.h"
#include "input_events.h"
#include "utils.h"
#include "image.h"
#include "ct_array.h"
#include "constants.h"
#include "input_events.h"
#include "ui_sprite.h"
#include "text.h"
#include "ui_containers.h"

struct CT_StackTrace;
struct Game;

typedef struct UI {
  Array_UIRenderable_300 renderables;
  TopNav top_nav;
  RecruitNoviceModal recruit_novice_modal;
  GuildWindow guild_window;
  UnitsWindow units_window;
  MerchantsWindow merchants_window;
  bool is_mouse_over_ui;
  bool on_click_fired_this_frame;
} UI;

void void_mfunc_UI_init_UIPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UI* self, struct Game* game);
void void_mfunc_UI_clear_UIPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UI* self);
void void_mfunc_UI_on_click_UIPtr_GamePtr_UIEventPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UI* self, struct Game* game, struct UIEvent* ui_event);
void void_mfunc_UI_after_on_click_UIPtr_GamePtr_UIEventPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UI* self, struct Game* game, struct UIEvent* ui_event);
void void_mfunc_UI_update_UIPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UI* self, struct Game* game);
void void_mfunc_UI_draw_UIPtr_GamePtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, UI* self, struct Game* game);

#endif // GAME_UI
