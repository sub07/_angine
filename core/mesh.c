#include "mesh.h"
#include <stdlib.h>
#include <utils/types.h>
#include <utils/log.h>
#include <string.h>

typedef struct Mesh {
  Handle vbo;
  float *data;
  int current_size;
  int capacity;
} Mesh;

Mesh *mesh_create(int capacity) {
  Mesh *m = malloc(sizeof(Mesh));
  m->data = malloc(capacity * sizeof(float));
  m->current_size = 0;
  m->capacity = capacity;
  m->vbo = create_buffer(null, capacity * (int) sizeof(float), Dynamic);
  return m;
}

void mesh_free(Mesh *m) {
  free(m->data);
  delete_buffer(m->vbo);
  free(m);
}

void mesh_submit_gpu(Mesh *m) {
  upload_data_buffer(m->vbo, m->data, m->current_size * (int) sizeof(float), 0);
}

void mesh_clear(Mesh *m) {
  m->current_size = 0;
}

int mesh_size_remaining(Mesh *m) {
  return m->capacity - m->current_size;
}

void mesh_add(Mesh *m, float *data, int size) {
  if (m->current_size + size >= m->capacity) {
    log_abort("mesh overflow %d(mesh current size) + %d(input size) >= %d(mesh capacity)",
              m->current_size,
              size,
              m->current_size);
  }
  memcpy(m->data + m->current_size, data, size * sizeof(float));
  m->current_size += size;
}

Handle mesh_gpu_buffer(Mesh *mesh) {
  return mesh->vbo;
}

int mesh_size(Mesh *mesh) {
  return mesh->current_size;
}
