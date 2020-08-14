#include <core/angine.h>
#include <stdbool.h>
#include <maths/matrix.h>
#include "scene.h"
#include "window.h"
#include "batch.h"
#include <stdlib.h>
#include <core/key.h>

typedef struct {int a;} shader_collection_t;
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
} angine_t;

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

}

angine_t *angine_create(angine_config_t *config) {
  angine_t *a = malloc(sizeof(angine_t));
  event_callbacks_t callbacks;
  callbacks.event_manager = a;
  callbacks.window_resize_callback = window_resize_callback;
  callbacks.mouse_scroll_callback = mouse_scroll_callback;
  callbacks.mouse_move_callback = mouse_move_callback;
  callbacks.mouse_button_callback = mouse_button_callback;
  callbacks.key_callback = key_callback;
  a->window = window_create((window_config_t *) config, &callbacks);
  return a;
}

void angine_free(angine_t *a) {
  window_free(a->window);
  free(a);
}

void angine_run(angine_config_t *config) {
  angine_t *a = angine_create(config);
  
  angine_free(a);
}
