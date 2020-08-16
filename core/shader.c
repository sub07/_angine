#include <utils/types.h>
#include "shader.h"

ShaderCollection shader_collection_create() {
  return (ShaderCollection) {
      shader_create(texture_batch_vertex_shader_source, texture_batch_fragment_shader_source, "texture_batch_shader"),
      shader_create(texture_batch_vertex_shader_source,
                    texture_batch_text_fragment_shader_source,
                    "texture_batch_text_shader")
  };
}

void shader_collection_free(ShaderCollection s) {
  delete_shader(s.texture_batch_shader);
}

Shader shader_create(const char *v, const char *f, const char *name) {
  char vert_logs[1000];
  char frag_logs[1000];
  Shader s = create_shader(v, f, vert_logs, frag_logs, 1000, 1000);
  if (!s) {
    if (name != null) {
      log_error("Shader name: %s", name);
    }
    log_abort("vert logs: %s\n\nfrag logs: %s\n", vert_logs, frag_logs);
  }
  return s;
}
