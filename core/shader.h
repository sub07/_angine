#pragma once

#include <graphics/graphics.h>
#include <utils/log.h>
#include "shader_sources.h"

typedef Handle Shader;

typedef struct {
  Shader texture_batch_shader;
  Shader texture_batch_text_shader;
  Shader polygon_batch_shader;
} ShaderCollection;

ShaderCollection shader_collection_create();
void shader_collection_free(ShaderCollection s);

// Give a name for logging purposes, null is ok
Shader shader_create(const char *v, const char *f, const char *name);
