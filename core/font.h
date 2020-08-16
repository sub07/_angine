#pragma once

#include <maths/vec.h>

#define nb_char 590

typedef struct {
  Rect sub_texture;
  Vec advance;
  Vec offset;
} Glyph;

typedef struct Font {
  Texture *texture_atlas;
  Glyph glyphs[nb_char];
} Font;

Vec font_string_size_bottom(Font *font, const char *string, float *bottom_out);
