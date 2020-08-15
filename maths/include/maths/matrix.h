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
} Mat3;

Mat3 mat3_identity();
Mat3 mat3_ortho(float left, float right, float top, float bottom);
Mat3 mat3_translate(Mat3 m, float x, float y);
Mat3 mat3_rotate(Mat3 m, float rotate);
Mat3 mat3_scale(Mat3 m, float x, float y);
Mat3 mat3_mul(Mat3 m1, Mat3 m2);
Vec mat3_mul_vec(Mat3 m, Vec v);
