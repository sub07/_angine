#pragma once

#include <stdbool.h>

#define API __declspec(dllexport)

#define to_string(vec) "%f, %f\n",(vec).x,(vec).y

typedef struct {
  float x;
  float y;
} vec;

API bool vec_eq(vec v1, vec v2);
API vec vec_add(vec v1, vec v2);
API vec vec_sub(vec v1, vec v2);
API vec vec_mul(vec v1, vec v2);
API vec vec_div(vec v1, vec v2);
API vec vec_add_f(vec v, float val);
API vec vec_sub_f(vec v, float val);
API vec vec_mul_f(vec v, float val);
API vec vec_div_f(vec v, float val);
API float vec_norm(vec v);
API vec vec_middle(vec v1, vec v2);
API vec vec_normalize(vec v);
API vec vec_normal(vec v);
API float vec_dist(vec v1, vec v2);
API float vec_dist2(vec v1, vec v2);
API float vec_det(vec v1, vec v2);
API float dev_dot(vec v1, vec v2);
API vec vec_rotate(vec v, float val);
