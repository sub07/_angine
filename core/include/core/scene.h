#pragma once

#include <maths/vec.h>
#include <utils/types.h>
#include "key.h"
#include "texture_batch.h"

typedef struct {
  float dt;
  float fps;
  u64 frame_index;
} FrameInfo;

typedef struct {
  void (*close_program)(void);
  float (*window_height)(void);
  float (*window_width)(void);
  TextureBatch *(*batch_texture_create)(void);
} Capacities;

typedef enum {
  KeyDown = 0, OnKeyDown, OnKeyUp,
  OnMouseMove, OnMouseDown, OnMouseUp, MouseDown, OnMouseScroll,
  OnWindowResize,
} EventType;

typedef struct {
  EventType type;
  union data_t {
    float new_window_width;
    float new_window_height;
    Vec mouse_position;
    Vec mouse_scroll;
    Modifiers mods;
    MouseButton button;
    Key key;
  } data;
} EventData;

typedef void (*LoopFunc)(FrameInfo *info, Capacities *capacities, void *scene_data);
typedef void (*EventFunc)(EventData *data, Capacities *capacities, void *scene_data);
typedef void (*InitFunc)(void *scene_data, Capacities *capacities);
typedef void (*EndFunc)(void *scene_data);

typedef struct {
  InitFunc init_func;
  LoopFunc loop_func;
  EndFunc end_func;
  EventFunc event_func;
  void *data;
} Scene;

Scene *scene_create();
