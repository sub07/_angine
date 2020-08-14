#include <core/angine.h>

int main() {
  angine_config_t c;
  c.initial_width = 800;
  c.initial_height = 600;
  c.application_name = "window-alt";
  c.vsync = true;
  c.fullscreen = false;
  c.monitor_index = 0;
  
  angine_run(&c);
  return 0;
}