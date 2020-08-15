#pragma once

#include <maths/vec.h>
#include "key.h"

typedef struct {
  float dt;
  float fps;
  float frame_index;
} FrameInfo;

typedef struct {
  void (*close_program)(void);
  float (*window_height)(void);
  float (*window_width)(void);
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
    vec mouse_position;
    vec mouse_scroll;
    Modifiers mods;
    MouseButton button;
    Key key;
  } data;
} EventData;

typedef void (*LoopFunc)(FrameInfo *info, Capacities *capacities, void *scene_data);
typedef void (*EventFunc)(EventData *data, Capacities *capacities, void *scene_data);

typedef struct {
  LoopFunc loop_func;
  EventFunc event_func;
  void *data;
} Scene;

Scene *scene_create();
