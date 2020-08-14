#include <maths/vec.h>
#include <math.h>

vec vec_add(vec v1, vec v2) {
  return (const vec) {v1.x + v2.x, v1.y + v2.y};
}

vec vec_sub(vec v1, vec v2) {
  return (const vec) {v1.x - v2.x, v1.y - v2.y};
}

vec vec_mul(vec v1, vec v2) {
  return (const vec) {v1.x * v2.x, v1.y * v2.y};
}

vec vec_div(vec v1, vec v2) {
  return (const vec) {v1.x / v2.x, v1.y / v2.y};
}

vec vec_add_f(vec v, float val) {
  return (const vec) {v.x + val, v.y + val};
}

vec vec_sub_f(vec v, float val) {
  return (const vec) {v.x - val, v.y - val};
}

vec vec_mul_f(vec v, float val) {
  return (const vec) {v.x * val, v.y * val};
}

vec vec_div_f(vec v, float val) {
  return (const vec) {v.x / val, v.y / val};
}

float vec_norm(vec v) {
  return sqrtf(v.x * v.x + v.y * v.y);
}

vec vec_middle(vec v1, vec v2) {
  return vec_div_f(vec_add(v1, v2), 2.f);
}

vec vec_normalize(vec v) {
  float n = vec_norm(v);
  return (vec) {v.x / n, v.y / n};
}

vec vec_normal(vec v) {
  return (vec) {v.y, -v.x};
}

float vec_dist(vec v1, vec v2) {
  const vec sub = vec_sub(v1, v2);
  return vec_norm(sub);
}

float vec_dist2(vec v1, vec v2) {
  const vec sub = vec_sub(v1, v2);
  return sub.x * sub.x + sub.y * sub.y;
}

float vec_det(vec v1, vec v2) {
  return v1.x * v2.y - v1.y * v2.x;
}

float dev_dot(vec v1, vec v2) {
  return v1.x * v2.x + v1.y * v2.y;
}

vec vec_rotate(vec v, float val) {
  float new_x = cosf(val) * v.x - sinf(val) * v.y;
  float new_y = sinf(val) * v.x + cosf(val) * v.y;
  return (vec) {new_x, new_y};
}

bool vec_eq(vec v1, vec v2) {
  return v1.x == v2.x && v1.y == v2.y;
}
