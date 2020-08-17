#pragma once

#include <stdbool.h>
#include <graphics/graphics.h>

typedef struct Mesh Mesh;

Mesh *mesh_create(int capacity);
void mesh_free(Mesh *mesh);
void mesh_submit_gpu(Mesh *mesh);
void mesh_clear(Mesh *mesh);
int mesh_size_remaining(Mesh *mesh);
int mesh_size(Mesh *mesh);
void mesh_add(Mesh *mesh, float *data, int size);
Handle mesh_gpu_buffer(Mesh *mesh);
