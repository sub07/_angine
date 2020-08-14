#include <core/angine.h>
#include <utils/log.h>

typedef struct {
  int counter;
} data;

void scene_loop(frame_info_t *info, capacities_t *capacities, data *scene_data) {
  log_debug("%d", scene_data->counter);
  scene_data->counter++;
}

void scene_event(event_data_t *event, capacities_t *capacities, data *scene_data) {
  if (event->type == OnKeyDown) {
    if (event->data.key.key == R) {
      scene_data->counter = 0;
    }
  }
}

int main() {
  angine_config_t c;
  c.initial_width = 800;
  c.initial_height = 600;
  c.application_name = "window-alt";
  c.vsync = true;
  c.fullscreen = false;
  c.monitor_index = 0;
  c.initial_scene.loop_func = (loop_func) scene_loop;
  c.initial_scene.event_func = (event_func) scene_event;
  
  data d = {0};
  c.initial_scene.data = &d;
  
  angine_run(&c);
  return 0;
}