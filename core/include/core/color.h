#pragma once

#include <utils/types.h>

typedef struct {
  u8 r;
  u8 g;
  u8 b;
  u8 a;
} Color;

u8 color_get_component(Color c, int index);

extern Color color_black;
extern Color color_white;
extern Color color_red;
extern Color color_blue;
extern Color color_green;
extern Color color_gray;
extern Color color_transparent;
