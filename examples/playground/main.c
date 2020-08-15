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
} data;

void scene_init(data *d, Capacities *c) {
  Image *i = image_create_from_file("assets/tex.png");
  d->tex = texture_create_img(i);
  image_free(i);
  d->batch = c->batch_texture_create();
  d->tex_transform = transform_default();
//  batch_set_colors(d->batch, color_red, color_transparent, color_blue, color_gray);
  d->c = 1;
  d->courier = font_create("assets/courier.ttf", 20);
}

typedef struct {
  Texture *t;
} hack;

void scene_loop(FrameInfo *info, Capacities *c, data *d) {
  char fps_string[50];
  sprintf(fps_string, "%d %d", (int) info->fps, d->c * d->c);
  c->window_title(fps_string);
  hack *h = (hack *) d->courier;
  batch_begin(d->batch);
  for (int x = 0; x < d->c; x++) {
    for (int y = 0; y < d->c; y++) {
      d->tex_transform.translate.x = (float) x * 16 + 50;
      d->tex_transform.translate.y = (float) y * 16 + 50;
      batch_texture(d->batch, d->tex, &d->tex_transform);
    }
  }
  Transform def = transform_default();
  def.translate.x = -500;
  batch_texture(d->batch, h->t, &def);
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
  
  if (event->type == OnMouseDown) {
    batch_enable_alpha_blending(d->batch);
  }
  
  if (event->type == OnMouseUp) {
    batch_disable_alpha_blending(d->batch);
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
