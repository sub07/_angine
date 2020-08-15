#include <core/angine.h>
#include <utils/log.h>

typedef struct {
  int counter;
} data;

void scene_loop(FrameInfo *info, Capacities *capacities, data *scene_data) {
  log_debug("%d", scene_data->counter);
  scene_data->counter++;
}

void scene_event(EventData *event, Capacities *capacities, data *scene_data) {
  if (event->type == OnKeyDown) {
    if (event->data.key == R) {
      scene_data->counter = 0;
    }
    if (event->data.key == S) {
      capacities->close_program();
    }
  }
}

int main() {
  AngineConfig c = default_config();
  c.initial_scene.loop_func = (LoopFunc) scene_loop;
  c.initial_scene.event_func = (EventFunc) scene_event;
  data d;
  c.initial_scene.data = &d;
  
  angine_run(&c);
  return 0;
}
