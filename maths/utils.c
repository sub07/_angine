#include <maths/utils.h>

const float pi = 3.14159265f;

float deg_to_rad(float deg) {
  return deg * pi / 180.f;
}

float rad_to_deg(float rad) {
  return rad * 180.f / pi;
}
