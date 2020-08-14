#include <core/angine.h>

void scene_loop(frame_info_t *info, capacities_t *capacities, void *scene_data) {

}

void scene_event(event_data_t *event, capacities_t *capacities, void *scene_data) {

}

int main() {
  angine_config_t c;
  c.initial_width = 800;
  c.initial_height = 600;
  c.application_name = "window-alt";
  c.vsync = true;
  c.fullscreen = false;
  c.monitor_index = 0;
  c.initial_scene.loop_func = scene_loop;
  c.initial_scene.event_func = scene_event;
  
  angine_run(&c);
  return 0;
}