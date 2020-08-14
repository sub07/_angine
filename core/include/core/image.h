#pragma once

#include <utils/types.h>
#include "color.h"

typedef struct image_t {
  u8 *pixels;
  int width;
  int height;
  int nb_channel;
} image_t;

typedef enum {
  R8 = 1,
  Rg88,
  Rgb888,
  Rgba8888
} image_format_;

image_t *image_create(int width, int height, image_format_ format);
image_t *image_create_from_file(const char *path);
void image_free(image_t *image);

void image_clear(image_t *image, color_t clear_color);
void image_draw_image(image_t *dest, image_t *src, int x, int y);