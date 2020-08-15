#include <core/color.h>

u8 color_get_int_component(Color c, int index) {
  switch (index) {
  case 0:
    return c.r * 255;
  case 1:
    return c.g * 255;
  case 2:
    return c.b * 255;
  case 3:
    return c.a * 255;
  default:
    return 0;
  }
}

float color_get_float_component(Color c, int index) {
  switch (index) {
  case 0:
    return c.r;
  case 1:
    return c.g;
  case 2:
    return c.b;
  case 3:
    return c.a;
  default:
    return 0;
  }
}

Color const color_black = {0, 0, 0, 1};
Color const color_white = {1, 1, 1, 1};
Color const color_red = {1, 0, 0, 1};
Color const color_blue = {0, 0, 1, 1};
Color const color_green = {0, 1, 0, 1};
Color const color_gray = {0.5f, 0.5f, 0.5f, 1};
Color const color_transparent = {0, 0, 0, 0};

