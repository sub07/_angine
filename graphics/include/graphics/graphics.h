#pragma once

#include <stdbool.h>

typedef void *(*ProcFuncLoader)(const char *name);
typedef unsigned int Handle;

// Common
bool load_gl(bool use_pre_callback);
bool load_gl_from_loader(ProcFuncLoader loader, bool use_pre_callback);
void set_viewport(int width, int height);
const char *gl_version();

// Screen
void clear_screen();
void set_clear_color(float r, float g, float b, float a);

// Vbo
enum buffer_type { Dynamic, Static };

Handle create_buffer(void *data, int size, enum buffer_type type);
void upload_data_buffer(Handle vbo, void *data, int size, long long int offset);
void bind_as_indices_buffer(Handle ibo);
void delete_buffer(Handle buffer);

// Vao
Handle create_vao(int n, int *strides, long int *offsets, int *sizes,
                  Handle vbo);
void bind_vao(Handle vao);
void delete_vao(Handle vao);

// Texture
enum filter_t { Nearest, Linear };

Handle create_texture(enum filter_t filter, int width, int height,
                      int nb_channel, void *data);
void bind_texture_unit(Handle texture, unsigned int texture_unit);
void delete_texture(Handle texture);

// Shader
Handle create_shader(const char *vertex_source, const char *fragment_source,
                     char *vertex_compilation_error,
                     char *fragment_compilation_error,
                     int vertex_compilation_error_buffer_size,
                     int fragment_compilation_error_buffer_size);
void use_shader(Handle shader);
void send_int_shader(Handle shader, const char *name, int value);
void send_float_shader(Handle shader, const char *name, float value);
void send_matrix3_shader(Handle shader, const char *name, float *mat);
void send_vec2_shader(Handle shader, const char *name, float x, float y);
void send_vec4_shader(Handle shader, const char *name, float r, float g,
                      float b, float a);
void delete_shader(Handle shader);

// Draw
enum draw_primitive { TriangleStrip, LineStrip, Lines, Triangles };

void draw(enum draw_primitive primitive, int nb_vertices);
void draw_indices(enum draw_primitive primitive, int nb_index);

// Alpha blending
void enable_alpha_blending();
void disable_alpha_blending();
