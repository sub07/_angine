#include <stdlib.h>
#include <core/texture.h>
#include <maths/vec.h>
#include <core/font.h>
#include <core/scene.h>
#include <core/angine.h>

typedef enum {
  Head,
  Body,
  Tail,
  NbPart
} SnakePart;

typedef struct {
  Texture *snake_tex;
  Rect sub_textures[NbPart];
  Font *courier;
  TextureBatch *b;
  Vec grid_size;
  Vec tile_size;
} SnakeData;

void snake_init(SnakeData *d, Capacities c) {
  d->b = c.batch_texture_create();
  d->snake_tex = texture_create_from_file("assets/snake.png");
  d->sub_textures[Head] = (Rect) {0, 0, 32, 32};
  d->sub_textures[Body] = (Rect) {32, 32, 32, 32};
  d->sub_textures[Tail] = (Rect) {64, 64, 32, 32};
  d->courier = font_create("assets/courier.ttf", 15);
  d->grid_size = (Vec) {15, 15};
  d->tile_size = (Vec) {32, 32};
}

void snake_loop(FrameInfo *info, Capacities *c, SnakeData *d) {

}

void snake_event(EventData *data, FrameInfo *info, Capacities *capacities, SnakeData *d) {

}

void snake_free(SnakeData *d) {
  texture_free(d->snake_tex);
  font_free(d->courier);
  batch_free(d->b);
}

int main() {
  AngineConfig config = default_config();
  config.initial_scene.init_func = (InitFunc) snake_init;
  config.initial_scene.loop_func = (LoopFunc) snake_loop;
  config.initial_scene.event_func = (EventFunc) snake_event;
  config.initial_scene.end_func = (EndFunc) snake_free;
  SnakeData d;
  config.initial_scene.data = &d;
  
  config.application_name = "Snake";
  
  angine_run(&config);
  return EXIT_SUCCESS;
}
