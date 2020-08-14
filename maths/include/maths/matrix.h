#pragma once

#include "vec.h"

typedef struct {
  float m00;
  float m01;
  float m02;
  
  float m10;
  float m11;
  float m12;
  
  float m20;
  float m21;
  float m22;
} mat3_t;

mat3_t mat3_identity();
mat3_t mat3_ortho(float left, float right, float top, float bottom);
mat3_t mat3_translate(mat3_t m, float x, float y);
mat3_t mat3_rotate(mat3_t m, float rotate);
mat3_t mat3_scale(mat3_t m, float x, float y);
mat3_t mat3_mul(mat3_t m1, mat3_t m2);
vec mat3_mul_vec(mat3_t m, vec v);
