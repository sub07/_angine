#pragma once

#include <stdbool.h>
#include <core/key.h>
#include <graphics/graphics.h>

typedef struct {
  void *event_manager;
  void (*key_callback)(void *, Key, ActionState, Modifiers);
  void (*mouse_button_callback)(void *, MouseButton, ActionState, Modifiers);
  void (*mouse_move_callback)(void *, float, float);
  void (*mouse_scroll_callback)(void *, float, float);
  void (*window_resize_callback)(void *, float, float);
} event_callbacks_t;

typedef struct {
  void *window;
} Window;

typedef struct {
  int initial_width;
  int initial_height;
  const char *application_name;
  bool fullscreen;
  bool vsync;
  int monitor_index;
} window_config_t;

Window *window_create(window_config_t *config, event_callbacks_t *callbacks);
void window_free(Window *w);
void window_swap_buffer(Window *w);
void window_set_title(Window *w, const char *title);
void window_poll_event();
void window_enable_vsync();
void window_disable_vsync();
float window_get_width(Window *w);
float window_get_height(Window *w);
void window_close(Window *w);
bool window_should_close(Window *w);
float window_get_time();
ProcFuncLoader window_get_proc_loader();
