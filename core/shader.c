#include "shader.h"

ShaderCollection shader_collection_create() {
  char vert_logs[1000];
  char frag_logs[1000];
  Shader s1 = create_shader(texture_batch_vertex_shader_source,
                            texture_batch_fragment_shader_source,
                            vert_logs,
                            frag_logs,
                            1000,
                            1000);
  if (!s1) {
    log_abort("vert logs: %s\n\nfrag logs: %s\n", vert_logs, frag_logs);
  }
  return (ShaderCollection) {s1};
}

void shader_collection_free(ShaderCollection s) {
  delete_shader(s.texture_batch_shader);
}
