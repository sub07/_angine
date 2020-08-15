#pragma once

#include <utils/types.h>

typedef struct {
  float r;
  float g;
  float b;
  float a;
} Color;

u8 color_get_int_component(Color c, int index);
float color_get_float_component(Color c, int index);

extern Color const color_black;
extern Color const color_white;
extern Color const color_red;
extern Color const color_blue;
extern Color const color_green;
extern Color const color_gray;
extern Color const color_transparent;
