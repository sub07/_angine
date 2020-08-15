#include <maths/matrix.h>
#include <math.h>

Mat3 mat3_identity() {
  return (Mat3) {
      1.f, 0.f, 0.f,
      0.f, 1.f, 0.f,
      0.f, 0.f, 1.f
  };
}

Mat3 mat3_ortho(float left, float right, float top, float bottom) {
  return (Mat3) {
      2 / (right - left), 0.f, -(right + left) / (right - left),
      0.f, 2 / (top - bottom), -(top + bottom) / (top - bottom),
      0.f, 0.f, 1.f
  };
}

Mat3 mat3_translate(Mat3 m, float x, float y) {
  Mat3 translate = {
      1.f, 0.f, x,
      0.f, 1.f, y,
      0.f, 0.f, 1.f
  };
  return mat3_mul(m, translate);
}

Mat3 mat3_rotate(Mat3 m, float rotate) {
  Mat3 translate = {
      cosf(rotate), -sinf(rotate), 0.f,
      sinf(rotate), cos(rotate), 0.f,
      0.f, 0.f, 1.f
  };
  return mat3_mul(m, translate);
}

Mat3 mat3_scale(Mat3 m, float x, float y) {
  Mat3 scale = {
      x, 0.f, 0.f,
      0.f, y, 0.f,
      0.f, 0.f, 1.f
  };
  return mat3_mul(m, scale);
}

Mat3 mat3_mul(Mat3 m1, Mat3 m2) {
  float m00New = m1.m00 * m2.m00 + m1.m01 * m2.m10 + m1.m02 * m2.m20;
  float m01New = m1.m00 * m2.m01 + m1.m01 * m2.m11 + m1.m02 * m2.m21;
  float m02New = m1.m00 * m2.m02 + m1.m01 * m2.m12 + m1.m02 * m2.m22;
  
  float m10New = m1.m10 * m2.m00 + m1.m11 * m2.m10 + m1.m12 * m2.m20;
  float m11New = m1.m10 * m2.m01 + m1.m11 * m2.m11 + m1.m12 * m2.m21;
  float m12New = m1.m10 * m2.m02 + m1.m11 * m2.m12 + m1.m12 * m2.m22;
  
  float m20New = m1.m20 * m2.m00 + m1.m21 * m2.m10 + m1.m22 * m2.m20;
  float m21New = m1.m20 * m2.m01 + m1.m21 * m2.m11 + m1.m22 * m2.m21;
  float m22New = m1.m20 * m2.m02 + m1.m21 * m2.m12 + m1.m22 * m2.m22;
  
  return (Mat3) {
      m00New, m01New, m02New,
      m10New, m11New, m12New,
      m20New, m21New, m22New
  };
}

Vec mat3_mul_vec(Mat3 m, Vec v) {
  return (Vec) {
      m.m00 * v.x + m.m01 * v.y + m.m02,
      m.m10 * v.x + m.m11 * v.y + m.m12
  };
}
