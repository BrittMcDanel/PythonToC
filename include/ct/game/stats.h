#ifndef GAME_STATS
#define GAME_STATS

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
#include "sprite.h"
#include "constants.h"

struct CT_StackTrace;

typedef struct Stats {
  int level;
  int job_level;
  Uint64 experience_drop;
  Uint64 job_experience_drop;
  Range experience;
  Range job_experience;
  Range strength;
  Range intelligence;
  Range dexterity;
  Range vitality;
  Range agility;
  Range luck;
  Range hp;
  Range attack_speed;
} Stats;


#endif // GAME_STATS
