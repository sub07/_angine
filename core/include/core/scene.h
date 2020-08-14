#pragma once

#include <maths/vec.h>
#include "key.h"

typedef struct {
  float dt;
  float fps;
  float frame_index;
} frame_info_t;

typedef struct {
  void (*close_program)(void);
  float (*window_height)(void);
  float (*window_width)(void);
} capacities_t;

typedef enum {
  KeyDown = 0, OnKeyDown, OnKeyUp,
  OnMouseMove, OnMouseDown, OnMouseUp, MouseDown, OnMouseScroll,
  OnWindowResize,
} event_type_t;

typedef struct {
  key_t key;
  modifiers_t mods;
} key_event_t;

typedef struct {
  mouse_button_t button;
  modifiers_t mods;
} mouse_button_event_t;

typedef struct {
  vec pos;
} mouse_motion_event_t;

typedef struct {
  float new_width;
  float new_height;
} window_resize_event_t;

typedef struct {
  event_type_t type;
  union data_t {
    key_event_t key;
    mouse_button_event_t mouse_button;
    mouse_motion_event_t mouse_motion;
    window_resize_event_t window_resize;
  } data;
} event_data_t;

typedef void (*loop_func)(frame_info_t *info, capacities_t *capacities, void *scene_data);
typedef void (*event_func)(event_data_t *data, capacities_t *capacities, void *scene_data);

typedef struct {
  loop_func loop_func;
  event_func event_func;
  void *data;
} scene_t;

scene_t *scene_create();
