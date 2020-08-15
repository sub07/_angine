#pragma once

#include <utils/types.h>
#include <stdbool.h>
#include "color.h"

typedef struct image_t {
  u8 *pixels;
  int width;
  int height;
  int nb_channel;
} Image;

typedef enum {
  R8 = 1,
  Rg88,
  Rgb888,
  Rgba8888
} image_format_;

Image *image_create(int width, int height, image_format_ format);
Image *image_create_from_data(void *data, int width, int height, image_format_ format);
Image *image_create_from_file(const char *path);
void image_free(Image *image);

void image_clear(Image *image, Color clear_color);
void image_draw_image(Image *dest, Image *src, int x, int y);
