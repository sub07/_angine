#pragma once

#include <maths/vec.h>

typedef struct {
  float x;
  float y;
  float w;
  float h;
  Vec advance;
  Vec offset;
} Glyph;
