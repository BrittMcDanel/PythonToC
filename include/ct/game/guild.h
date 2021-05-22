#ifndef GAME_GUILD
#define GAME_GUILD

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "stbttf_sdl.h"
#include "utils.h"
#include "ct_array.h"
#include "inventory.h"

struct CT_StackTrace;
struct Game;

typedef struct Guild {
  Array_char_100 display_name;
  Array_int_30 unit_handles;
  Array_int_30 merchant_handles;
  Inventory inventory;
  Uint64 current_money;
  Uint64 total_money_earned;
  bool is_anonymous;
  int handle;
  bool in_use_in_pool;
} Guild;

typedef struct Array_Guild_100 {
  Guild arr[100];
  int size;
  int capacity;
} Array_Guild_100;

void void_mfunc_Guild_init_GuildPtr_GamePtr_int(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Guild* self, struct Game* game, int handle);
void void_mfunc_Guild_set_to_GuildPtr_charPtr(struct CT_StackTrace *ct_stacktrace, int func_idx_of_call, int line_number_of_call, Guild* self, char* display_name_str);

#endif // GAME_GUILD
