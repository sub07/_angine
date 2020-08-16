#pragma once

#include <stdbool.h>

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

typedef struct {
  Vec position;
  Vec size;
} Rect;

Transform transform_default();

bool vec_eq(Vec v1, Vec v2);
Vec vec_add(Vec v1, Vec v2);
Vec vec_sub(Vec v1, Vec v2);
Vec vec_mul(Vec v1, Vec v2);
Vec vec_div(Vec v1, Vec v2);
Vec vec_add_f(Vec v, float val);
Vec vec_sub_f(Vec v, float val);
Vec vec_mul_f(Vec v, float val);
Vec vec_div_f(Vec v, float val);
float vec_norm(Vec v);
Vec vec_middle(Vec v1, Vec v2);
Vec vec_normalize(Vec v);
Vec vec_normal(Vec v);
float vec_dist(Vec v1, Vec v2);
float vec_dist2(Vec v1, Vec v2);
float vec_det(Vec v1, Vec v2);
float dev_dot(Vec v1, Vec v2);
Vec vec_rotate(Vec v, float val);
