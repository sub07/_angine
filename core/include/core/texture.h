#pragma once

#include "image.h"

typedef struct {
  float width;
  float height;
} Texture;

Texture *texture_create(void *data, int width, int height, int nb_channel);
Texture *texture_create_from_img(Image *image);
Texture *texture_create_from_file(const char *path);
void texture_bind(Texture *texture);
void texture_bind_texture_unit(Texture *texture, unsigned int texture_unit);
void texture_free(Texture *texture);
