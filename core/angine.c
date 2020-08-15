#include <core/angine.h>
#include <stdbool.h>
#include "window.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "texture_batch.h"

typedef struct {
  bool keys_state[NbKey];
  bool mouse_buttons_state[NbMouseButton];
  Vec mouse_pos;
  Vec mouse_scroll;
  Modifiers mods;
} EventState;

typedef struct {
  Window *window;
  Scene scene;
  FrameInfo frame_info;
  bool program_should_close;
  ShaderCollection shaders;
  EventState event_state;
  Transform global_transformation;
  Capacities capacities;
} Angine;

Angine *instance = null;

void key_callback(void *p, Key key, ActionState action, Modifiers mods) {
  Angine *a = p;
  a->event_state.mods = mods;
  if (action == Pressed) {
    a->event_state.keys_state[key] = true;
  } else if (action == Released) {
    a->event_state.keys_state[key] = false;
  } else {
    // Repeat
  }
}

void mouse_button_callback(void *p, MouseButton button, ActionState action, Modifiers mods) {
  Angine *a = p;
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
  Angine *a = p;
  a->event_state.mouse_pos.x = x;
  a->event_state.mouse_pos.y = y;
}

void mouse_scroll_callback(void *p, float x, float y) {
  Angine *a = p;
  a->event_state.mouse_scroll.x = x;
  a->event_state.mouse_scroll.y = y;
}

void window_resize_callback(void *p, float w, float h) {
  Angine *a = p;
  EventData e;
  e.type = OnWindowResize;
  e.data.new_window_size.x = w;
  e.data.new_window_size.y = h;
  a->scene.event_func(&e, &a->frame_info, &a->capacities, a->scene.data);
  set_viewport((int) w, (int) h);
  use_shader(a->shaders.texture_batch_shader);
  send_vec2_shader(a->shaders.texture_batch_shader, "viewportSize", w, h);
}

void event_state_init(Angine *a) {
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

void init_shaders(Angine *a) {
  a->shaders = shader_collection_create();
  use_shader(a->shaders.texture_batch_shader);
  send_vec2_shader(a->shaders.texture_batch_shader,
                   "viewportSize",
                   window_get_width(a->window),
                   window_get_height(a->window));
}

Angine *angine_create(AngineConfig *config, event_callbacks_t *callbacks) {
  assert(instance == null);
  Angine *a = malloc(sizeof(Angine));
  callbacks->event_manager = a;
  callbacks->window_resize_callback = window_resize_callback;
  callbacks->mouse_scroll_callback = mouse_scroll_callback;
  callbacks->mouse_move_callback = mouse_move_callback;
  callbacks->mouse_button_callback = mouse_button_callback;
  callbacks->key_callback = key_callback;
  a->window = window_create((window_config_t *) config, callbacks);
  a->program_should_close = false;
  a->scene = config->initial_scene;
  a->frame_info.frame_index = 0;
  a->frame_info.fps = 0;
  a->frame_info.dt = 0;
  event_state_init(a);
  instance = a;
  load_gl_from_loader(window_get_proc_loader(), false);
  set_clear_color(0.5f, 0.5f, 0.5f, 1.f);
  init_shaders(a);
  return a;
}

void angine_free(Angine *a) {
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

TextureBatch *cap_batch_create() {
  return batch_create(instance->shaders.texture_batch_shader);
}

void cap_window_title(const char *title) {
  window_set_title(instance->window, title);
}

void dispatch_events(Angine *a, EventState previous) {
  a->program_should_close = window_should_close(a->window);
  Scene s = a->scene;
  EventData e;
  e.mods = a->event_state.mods;
  for (int key = 0; key < NbKey; key++) {
    if (a->event_state.keys_state[key]) {
      if (!previous.keys_state[key]) {
        e.type = OnKeyDown;
        e.data.key = key;
        s.event_func(&e, &a->frame_info, &a->capacities, s.data);
      }
      e.type = KeyDown;
      e.data.key = key;
      s.event_func(&e, &a->frame_info, &a->capacities, s.data);
    }
    
    if (previous.keys_state[key]) {
      if (!a->event_state.keys_state[key]) {
        e.type = OnKeyUp;
        e.data.key = key;
        s.event_func(&e, &a->frame_info, &a->capacities, s.data);
      }
    }
  }
  
  for (int button = 0; button < NbMouseButton; button++) {
    if (a->event_state.mouse_buttons_state[button]) {
      if (!previous.mouse_buttons_state[button]) {
        e.type = OnMouseDown;
        e.data.button = button;
        s.event_func(&e, &a->frame_info, &a->capacities, s.data);
      }
      e.type = MouseDown;
      e.data.button = button;
      s.event_func(&e, &a->frame_info, &a->capacities, s.data);
    }
    
    if (previous.mouse_buttons_state[button]) {
      if (!a->event_state.mouse_buttons_state[button]) {
        e.type = OnMouseUp;
        e.data.button = button;
        s.event_func(&e, &a->frame_info, &a->capacities, s.data);
      }
    }
    
    if (!vec_eq(a->event_state.mouse_pos, previous.mouse_pos)) {
      e.type = OnMouseMove;
      e.data.mouse_position = a->event_state.mouse_pos;
      s.event_func(&e, &a->frame_info, &a->capacities, s.data);
    }
    
    if (!vec_eq(a->event_state.mouse_scroll, previous.mouse_scroll)) {
      e.type = OnMouseScroll;
      e.data.mouse_scroll = a->event_state.mouse_scroll;
      s.event_func(&e, &a->frame_info, &a->capacities, s.data);
      a->event_state.mouse_scroll.x = 0;
      a->event_state.mouse_scroll.y = 0;
    }
  }
}

void angine_run(AngineConfig *config) {
  event_callbacks_t callbacks;
  Angine *a = angine_create(config, &callbacks);
  a->capacities.close_program = cap_close_program;
  a->capacities.window_height = cap_window_height;
  a->capacities.window_width = cap_window_width;
  a->capacities.batch_texture_create = cap_batch_create;
  a->capacities.window_title = cap_window_title;
  
  float last = window_get_time();
  
  float dt_acc = 0;
  const int acc_reset_size = 20;
  int acc_size = 0;
  
  a->scene.init_func(a->scene.data, &a->capacities);
  
  EventState previous = a->event_state;
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
    clear_screen();
    a->scene.loop_func(&a->frame_info, &a->capacities, a->scene.data);
    a->frame_info.frame_index++;
    window_swap_buffer(a->window);
  }
  a->scene.end_func(a->scene.data);
  
  angine_free(a);
}

AngineConfig default_config() {
  AngineConfig c;
  c.fullscreen = false;
  c.monitor_index = 0;
  c.vsync = true;
  c.application_name = "Angine window";
  c.initial_width = 800;
  c.initial_height = 600;
  return c;
}
