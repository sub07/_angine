#pragma once

#include <stdbool.h>

#define GRAPHIC_API __declspec(dllexport)

typedef void *(*ProcFuncLoader)(const char *name);
typedef unsigned int handle_t;

// Common
GRAPHIC_API bool load_gl(bool use_pre_callback);
GRAPHIC_API bool load_gl_from_loader(ProcFuncLoader loader, bool use_pre_callback);
GRAPHIC_API void set_viewport(int width, int height);
GRAPHIC_API const char *gl_version();

// Screen
GRAPHIC_API void clear_screen();
GRAPHIC_API void set_clear_color(float r, float g, float b, float a);

// Vbo
enum buffer_type { Dynamic, Static };

GRAPHIC_API handle_t create_buffer(void *data, int size, enum buffer_type type);
GRAPHIC_API void upload_data_buffer(handle_t vbo, void *data, int size, long long int offset);
GRAPHIC_API void bind_as_indices_buffer(handle_t ibo);
GRAPHIC_API void delete_buffer(handle_t buffer);

// Vao
GRAPHIC_API handle_t create_vao(int n, int *strides, long int *offsets, int *sizes,
                                handle_t vbo);
GRAPHIC_API void bind_vao(handle_t vao);
GRAPHIC_API void delete_vao(handle_t vao);

// Texture
enum filter_t { Nearest, Linear };

GRAPHIC_API handle_t create_texture(enum filter_t filter, int width, int height,
                                    int nb_channel, void *data);
GRAPHIC_API void bind_texture_unit(handle_t texture, unsigned int texture_unit);
GRAPHIC_API void delete_texture(handle_t texture);

// Shader
GRAPHIC_API handle_t create_shader(const char *vertex_source, const char *fragment_source,
                                   char *vertex_compilation_error,
                                   char *fragment_compilation_error,
                                   int vertex_compilation_error_buffer_size,
                                   int fragment_compilation_error_buffer_size);
GRAPHIC_API void use_shader(handle_t shader);
GRAPHIC_API void send_int_shader(handle_t shader, const char *name, int value);
GRAPHIC_API void send_float_shader(handle_t shader, const char *name, float value);
GRAPHIC_API void send_matrix3_shader(handle_t shader, const char *name, float *mat);
GRAPHIC_API void send_vec2_shader(handle_t shader, const char *name, float x, float y);
GRAPHIC_API void send_vec4_shader(handle_t shader, const char *name, float r, float g,
                                  float b, float a);
GRAPHIC_API void delete_shader(handle_t shader);

// Draw
enum draw_primitive { TriangleStrip, LineStrip, LineLoop, Triangles };

GRAPHIC_API void draw(enum draw_primitive primitive, int nb_vertices);
GRAPHIC_API void draw_indices(enum draw_primitive primitive, int nb_index);

// Alpha blending
GRAPHIC_API void enable_alpha_blending();
GRAPHIC_API void disable_alpha_blending();
