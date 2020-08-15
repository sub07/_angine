#include <maths/vec.h>
#include <math.h>

Vec vec_add(Vec v1, Vec v2) {
  return (const Vec) {v1.x + v2.x, v1.y + v2.y};
}

Vec vec_sub(Vec v1, Vec v2) {
  return (const Vec) {v1.x - v2.x, v1.y - v2.y};
}

Vec vec_mul(Vec v1, Vec v2) {
  return (const Vec) {v1.x * v2.x, v1.y * v2.y};
}

Vec vec_div(Vec v1, Vec v2) {
  return (const Vec) {v1.x / v2.x, v1.y / v2.y};
}

Vec vec_add_f(Vec v, float val) {
  return (const Vec) {v.x + val, v.y + val};
}

Vec vec_sub_f(Vec v, float val) {
  return (const Vec) {v.x - val, v.y - val};
}

Vec vec_mul_f(Vec v, float val) {
  return (const Vec) {v.x * val, v.y * val};
}

Vec vec_div_f(Vec v, float val) {
  return (const Vec) {v.x / val, v.y / val};
}

float vec_norm(Vec v) {
  return sqrtf(v.x * v.x + v.y * v.y);
}

Vec vec_middle(Vec v1, Vec v2) {
  return vec_div_f(vec_add(v1, v2), 2.f);
}

Vec vec_normalize(Vec v) {
  float n = vec_norm(v);
  return (Vec) {v.x / n, v.y / n};
}

Vec vec_normal(Vec v) {
  return (Vec) {v.y, -v.x};
}

float vec_dist(Vec v1, Vec v2) {
  const Vec sub = vec_sub(v1, v2);
  return vec_norm(sub);
}

float vec_dist2(Vec v1, Vec v2) {
  const Vec sub = vec_sub(v1, v2);
  return sub.x * sub.x + sub.y * sub.y;
}

float vec_det(Vec v1, Vec v2) {
  return v1.x * v2.y - v1.y * v2.x;
}

float dev_dot(Vec v1, Vec v2) {
  return v1.x * v2.x + v1.y * v2.y;
}

Vec vec_rotate(Vec v, float val) {
  float new_x = cosf(val) * v.x - sinf(val) * v.y;
  float new_y = sinf(val) * v.x + cosf(val) * v.y;
  return (Vec) {new_x, new_y};
}

bool vec_eq(Vec v1, Vec v2) {
  return v1.x == v2.x && v1.y == v2.y;
}

Transform transform_default() {
  return (Transform) {{0.f, 0.f}, 0.f, {1.f, 1.f}, {0.f, 0.f}};
}
