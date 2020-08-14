#pragma once

#include <stdbool.h>
#include <core/key.h>

typedef struct {
  void *event_manager;
  void (*key_callback)(void *, key_t, action_state_t, modifiers_t);
  void (*mouse_button_callback)(void *, mouse_button_t, action_state_t, modifiers_t);
  void (*mouse_move_callback)(void *, float, float);
  void (*mouse_scroll_callback)(void *, float, float);
  void (*window_resize_callback)(void *, float, float);
} event_callbacks_t;

typedef struct {
  void *window;
  event_callbacks_t callbacks;
} window_t;

typedef struct {
  int initial_width;
  int initial_height;
  const char *application_name;
  bool fullscreen;
  bool vsync;
  int monitor_index;
} window_config_t;

window_t *window_create(window_config_t *config, event_callbacks_t *callbacks);
void window_free(window_t *w);
void window_swap(window_t *w);
void window_set_title(window_t *w, const char *title);
void window_poll_event();
void window_enable_vsync();
void window_disable_vsync();
int window_get_width(window_t *w);
int window_get_height(window_t *w);
