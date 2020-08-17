#include <core/angine.h>
#include <stdio.h>
#include <maths/utils.h>
#include <core/font.h>
#include <core/polygon_batch.h>

typedef struct {
  Texture *tex;
  Transform tex_transform;
  TextureBatch *batch;
  PolygonBatch *p_batch;
  int c;
  Font *courier;
  float x;
} data;

void scene_init(data *d, Capacities *c) {
  Image *i = image_create_from_file("assets/tex.png");
  d->tex = texture_create_from_img(i);
  image_free(i);
  d->batch = c->batch_texture_create();
  d->p_batch = c->batch_polygon_create();
  batch_enable_alpha_blending(d->batch);
  d->tex_transform = transform_default();
  d->c = 1;
  d->courier = font_create("assets/courier.ttf", 25);
  batch_set_color(d->batch, color_black);
  d->tex_transform.translate = (Vec) {80, 90};
}

void scene_loop(FrameInfo *info, Capacities *c, data *d) {
  char fps_string[50];
  sprintf(fps_string, "%d", (int) info->fps);
  p_batch_begin(d->p_batch);
  p_batch_draw_rect(d->p_batch, (Vec) {80, 60}, &d->tex_transform);
  Transform t = d->tex_transform;
  t.translate.x += 100;
  p_batch_draw_rect(d->p_batch, (Vec) {80, 60}, &t);
  p_batch_end(d->p_batch);
//  batch_begin(d->batch);
//  batch_string(d->batch, d->courier, fps_string, transform_default());
//  batch_end(d->batch);
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
//    d->tex_transform.translate = event->data.mouse_position;
  }
}

void scene_end(data *d) {
  font_free(d->courier);
  batch_free(d->batch);
  p_batch_free(d->p_batch);
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
