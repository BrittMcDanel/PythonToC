#ifndef GAME_IMAGE
#define GAME_IMAGE

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "stbttf_sdl.h"
#include "constants.h"

struct CT_StackTrace;

typedef struct Image {
  ImageName image_name;
  SDL_Texture* texture;
} Image;

typedef struct Array_Image_50 {
  Image arr[50];
  int size;
  int capacity;
} Array_Image_50;


#endif // GAME_IMAGE
