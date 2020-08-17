#include <graphics/graphics.h>
#include <stdarg.h>
#include <stdio.h>
#include <glad/glad.h>

void gladPostCallback(const char *name, void *funcPtr, int len_args, ...) {
  unsigned int err = glad_glGetError();
  if (err != GL_NO_ERROR) {
    const char *errorString;
    switch (err) {
    case GL_INVALID_ENUM:
      errorString = "GL_INVALID_ENUM";
      break;
    case GL_INVALID_VALUE:
      errorString = "GL_INVALID_VALUE";
      break;
    case GL_INVALID_OPERATION:
      errorString = "GL_INVALID_OPERATION";
      break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      errorString = "GL_INVALID_FRAMEBUFFER_OPERATION";
      break;
    case GL_OUT_OF_MEMORY:
      errorString = "GL_OUT_OF_MEMORY";
      break;
    case GL_STACK_UNDERFLOW:
      errorString = "GL_STACK_UNDERFLOW";
      break;
    case GL_STACK_OVERFLOW:
      errorString = "GL_STACK_OVERFLOW";
      break;
    default:
      errorString = "UNEXPECTED";
    }
    va_list args;
    va_start(args, len_args);
    fprintf(stderr, "Error %s in function %s(", errorString, name);
    for (int i = 0; i < len_args; i++) {
      if (i == len_args - 1)
        fprintf(stderr, "%d)\n", va_arg(args, int));
      else
        fprintf(stderr, "%d, ", va_arg(args, int));
    }
    fflush(stderr);
    va_end(args);
  }
}

void gladPreCallback(const char *name, void *funcPtr, int len_args, ...) {
  va_list args;
  va_start(args, len_args);
  fprintf(stderr, "%s(", name);
  for (int i = 0; i < len_args; i++) {
    if (i == len_args - 1)
      fprintf(stderr, "%d)\n", va_arg(args, int));
    else
      fprintf(stderr, "%d, ", va_arg(args, int));
  }
  fflush(stderr);
  va_end(args);
}

bool load_gl(bool use_pre_callback) {
  if (!gladLoadGL()) {
    return false;
  }
#ifndef NDEBUG
  glad_set_post_callback(gladPostCallback);
  if (use_pre_callback) {
    glad_set_pre_callback(gladPreCallback);
  }
#endif
  return true;
}

bool load_gl_from_loader(ProcFuncLoader loader, bool use_pre_callback) {
  if (!gladLoadGLLoader((GLADloadproc) loader)) {
    return false;
  }
#ifndef NDEBUG
  glad_set_post_callback(gladPostCallback);
  if (use_pre_callback) {
    glad_set_pre_callback(gladPreCallback);
  }
#endif
  return true;
}

void set_viewport(int width, int height) {
  glViewport(0, 0, width, height);
}

const char *gl_version() { return (const char *) glGetString(GL_VERSION); }

void clear_screen() {
  glClear(GL_COLOR_BUFFER_BIT);
}

void set_clear_color(float r, float g, float b, float a) {
  glClearColor(r, g, b, a);
}

GLenum gl_enum_from_buffer_type(enum buffer_type type) {
  switch (type) {
  case Dynamic:
    return GL_DYNAMIC_DRAW;
  case Static:
    return GL_STATIC_DRAW;
  default:
    return 0;
  }
}

Handle create_buffer(void *data, int size, enum buffer_type type) {
  Handle vbo;
  glCreateBuffers(1, &vbo);
  glNamedBufferData(vbo, size, data, gl_enum_from_buffer_type(type));
  return vbo;
}

void upload_data_buffer(Handle vbo, void *data, int size, long long int offset) {
  glNamedBufferSubData(vbo, offset, size, data);
}

Handle bound_ibo = 0;

void bind_as_indices_buffer(Handle ibo) {
  if (bound_ibo != ibo) {
    bound_ibo = ibo;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  }
}

void delete_buffer(Handle buffer) {
  glDeleteBuffers(1, &buffer);
}

Handle create_vao(int n, int *strides, long int *offsets, int *sizes,
                  Handle vbo) {
  Handle vao;
  glCreateVertexArrays(1, &vao);
  
  for (int i = 0; i < n; i++) {
    glEnableVertexArrayAttrib(vao, i);
    glVertexArrayVertexBuffer(vao, i, vbo, offsets[i], strides[i]);
    glVertexArrayAttribFormat(vao, i, sizes[i], GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(vao, i, i);
  }
  
  return vao;
}

Handle bound_vao = 0;

void bind_vao(Handle vao) {
  if (bound_vao != vao) {
    bound_vao = vao;
    glBindVertexArray(vao);
  }
}

void delete_vao(Handle vao) {
  glDeleteVertexArrays(1, &vao);
}

GLenum internalStorageFromNbChannel(int nbChannel) {
  switch (nbChannel) {
  case 1:
    return GL_R8;
  case 2:
    return GL_RG8;
  case 3:
    return GL_RGB8;
  default:
    return GL_RGBA8;
  }
}

GLenum externalStorageFromNbChannel(int nbChannel) {
  switch (nbChannel) {
  case 1:
    return GL_RED;
  case 2:
    return GL_RG;
  case 3:
    return GL_RGB;
  default:
    return GL_RGBA;
  }
}

int alignmentFromNbChannel(int nbChannel) {
  switch (nbChannel) {
  case 1:
    return 1;
  case 2:
    return 2;
  case 3:
    return 1;
  case 4:
    return 4;
  default:
    return GL_RGBA;
  }
}

Handle create_texture(enum filter_t filter, int width, int height,
                      int nb_channel, void *data) {
  Handle tex;
  glPixelStorei(GL_UNPACK_ALIGNMENT, alignmentFromNbChannel(nb_channel));
  glCreateTextures(GL_TEXTURE_2D, 1, &tex);
  glTextureParameteri(tex, GL_TEXTURE_MIN_FILTER,
                      filter == Nearest ? GL_NEAREST : GL_LINEAR);
  glTextureParameteri(tex, GL_TEXTURE_MAG_FILTER,
                      filter == Nearest ? GL_NEAREST : GL_LINEAR);
  glTextureStorage2D(tex, 1, internalStorageFromNbChannel(nb_channel), width,
                     height);
  glTextureSubImage2D(tex, 0, 0, 0, width, height,
                      externalStorageFromNbChannel(nb_channel), GL_UNSIGNED_BYTE,
                      data);
  return tex;
}

void bind_texture_unit(Handle texture, unsigned int texture_unit) {
  glBindTextureUnit(texture_unit, texture);
}

void delete_texture(Handle texture) {
  glDeleteTextures(1, &texture);
}

bool checkCompileLog(Handle shader, char *buffer, int bufferSize) {
  if (buffer != NULL) {
    int compileStatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus == GL_FALSE) {
      glGetShaderInfoLog(shader, bufferSize, 0, buffer);
      return false;
    }
  }
  return true;
}

Handle create_shader(const char *vertex_source, const char *fragment_source,
                     char *vertex_compilation_error,
                     char *fragment_compilation_error,
                     int vertex_compilation_error_buffer_size,
                     int fragment_compilation_error_buffer_size) {
  Handle vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vertex_source, 0);
  glCompileShader(vs);
  bool vertexSuccess = checkCompileLog(vs, vertex_compilation_error,
                                       vertex_compilation_error_buffer_size);
  
  Handle fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fragment_source, 0);
  glCompileShader(fs);
  bool fragmentSuccess = checkCompileLog(fs, fragment_compilation_error,
                                         fragment_compilation_error_buffer_size);
  
  Handle program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glDeleteShader(vs);
  glDeleteShader(fs);
  
  return vertexSuccess && fragmentSuccess ? program : 0u;
}

Handle bound_shader = 0;

void use_shader(Handle shader) {
  if (bound_shader != shader) {
    bound_shader = shader;
    glUseProgram(shader);
  }
}

void send_int_shader(Handle shader, const char *name, int value) {
  unsigned int location = glGetUniformLocation(shader, name);
  glUniform1i(location, value);
}

void send_float_shader(Handle shader, const char *name, float value) {
  unsigned int location = glGetUniformLocation(shader, name);
  glUniform1f(location, value);
}

void send_matrix3_shader(Handle shader, const char *name, float *mat) {
  unsigned int location = glGetUniformLocation(shader, name);
  glUniformMatrix3fv(location, 1, GL_FALSE, mat);
}

void send_vec2_shader(Handle shader, const char *name, float x, float y) {
  unsigned int location = glGetUniformLocation(shader, name);
  glUniform2f(location, x, y);
}

void send_vec4_shader(Handle shader, const char *name, float r, float g,
                      float b, float a) {
  unsigned int location = glGetUniformLocation(shader, name);
  glUniform4f(location, r, g, b, a);
}

void delete_shader(Handle shader) {
  glDeleteProgram(shader);
}

GLenum primitive_from_enum(enum draw_primitive p) {
  switch (p) {
  case TriangleStrip:
    return GL_TRIANGLE_STRIP;
  case LineStrip:
    return GL_LINE_STRIP;
  case Lines:
    return GL_LINES;
  case Triangles:
    return GL_TRIANGLES;
  default:
    return 0;
  }
}

void draw(enum draw_primitive primitive, int nb_vertices) {
  glDrawArrays(primitive_from_enum(primitive), 0, nb_vertices);
}

void draw_indices(enum draw_primitive primitive, int nb_index) {
  glDrawElements(primitive_from_enum(primitive), nb_index, GL_UNSIGNED_INT, 0);
}

bool alpha_blending_enabled = false;

void enable_alpha_blending() {
  if (!alpha_blending_enabled) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    alpha_blending_enabled = true;
  }
}

void disable_alpha_blending() {
  if (alpha_blending_enabled) {
    alpha_blending_enabled = false;
    glDisable(GL_BLEND);
  }
}
