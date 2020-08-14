#include <maths/matrix.h>
#include <math.h>

mat3_t mat3_identity() {
  return (mat3_t) {
      1.f, 0.f, 0.f,
      0.f, 1.f, 0.f,
      0.f, 0.f, 1.f
  };
}

mat3_t mat3_ortho(float left, float right, float top, float bottom) {
  return (mat3_t) {
      2 / (right - left), 0.f, -(right + left) / (right - left),
      0.f, 2 / (top - bottom), -(top + bottom) / (top - bottom),
      0.f, 0.f, 1.f
  };
}

mat3_t mat3_translate(mat3_t m, float x, float y) {
  mat3_t translate = {
      1.f, 0.f, x,
      0.f, 1.f, y,
      0.f, 0.f, 1.f
  };
  return mat3_mul(m, translate);
}

mat3_t mat3_rotate(mat3_t m, float rotate) {
  mat3_t translate = {
      cosf(rotate), -sinf(rotate), 0.f,
      sinf(rotate), cos(rotate), 0.f,
      0.f, 0.f, 1.f
  };
  return mat3_mul(m, translate);
}

mat3_t mat3_scale(mat3_t m, float x, float y) {
  mat3_t scale = {
      x, 0.f, 0.f,
      0.f, y, 0.f,
      0.f, 0.f, 1.f
  };
  return mat3_mul(m, scale);
}

mat3_t mat3_mul(mat3_t m1, mat3_t m2) {
  float m00New = m1.m00 * m2.m00 + m1.m01 * m2.m10 + m1.m02 * m2.m20;
  float m01New = m1.m00 * m2.m01 + m1.m01 * m2.m11 + m1.m02 * m2.m21;
  float m02New = m1.m00 * m2.m02 + m1.m01 * m2.m12 + m1.m02 * m2.m22;
  
  float m10New = m1.m10 * m2.m00 + m1.m11 * m2.m10 + m1.m12 * m2.m20;
  float m11New = m1.m10 * m2.m01 + m1.m11 * m2.m11 + m1.m12 * m2.m21;
  float m12New = m1.m10 * m2.m02 + m1.m11 * m2.m12 + m1.m12 * m2.m22;
  
  float m20New = m1.m20 * m2.m00 + m1.m21 * m2.m10 + m1.m22 * m2.m20;
  float m21New = m1.m20 * m2.m01 + m1.m21 * m2.m11 + m1.m22 * m2.m21;
  float m22New = m1.m20 * m2.m02 + m1.m21 * m2.m12 + m1.m22 * m2.m22;
  
  return (mat3_t) {
      m00New, m01New, m02New,
      m10New, m11New, m12New,
      m20New, m21New, m22New
  };
}

vec mat3_mul_vec(mat3_t m, vec v) {
  return (vec) {
      m.m00 * v.x + m.m01 * v.y + m.m02,
      m.m10 * v.x + m.m11 * v.y + m.m12
  };
}
