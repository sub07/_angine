#include <core/font.h>
#include <stdlib.h>
#include <core/texture.h>
#include "font.h"
#include <ft2build.h>
#include <freetype/freetype.h>
#include <utils/log.h>

#define nb_char 591

typedef struct Font {
  Texture *texture_atlas;
  Glyph glyphs[nb_char];
} Font;

Font *font_create(const char *path, int font_size) {
  Font *f = malloc(sizeof(Font));
  FT_Library lib;
  if (FT_Init_FreeType(&lib)) { log_abort("Freetype failed to load"); }
  FT_Face face;
  if (FT_New_Face(lib, path, 0, &face)) { log_abort("Unable to load font at %s", path); }
  if (FT_Set_Pixel_Sizes(face, 0, font_size)) { log_abort("Unable to set font size"); }
  
  u32 total_width = 0;
  u32 max_height = 0;
  int top = INT32_MIN;
  int bottom = INT32_MAX;
  for (int c = 0; c < nb_char; c++) {
    if (FT_Load_Char(face, c, FT_LOAD_RENDER)) { log_abort("Unable to load char %c (%d)", c, c); }
    u32 w = face->glyph->bitmap.width;
    u32 h = face->glyph->bitmap.rows;
    total_width += w;
    if (h > max_height) max_height = h;
    if (face->glyph->bitmap_top > top) top = face->glyph->bitmap_top;
    if (face->glyph->bitmap_top - h < bottom) bottom = face->glyph->bitmap_top - h;
  }
  
  Image *atlas_builder = image_create(total_width, max_height, R8);
  
  int x = 0;
  for (int c = 0; c < nb_char; c++) {
    FT_Load_Char(face, c, FT_LOAD_RENDER);
    u32 w = face->glyph->bitmap.width;
    u32 h = face->glyph->bitmap.rows;
    u8 *buffer = face->glyph->bitmap.buffer;
    Glyph g;
    g.x = (float) x;
    g.y = 0;
    g.w = (float) w;
    g.h = (float) h;
    g.offset.x = face->glyph->bitmap_left;
    g.offset.y = face->glyph->bitmap_top;
    g.advance.x = (float) face->glyph->advance.x / 64;
    g.advance.y = (float) face->glyph->advance.y / 64;
    f->glyphs[c] = g;
    if (buffer != null) {
      Image glyph_img = {buffer, w, h, R8};
      image_draw_image(atlas_builder, &glyph_img, x, (int) max_height - ((int) g.offset.y + bottom));
    }
    x += w;
  }
  
  FT_Done_Face(face);
  FT_Done_FreeType(lib);
  
  f->texture_atlas = texture_create_img(atlas_builder);
  image_free(atlas_builder);
  return f;
}

void font_free(Font *font) {
  texture_free(font->texture_atlas);
  free(font);
}
