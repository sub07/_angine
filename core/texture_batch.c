#include <core/texture_batch.h>
#include "texture_batch.h"
#include "mesh.h"
#include "texture.h"
#include "font.h"
#include <stdlib.h>
#include <string.h>

#define CHECK_DRAWING(b) { if (!(b)->drawing) { log_abort("You must call batch_begin() to start drawing"); } }

enum Operation {
  OpText,
  OpTexture
};

typedef struct TextureBatch {
  Mesh *mesh;
  bool use_alpha_blending;
  Handle ibo;
  Handle vao;
  bool drawing;
  Texture *last_texture_used;
  Shader texture_shader;
  Shader text_shader;
  Color colors[4];
  int texture_counter;
  enum Operation current_operation;
} TextureBatch;

static const int nb_component_vao = 3;
static const int vertex_size = 2;
static const int texture_coord_size = 2;
static const int color_size = 4;
static const int nb_float_per_texture_point = vertex_size + texture_coord_size + color_size;

static long offsets[] = {
    0,
    vertex_size * (int) sizeof(float),
    (vertex_size + texture_coord_size) * (int) sizeof(float)
};
static int strides[] = {
    nb_float_per_texture_point * (int) sizeof(float),
    nb_float_per_texture_point * (int) sizeof(float),
    nb_float_per_texture_point * (int) sizeof(float)
};
static int sizes[] = {
    vertex_size,
    texture_coord_size,
    color_size
};

TextureBatch *batch_create(Shader texture_shader, Shader text_shader) {
  TextureBatch *t = malloc(sizeof(TextureBatch));
  t->texture_shader = texture_shader;
  t->text_shader = text_shader;
  t->last_texture_used = null;
  t->current_operation = OpTexture;
  int nb_texture = 5000;
  t->mesh = mesh_create(nb_texture * nb_float_per_texture_point * 4);
  t->use_alpha_blending = false;
  t->drawing = false;
  t->texture_counter = 0;
  batch_set_color(t, color_white);
  t->vao = create_vao(nb_component_vao, strides, offsets, sizes, mesh_gpu_buffer(t->mesh));
  u32 indices[nb_texture * 6];
  int index = 0;
  for (int i = 0; i < nb_texture * 4; i += 4) {
    indices[index++] = i;
    indices[index++] = i + 1;
    indices[index++] = i + 2;
    indices[index++] = i + 2;
    indices[index++] = i + 1;
    indices[index++] = i + 3;
  }
  t->ibo = create_buffer(indices, (int) sizeof(indices), Static);
  return t;
}

void batch_free(TextureBatch *batch) {
  delete_buffer(batch->ibo);
  delete_vao(batch->vao);
  mesh_free(batch->mesh);
  free(batch);
}

void batch_begin(TextureBatch *batch) {
  batch->drawing = true;
}

static void flush(TextureBatch *b) {
  if (b->texture_counter == 0) return;
  bind_texture_unit(texture_handle(b->last_texture_used), 0);
  use_shader(b->current_operation == OpTexture ? b->texture_shader : b->text_shader);
  bind_vao(b->vao);
  bind_as_indices_buffer(b->ibo);
  mesh_submit_gpu(b->mesh);
  if (b->use_alpha_blending) {
    enable_alpha_blending();
  } else {
    disable_alpha_blending();
  }
  draw_indices(Triangles, b->texture_counter * 6);
  b->texture_counter = 0;
  mesh_clear(b->mesh);
}

void batch_end(TextureBatch *batch) {
  flush(batch);
  batch->drawing = false;
}

void batch_set_colors(TextureBatch *batch, Color c1, Color c2, Color c3, Color c4) {
  batch->colors[0] = c1;
  batch->colors[1] = c2;
  batch->colors[2] = c3;
  batch->colors[3] = c4;
}

void batch_set_color(TextureBatch *batch, Color new_color) {
  batch->colors[0] = new_color;
  batch->colors[1] = new_color;
  batch->colors[2] = new_color;
  batch->colors[3] = new_color;
}

void batch_texture_private(TextureBatch *b, Texture *tex, Transform *transform, Rect *sub_tex) {
  CHECK_DRAWING(b)
  if (tex == null) return;
  
  if (tex != b->last_texture_used) {
    flush(b);
    b->last_texture_used = tex;
  }
  
  b->texture_counter++;
  int size = 4 * nb_float_per_texture_point;
  float vertices[size];
  
  float w = sub_tex == null ? tex->width : sub_tex->size.x;
  float h = sub_tex == null ? tex->height : sub_tex->size.y;
  
  Vec p1 = {0, 0};
  Vec p2 = {w, 0};
  Vec p3 = {0, h};
  Vec p4 = {w, h};
  
  p1 = vec_sub(p1, transform->origin);
  p2 = vec_sub(p2, transform->origin);
  p3 = vec_sub(p3, transform->origin);
  p4 = vec_sub(p4, transform->origin);
  
  p1 = vec_mul(p1, transform->scale);
  p2 = vec_mul(p2, transform->scale);
  p3 = vec_mul(p3, transform->scale);
  p4 = vec_mul(p4, transform->scale);
  
  p1 = vec_rotate(p1, transform->rotate);
  p2 = vec_rotate(p2, transform->rotate);
  p3 = vec_rotate(p3, transform->rotate);
  p4 = vec_rotate(p4, transform->rotate);
  
  p1 = vec_add(p1, transform->translate);
  p2 = vec_add(p2, transform->translate);
  p3 = vec_add(p3, transform->translate);
  p4 = vec_add(p4, transform->translate);
  
  float start_u = sub_tex == null ? 0 : sub_tex->position.x / tex->width;
  float end_u = sub_tex == null ? 1 : (sub_tex->position.x + sub_tex->size.x) / tex->width;
  float start_v = sub_tex == null ? 0 : sub_tex->position.y / tex->height;
  float end_v = sub_tex == null ? 1 : (sub_tex->position.y + sub_tex->size.y) / tex->height;
  
  vertices[0] = p1.x;
  vertices[1] = p1.y;
  vertices[2] = start_u;
  vertices[3] = start_v;
  vertices[4] = b->colors[0].r;
  vertices[5] = b->colors[0].g;
  vertices[6] = b->colors[0].b;
  vertices[7] = b->colors[0].a;
  
  vertices[8] = p2.x;
  vertices[9] = p2.y;
  vertices[10] = end_u;
  vertices[11] = start_v;
  vertices[12] = b->colors[1].r;
  vertices[13] = b->colors[1].g;
  vertices[14] = b->colors[1].b;
  vertices[15] = b->colors[1].a;
  
  vertices[16] = p3.x;
  vertices[17] = p3.y;
  vertices[18] = start_u;
  vertices[19] = end_v;
  vertices[20] = b->colors[2].r;
  vertices[21] = b->colors[2].g;
  vertices[22] = b->colors[2].b;
  vertices[23] = b->colors[2].a;
  
  vertices[24] = p4.x;
  vertices[25] = p4.y;
  vertices[26] = end_u;
  vertices[27] = end_v;
  vertices[28] = b->colors[3].r;
  vertices[29] = b->colors[3].g;
  vertices[30] = b->colors[3].b;
  vertices[31] = b->colors[3].a;
  
  mesh_add(b->mesh, vertices, size);
}

void batch_texture(TextureBatch *b, Texture *tex, Transform *transform, Rect *sub_texture) {
  CHECK_DRAWING(b)
  if (b->current_operation != OpTexture) {
    flush(b);
    b->current_operation = OpTexture;
  }
  batch_texture_private(b, tex, transform, sub_texture);
}

void batch_string(TextureBatch *b, Font *font, const char *s, Transform transform) {
  CHECK_DRAWING(b)
  if (b->current_operation != OpText) {
    flush(b);
    b->current_operation = OpText;
  }
  float bottom;
  Vec string_size = font_string_size_bottom(font, s, &bottom);
  size_t len = strlen(s);
  Vec origin = transform.origin;
  for (size_t i = 0; i < len; i++) {
    Glyph g = font->glyphs[s[i]];
    Transform t = transform;
    t.origin = origin;
    t.origin.x -= g.offset.x;
    t.origin.y -= string_size.y - g.offset.y + bottom;
    batch_texture_private(b, font->texture_atlas, &t, &g.sub_texture);
    origin = vec_sub(origin, g.advance);
  }
}

void batch_enable_alpha_blending(TextureBatch *b) {
  if (b->drawing && !b->use_alpha_blending) {
    flush(b);
  }
  b->use_alpha_blending = true;
}

void batch_disable_alpha_blending(TextureBatch *b) {
  if (b->drawing && b->use_alpha_blending) {
    flush(b);
  }
  b->use_alpha_blending = false;
}
