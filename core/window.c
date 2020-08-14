#include "window.h"
#include "glfw.h"
#include "utils.h"
#include <stdlib.h>
#include <utils/types.h>
#include <utils/log.h>

void glfw_key_callback(GLFWwindow *w, int key, int scancode, int action, int mods) {
  event_callbacks_t *e = glfwGetWindowUserPointer(w);
  
  e->key_callback(e->event_manager,
                  glfw_to_engine_key(key),
                  glfw_to_engine_action(action),
                  glfw_to_engine_modifiers(mods));
}

void glfw_mouse_button_callback(GLFWwindow *w, int button, int action, int mods) {
  event_callbacks_t *e = glfwGetWindowUserPointer(w);
  e->mouse_button_callback(e->event_manager,
                           glfw_to_engine_mouse_button(button),
                           glfw_to_engine_action(action),
                           glfw_to_engine_modifiers(mods));
}

void glfw_mouse_move_callback(GLFWwindow *w, double x, double y) {
  event_callbacks_t *e = glfwGetWindowUserPointer(w);
  e->mouse_move_callback(e->event_manager, (float) x, (float) y);
}

void glfw_mouse_scroll_callback(GLFWwindow *w, double x, double y) {
  event_callbacks_t *e = glfwGetWindowUserPointer(w);
  e->mouse_scroll_callback(e->event_manager, (float) x, (float) y);
}

void glfw_window_resize_callback(GLFWwindow *w, int width, int height) {
  event_callbacks_t *e = glfwGetWindowUserPointer(w);
  e->window_resize_callback(e->event_manager, (float) width, (float) height);
}

GLFWmonitor *get_monitor_from_index(int index) {
  int count;
  GLFWmonitor **monitors = glfwGetMonitors(&count);
  if (index < 0 || index >= count) return glfwGetPrimaryMonitor();
  return monitors[index];
}

void glfw_error_callback(int error_code, const char *desc) {
  log_abort("glfw error occurred: %s", desc);
}

window_t *window_create(window_config_t *config, event_callbacks_t *callbacks) {
  glfwInit();
  glfwSetErrorCallback(glfw_error_callback);
  window_t *w = malloc(sizeof(window_t));
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  
  if (config->fullscreen) {
    GLFWmonitor *monitor = get_monitor_from_index(config->monitor_index);
    if (config->initial_width == 0 && config->initial_height == 0) {
      int width, height;
      glfwGetMonitorWorkarea(monitor, null, null, &width, &height);
      w->window = glfwCreateWindow(width, height, config->application_name, monitor, null);
    } else {
      w->window =
          glfwCreateWindow(config->initial_width, config->initial_height, config->application_name, monitor, null);
    }
  } else {
    w->window = glfwCreateWindow(config->initial_width, config->initial_height, config->application_name, null, null);
  }
  
  glfwMakeContextCurrent(w->window);
  glfwSwapInterval(config->vsync ? 1 : 0);
  
  glfwSetWindowUserPointer(w->window, callbacks);
  
  glfwSetKeyCallback(w->window, glfw_key_callback);
  glfwSetMouseButtonCallback(w->window, glfw_mouse_button_callback);
  glfwSetCursorPosCallback(w->window, glfw_mouse_move_callback);
  glfwSetScrollCallback(w->window, glfw_mouse_scroll_callback);
  glfwSetWindowSizeCallback(w->window, glfw_window_resize_callback);
  // TODO other glfw events
  return w;
}

void window_free(window_t *w) {
  glfwDestroyWindow(w->window);
  glfwTerminate();
}

void window_swap_buffer(window_t *w) {
  glfwSwapBuffers(w->window);
}

void window_set_title(window_t *w, const char *title) {
  glfwSetWindowTitle(w->window, title);
}

void window_poll_event() {
  glfwPollEvents();
}

void window_enable_vsync() {
  glfwSwapInterval(1);
}

void window_disable_vsync() {
  glfwSwapInterval(0);
}

float window_get_width(window_t *w) {
  int width;
  glfwGetWindowSize(w->window, &width, null);
  return (float) width;
}

float window_get_height(window_t *w) {
  int height;
  glfwGetWindowSize(w->window, null, &height);
  return (float) height;
}

void window_close(window_t *w) {
  glfwSetWindowShouldClose(w->window, GLFW_TRUE);
}

float window_get_time() {
  return (float) glfwGetTime();
}

bool window_should_close(window_t *w) {
  return glfwWindowShouldClose(w->window);
}
