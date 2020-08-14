#pragma once

#include <stdbool.h>
#include "scene.h"

typedef struct { int a; } transform_t;
typedef struct {
  int initial_width;
  int initial_height;
  const char *application_name;
  bool fullscreen;
  bool vsync;
  int monitor_index;
  scene_t initial_scene;
  int needed_batch;
  void (*batches_configuration_function)(void *, int);
} angine_config_t;

angine_config_t default_config();
void angine_run(angine_config_t *config);
