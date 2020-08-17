#pragma once

#include <maths/vec.h>
#include <utils/types.h>
#include "key.h"
#include "texture_batch.h"
#include "polygon_batch.h"

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
  PolygonBatch *(*batch_polygon_create)(void);
  void (*window_title)(const char *);
} Capacities;

typedef enum {
  KeyDown = 0, OnKeyDown, OnKeyUp,
  OnMouseMove, OnMouseDown, OnMouseUp, MouseDown, OnMouseScroll,
  OnWindowResize,
} EventType;

typedef struct {
  EventType type;
  Modifiers mods;
  union data_t {
    Vec new_window_size;
    Vec mouse_position;
    Vec mouse_scroll;
    MouseButton button;
    Key key;
  } data;
} EventData;

typedef void (*LoopFunc)(FrameInfo *info, Capacities *capacities, void *scene_data);
typedef void (*EventFunc)(EventData *data, FrameInfo *info, Capacities *capacities, void *scene_data);
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
