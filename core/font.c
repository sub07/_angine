#include <core/font.h>
#include <stdlib.h>
#include <core/texture.h>
#include "font.h"
#include <freetype/freetype.h>
#include <utils/log.h>
#include <float.h>

Font *font_create(const char *path, int font_size) {
  Font *f = malloc(sizeof(Font));
  FT_Library lib;
  if (FT_Init_FreeType(&lib)) { log_abort("Freetype failed to load"); }
  FT_Face face;
  if (FT_New_Face(lib, path, 0, &face)) { log_abort("Unable to load font at %s", path); }
  if (FT_Set_Pixel_Sizes(face, 0, font_size)) { log_abort("Unable to set font size"); }
  
  u32 total_width = 0;
  u32 max_height = 0;
  
  for (int c = 0; c < nb_char; c++) {
    if (FT_Load_Char(face, c, FT_LOAD_RENDER)) { log_abort("Unable to load char %c (%d)", c, c); }
    u32 h = face->glyph->bitmap.rows;
    total_width += face->glyph->bitmap.width;
    if (max_height < h) max_height = h;
    
  }
  
  Image *atlas_builder = image_create(total_width, max_height, R8);
  
  int x = 0;
  for (int c = 0; c < nb_char; c++) {
    FT_Load_Char(face, c, FT_LOAD_RENDER);
    u32 w = face->glyph->bitmap.width;
    u32 h = face->glyph->bitmap.rows;
    u8 *buffer = face->glyph->bitmap.buffer;
    Glyph g;
    g.sub_texture.position.x = (float) x;
    g.sub_texture.position.y = 0;
    g.sub_texture.size.x = (float) w;
    g.sub_texture.size.y = (float) h;
    g.offset.x = face->glyph->bitmap_left;
    g.offset.y = face->glyph->bitmap_top;
    g.advance.x = (float) face->glyph->advance.x / 64;
    g.advance.y = (float) face->glyph->advance.y / 64;
    f->glyphs[c] = g;
    if (buffer != null) {
      Image glyph_img = {buffer, w, h, R8};
      image_draw_image(atlas_builder, &glyph_img, x, 0);
    }
    x += w;
  }
  
  FT_Done_Face(face);
  FT_Done_FreeType(lib);
  
  f->texture_atlas = texture_create_img(atlas_builder);
  image_free(atlas_builder);
  return f;
}

Vec font_string_size(Font *font, const char *s) {
  return font_string_size_bottom(font, s, null);
}

Vec font_string_size_bottom(Font *font, const char *s, float *bottom_out) {
  float w = 0;
  float top = 0;
  float bottom = 0;
  size_t len = strlen(s);
  for (size_t i = 0; i < len; i++) {
    Glyph g = font->glyphs[s[i]];
    w += g.advance.x;
    if (g.offset.y > top) top = g.offset.y;
    if (g.offset.y - g.sub_texture.size.y < bottom) bottom = g.offset.y - g.sub_texture.size.y;
  }
  
  if (bottom_out != null) *bottom_out = bottom;
  
  return (Vec) {w, top - bottom};
}

void font_free(Font *font) {
  texture_free(font->texture_atlas);
  free(font);
}
