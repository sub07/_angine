#include <core/color.h>

u8 color_get_component(Color c, int index) {
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

Color color_black = {0, 0, 0, 255};
Color color_white = {255, 255, 255, 255};
Color color_red = {255, 0, 0, 255};
Color color_blue = {0, 0, 255, 255};
Color color_green = {0, 255, 0, 255};
Color color_gray = {125, 125, 125, 255};
Color color_transparent = {0, 0, 0, 0};

