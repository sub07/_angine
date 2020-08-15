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

extern Color color_black;
extern Color color_white;
extern Color color_red;
extern Color color_blue;
extern Color color_green;
extern Color color_gray;
extern Color color_transparent;
