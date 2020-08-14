#include <core/angine.h>
#include <stdbool.h>
#include <maths/matrix.h>
#include "core/scene.h"
#include "window.h"
#include "batch.h"
#include <stdlib.h>
#include <core/key.h>
#include <utils/types.h>
#include <assert.h>
#include <string.h>

typedef struct { int a; } shader_collection_t;
typedef struct {
  bool keys_state[NbKey];
  bool mouse_buttons_state[NbMouseButton];
  vec mouse_pos;
  vec mouse_scroll;
  modifiers_t mods;
} event_state_t;

typedef struct {
  window_t *window;
  scene_t scene;
  frame_info_t frame_info;
  bool program_should_close;
  shader_collection_t shaders;
  event_state_t event_state;
  batch_t *batches;
  transform_t global_transformation;
  capacities_t capacities;
} angine_t;

angine_t *instance = null;
bool any_instance = false;

void key_callback(void *p, key_t key, action_state_t action, modifiers_t mods) {
  angine_t *a = p;
  a->event_state.mods = mods;
  if (action == Pressed) {
    a->event_state.keys_state[key] = true;
  } else if (action == Released) {
    a->event_state.keys_state[key] = false;
  } else {
    // Repeat
  }
}

void mouse_button_callback(void *p, mouse_button_t button, action_state_t action, modifiers_t mods) {
  angine_t *a = p;
  a->event_state.mods = mods;
  if (button == LeftButton) {
    if (action == Pressed) a->event_state.mouse_buttons_state[LeftButton] = true;
    else a->event_state.mouse_buttons_state[LeftButton] = false;
  } else if (button == RightButton) {
    if (action == Pressed) a->event_state.mouse_buttons_state[RightButton] = true;
    else a->event_state.mouse_buttons_state[RightButton] = false;
  } else if (button == MiddleButton) {
    if (action == Pressed) a->event_state.mouse_buttons_state[MiddleButton] = true;
    else a->event_state.mouse_buttons_state[MiddleButton] = false;
  } else {
    // Not supported
  }
}

void mouse_move_callback(void *p, float x, float y) {
  angine_t *a = p;
  a->event_state.mouse_pos.x = x;
  a->event_state.mouse_pos.y = y;
}

void mouse_scroll_callback(void *p, float x, float y) {
  angine_t *a = p;
  a->event_state.mouse_scroll.x = x;
  a->event_state.mouse_scroll.y = y;
}

void window_resize_callback(void *p, float w, float h) {
  angine_t *a = p;
  event_data_t e;
  e.type = OnWindowResize;
  e.data.window_resize.new_width = w;
  e.data.window_resize.new_height = h;
  a->scene.event_func(&e, &a->capacities, a->scene.data);
}

void event_state_init(angine_t *a) {
  memset(a->event_state.keys_state, 0, NbKey);
  memset(a->event_state.mouse_buttons_state, 0, NbMouseButton);
  a->event_state.mouse_pos.x = 0;
  a->event_state.mouse_pos.y = 0;
  a->event_state.mouse_scroll.x = 0;
  a->event_state.mouse_scroll.y = 0;
  a->event_state.mods.alt = false;
  a->event_state.mods.caps_lock = false;
  a->event_state.mods.num_lock = false;
  a->event_state.mods.ctrl = false;
  a->event_state.mods.super = false;
  a->event_state.mods.shift = false;
}

angine_t *angine_create(angine_config_t *config, event_callbacks_t *callbacks) {
  assert(!any_instance);
  angine_t *a = malloc(sizeof(angine_t));
  callbacks->event_manager = a;
  callbacks->window_resize_callback = window_resize_callback;
  callbacks->mouse_scroll_callback = mouse_scroll_callback;
  callbacks->mouse_move_callback = mouse_move_callback;
  callbacks->mouse_button_callback = mouse_button_callback;
  callbacks->key_callback = key_callback;
  a->window = window_create((window_config_t *) config, callbacks);
  a->program_should_close = false;
  a->scene = config->initial_scene;
  event_state_init(a);
  any_instance = true;
  instance = a;
  return a;
}

void angine_free(angine_t *a) {
  any_instance = false;
  instance = null;
  window_free(a->window);
  free(a);
}

void cap_close_program() {
  instance->program_should_close = true;
}

float cap_window_width() {
  return window_get_width(instance->window);
}

float cap_window_height() {
  return window_get_height(instance->window);
}

void dispatch_events(angine_t *a, event_state_t previous) {
  a->program_should_close = window_should_close(a->window);
  scene_t s = a->scene;
  modifiers_t mods = a->event_state.mods;
  event_data_t e;
  for (int key = 0; key < NbKey; key++) {
    if (a->event_state.keys_state[key]) {
      if (!previous.keys_state[key]) {
        e.type = OnKeyDown;
        e.data.key.key = key;
        e.data.key.mods = mods;
        s.event_func(&e, &a->capacities, s.data);
      }
      e.type = KeyDown;
      e.data.key.key = key;
      e.data.key.mods = mods;
      s.event_func(&e, &a->capacities, s.data);
    }
    
    if (previous.keys_state[key]) {
      if (!a->event_state.keys_state[key]) {
        e.type = OnKeyUp;
        e.data.key.key = key;
        e.data.key.mods = mods;
        s.event_func(&e, &a->capacities, s.data);
      }
    }
  }
  
  for (int button = 0; button < NbMouseButton; button++) {
    if (a->event_state.mouse_buttons_state[button]) {
      if (!previous.mouse_buttons_state[button]) {
        e.type = OnMouseDown;
        e.data.mouse_button.button = button;
        e.data.mouse_button.mods = mods;
        s.event_func(&e, &a->capacities, s.data);
      }
      e.type = MouseDown;
      e.data.mouse_button.button = button;
      e.data.mouse_button.mods = mods;
      s.event_func(&e, &a->capacities, s.data);
    }
    
    if (previous.mouse_buttons_state[button]) {
      if (!a->event_state.mouse_buttons_state[button]) {
        e.type = OnMouseUp;
        e.data.mouse_button.button = button;
        e.data.mouse_button.mods = mods;
        s.event_func(&e, &a->capacities, s.data);
      }
    }
    
    if (!vec_eq(a->event_state.mouse_pos, previous.mouse_pos)) {
      e.type = OnMouseMove;
      e.data.mouse_motion.pos = a->event_state.mouse_pos;
      s.event_func(&e, &a->capacities, s.data);
    }
    
    if (!vec_eq(a->event_state.mouse_scroll, previous.mouse_scroll)) {
      e.type = OnMouseScroll;
      e.data.mouse_motion.pos = a->event_state.mouse_scroll;
      s.event_func(&e, &a->capacities, s.data);
      a->event_state.mouse_scroll.x = 0;
      a->event_state.mouse_scroll.y = 0;
    }
  }
  
}

void angine_run(angine_config_t *config) {
  event_callbacks_t callbacks;
  angine_t *a = angine_create(config, &callbacks);
  a->capacities.close_program = cap_close_program;
  a->capacities.window_height = cap_window_height;
  a->capacities.window_width = cap_window_width;
  
  float last = window_get_time();
  
  float dt_acc = 0;
  const int acc_reset_size = 20;
  int acc_size = 0;
  
  event_state_t previous = a->event_state;
  while (!a->program_should_close) {
    // dt
    float time = window_get_time();
    float dt = time - last;
    a->frame_info.dt = dt;
    last = time;
    
    // fps
    if (acc_size >= acc_reset_size) {
      a->frame_info.fps = 1 / (dt_acc / (float) acc_reset_size);
      acc_size = 0;
      dt_acc = 0;
    }
    dt_acc += dt;
    acc_size++;
    
    window_poll_event();
    
    // scene
    dispatch_events(a, previous);
    previous = a->event_state;
    
    a->scene.loop_func(&a->frame_info, &a->capacities, a->scene.data);
    a->frame_info.frame_index++;
    window_swap_buffer(a->window);
  }
  
  angine_free(a);
}

angine_config_t default_config() {
  angine_config_t c;
  c.needed_batch = 0;
  c.fullscreen = false;
  c.batches_configuration_function = null;
  c.monitor_index = 0;
  c.vsync = true;
  c.application_name = "Angine window";
  c.initial_width = 800;
  c.initial_height = 600;
  return c;
}
