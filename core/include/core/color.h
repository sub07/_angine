#pragma once

#include <utils/types.h>

typedef struct {
  u8 r;
  u8 g;
  u8 b;
  u8 a;
} color_t;

u8 color_get_component(color_t c, int index);

extern color_t color_black;
extern color_t color_white;
extern color_t color_red;
extern color_t color_blue;
extern color_t color_green;
extern color_t color_gray;
extern color_t color_transparent;