#pragma once

#include <stdbool.h>
#include "scene.h"

typedef struct { int a; } Transform;
typedef struct {
  int initial_width;
  int initial_height;
  const char *application_name;
  bool fullscreen;
  bool vsync;
  int monitor_index;
  Scene initial_scene;
  int needed_batch;
} AngineConfig;

AngineConfig default_config();
void angine_run(AngineConfig *config);
