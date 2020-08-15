#pragma once

#include <stdbool.h>

#define API __declspec(dllexport)

#define to_string(vec) "%f, %f\n",(vec).x,(vec).y

typedef struct {
  float x;
  float y;
} Vec;

typedef struct {
  Vec translate;
  float rotate;
  Vec scale;
  Vec origin;
} Transform;

API Transform transform_default();

API bool vec_eq(Vec v1, Vec v2);
API Vec vec_add(Vec v1, Vec v2);
API Vec vec_sub(Vec v1, Vec v2);
API Vec vec_mul(Vec v1, Vec v2);
API Vec vec_div(Vec v1, Vec v2);
API Vec vec_add_f(Vec v, float val);
API Vec vec_sub_f(Vec v, float val);
API Vec vec_mul_f(Vec v, float val);
API Vec vec_div_f(Vec v, float val);
API float vec_norm(Vec v);
API Vec vec_middle(Vec v1, Vec v2);
API Vec vec_normalize(Vec v);
API Vec vec_normal(Vec v);
API float vec_dist(Vec v1, Vec v2);
API float vec_dist2(Vec v1, Vec v2);
API float vec_det(Vec v1, Vec v2);
API float dev_dot(Vec v1, Vec v2);
API Vec vec_rotate(Vec v, float val);
