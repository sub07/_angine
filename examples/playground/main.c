#include <core/angine.h>
#include <stdio.h>
#include <maths/utils.h>
#include <core/font.h>

typedef struct {
  Texture *tex;
  Transform tex_transform;
  TextureBatch *batch;
  int c;
  Font *courier;
  float x;
} data;

void scene_init(data *d, Capacities *c) {
  Image *i = image_create_from_file("assets/tex.png");
  d->tex = texture_create_from_img(i);
  image_free(i);
  d->batch = c->batch_texture_create();
  batch_enable_alpha_blending(d->batch);
  d->tex_transform = transform_default();
  d->c = 1;
  d->courier = font_create("assets/courier.ttf", 25);
  batch_set_color(d->batch, color_black);
}

void scene_loop(FrameInfo *info, Capacities *c, data *d) {
  char fps_string[50];
  sprintf(fps_string, "%d", (int) info->fps);
  batch_begin(d->batch);
  batch_string(d->batch, d->courier, fps_string, d->tex_transform);
  batch_end(d->batch);
}

void scene_event(EventData *event, FrameInfo *info, Capacities *capacities, data *d) {
  if (event->type == KeyDown) {
    Key k = event->data.key;
    if (k == Q) {
      d->tex_transform.rotate += (pi / 2) * info->dt;
    } else if (k == D) {
      d->tex_transform.rotate -= (pi / 2) * info->dt;
    } else if (k == Z) {
      d->tex_transform.scale.x += 0.01f;
      d->tex_transform.scale.y += 0.01f;
    } else if (k == S) {
      d->tex_transform.scale.x -= 0.01f;
      d->tex_transform.scale.y -= 0.01f;
    } else if (k == Up) {
      d->c++;
      d->tex_transform.origin.y -= 0.1f;
    } else if (k == Down) {
      d->c--;
      d->tex_transform.origin.y += 0.1f;
    } else if (k == Left) {
      d->tex_transform.origin.x -= 0.1f;
    } else if (k == Right) {
      d->tex_transform.origin.x += 0.1f;
      d->x += 5;
    }
  }
  
  if (event->type == OnKeyDown) {
    if (event->mods.ctrl) {
      if (event->data.key == R) {
        d->c = 1;
      }
    }
  }
  
  if (event->type == OnMouseMove) {
    d->tex_transform.translate = event->data.mouse_position;
  }
}

void scene_end(data *d) {
  font_free(d->courier);
  texture_free(d->tex);
}

int main() {
  AngineConfig c = default_config();
  c.initial_scene.loop_func = (LoopFunc) scene_loop;
  c.initial_scene.event_func = (EventFunc) scene_event;
  c.initial_scene.init_func = (InitFunc) scene_init;
  c.initial_scene.end_func = (EndFunc) scene_end;
  data d;
  c.initial_scene.data = &d;
  
  angine_run(&c);
  return 0;
}
