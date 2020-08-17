#include "polygon_batch.h"
#include "mesh.h"
#include "shader.h"
#include <stdlib.h>

static const int p_nb_component_vao = 2;
static const int vertex_size = 2;
static const int color_size = 4;
static const int nb_float_per_vertex = vertex_size + color_size;

static long offsets[] = {
    0,
    vertex_size * (int) sizeof(float),
};
static int strides[] = {
    nb_float_per_vertex * (int) sizeof(float),
    nb_float_per_vertex * (int) sizeof(float),
};
static int sizes[] = {
    vertex_size,
    color_size
};

typedef enum {
  Fill,
  Stroke
} RenderMode;

typedef struct PolygonBatch {
  bool drawing;
  Mesh *vertices;
  Handle vao;
  Shader s;
  Color fill;
  Color stroke;
  int count;
  bool alpha_blending;
  RenderMode render_mode;
} PolygonBatch;

PolygonBatch *p_batch_create(Shader shape_shader) {
  PolygonBatch *p = malloc(sizeof(PolygonBatch));
  p->drawing = false;
  int nb_vertices = 5000;
  p->vertices = mesh_create(nb_vertices * nb_float_per_vertex);
  p->vao = create_vao(p_nb_component_vao, strides, offsets, sizes, mesh_gpu_buffer(p->vertices));
  p->s = shape_shader;
  p->count = 0;
  p_batch_stroke_color(p, color_white);
  p_batch_fill_color(p, color_white);
  p->alpha_blending = false;
  p->render_mode = Fill;
  return p;
}

static void flush(PolygonBatch *p) {
  if (p->count == 0) return;
  use_shader(p->s);
  bind_vao(p->vao);
  mesh_submit_gpu(p->vertices);
  if (p->alpha_blending) {
    enable_alpha_blending();
  } else {
    disable_alpha_blending();
  }
  draw(p->render_mode == Fill ? Triangles : Lines, p->count);
  p->count = 0;
  mesh_clear(p->vertices);
}

void p_batch_free(PolygonBatch *p) {
  mesh_free(p->vertices);
  delete_vao(p->vao);
  free(p);
}

void p_batch_begin(PolygonBatch *p) {
  if (p->drawing) { log_abort("call end before calling begin (PolygonBatch)"); }
  p->drawing = true;
}

void p_batch_end(PolygonBatch *p) {
  if (!p->drawing) { log_abort("call begin before calling end (PolygonBatch)"); }
  p->drawing = false;
  flush(p);
}

void p_batch_stroke_color(PolygonBatch *p, Color new_color) {
  p->stroke = new_color;
}

void p_batch_fill_color(PolygonBatch *p, Color new_color) {
  p->fill = new_color;
}

void p_batch_enable_alpha_blending(PolygonBatch *p) {
  if (p->drawing && !p->alpha_blending) {
    flush(p);
  }
  p->alpha_blending = true;
}

void p_batch_disable_alpha_blending(PolygonBatch *p) {
  if (p->drawing && p->alpha_blending) {
    flush(p);
  }
  p->alpha_blending = false;
}

void set_render_mode(PolygonBatch *p, RenderMode new_render_mode) {
  if (p->render_mode != new_render_mode) {
    flush(p);
    p->render_mode = new_render_mode;
  }
}

void p_batch_draw_polygon(PolygonBatch *p, float *vertices, int nb_vertex, Transform *transform) {
  set_render_mode(p, Stroke);
}

void p_batch_draw_polyline(PolygonBatch *p, float *vertices, int nb_vertex, Transform *transform) {
  set_render_mode(p, Stroke);
}

void p_batch_draw_rect(PolygonBatch *p, Vec size, Transform *transform) {
  set_render_mode(p, Stroke);
  int nb_vert = 8;
  int nb_float = nb_vert * nb_float_per_vertex;
  float vertices[nb_float];
  
  Vec p1 = {0, 0};
  Vec p2 = {size.x, 0};
  Vec p3 = {size.x, size.y};
  Vec p4 = {0, size.y};
  
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
  
  Color col = p->stroke;
  
  vertices[0] = p1.x;
  vertices[1] = p1.y;
  vertices[2] = col.r;
  vertices[3] = col.g;
  vertices[4] = col.b;
  vertices[5] = col.a;
  
  vertices[6] = p2.x;
  vertices[7] = p2.y;
  vertices[8] = col.r;
  vertices[9] = col.g;
  vertices[10] = col.b;
  vertices[11] = col.a;
  
  vertices[12] = p2.x;
  vertices[13] = p2.y;
  vertices[14] = col.r;
  vertices[15] = col.g;
  vertices[16] = col.b;
  vertices[17] = col.a;
  
  vertices[18] = p3.x;
  vertices[19] = p3.y;
  vertices[20] = col.r;
  vertices[21] = col.g;
  vertices[22] = col.b;
  vertices[23] = col.a;
  
  vertices[24] = p3.x;
  vertices[25] = p3.y;
  vertices[26] = col.r;
  vertices[27] = col.g;
  vertices[28] = col.b;
  vertices[29] = col.a;
  
  vertices[30] = p4.x;
  vertices[31] = p4.y;
  vertices[32] = col.r;
  vertices[33] = col.g;
  vertices[34] = col.b;
  vertices[35] = col.a;
  
  vertices[36] = p4.x;
  vertices[37] = p4.y;
  vertices[38] = col.r;
  vertices[39] = col.g;
  vertices[40] = col.b;
  vertices[41] = col.a;
  
  vertices[42] = p1.x;
  vertices[43] = p1.y;
  vertices[44] = col.r;
  vertices[45] = col.g;
  vertices[46] = col.b;
  vertices[47] = col.a;
  
  mesh_add(p->vertices, vertices, nb_float);
  p->count += nb_vert;
}

void p_batch_draw_ellipse(PolygonBatch *p, Vec size, Transform *transform) {
  set_render_mode(p, Stroke);
}

void p_batch_draw_line(PolygonBatch *p, Vec v1, Vec v2, Transform *transform) {
  set_render_mode(p, Stroke);
}

void p_batch_fill_polygon(PolygonBatch *p, float *vertices, int nb_vertex, Transform *transform) {
  set_render_mode(p, Fill);
}

void p_batch_fill_polyline(PolygonBatch *p, float *vertices, int nb_vertex, Transform *transform) {
  set_render_mode(p, Fill);
}

void p_batch_fill_rect(PolygonBatch *p, Vec size, Transform *transform) {
  set_render_mode(p, Fill);
}

void p_batch_fill_ellipse(PolygonBatch *p, Vec size, Transform *transform) {
  set_render_mode(p, Fill);
}
