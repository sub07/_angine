#include <core/angine.h>

typedef struct {
  Texture *tex;
  Transform tex_transform;
  TextureBatch *batch;
} data;

void scene_init(data *d, Capacities *c) {
  Image *i = image_create_from_file("assets/tex.png");
  d->tex = texture_create_img(i);
  image_free(i);
  d->batch = c->batch_texture_create();
  d->tex_transform = transform_default();
  batch_set_colors(d->batch, color_red, color_transparent, color_blue, color_gray);
  
}

void scene_loop(FrameInfo *info, Capacities *capacities, data *d) {
  batch_begin(d->batch);
  batch_texture(d->batch, d->tex, &d->tex_transform);
  batch_end(d->batch);
}

void scene_event(EventData *event, Capacities *capacities, data *d) {
  if (event->type == KeyDown) {
    Key k = event->data.key;
    if (k == Q) {
      d->tex_transform.rotate += 0.01f;
    } else if (k == D) {
      d->tex_transform.rotate -= 0.01f;
    } else if (k == Z) {
      d->tex_transform.scale.x += 0.01f;
      d->tex_transform.scale.y += 0.01f;
    } else if (k == S) {
      d->tex_transform.scale.x -= 0.01f;
      d->tex_transform.scale.y -= 0.01f;
    } else if (k == Up) {
      d->tex_transform.origin.y -= 0.1f;
    } else if (k == Down) {
      d->tex_transform.origin.y += 0.1f;
    } else if (k == Left) {
      d->tex_transform.origin.x -= 0.1f;
    } else if (k == Right) {
      d->tex_transform.origin.x += 0.1f;
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

void scene_end(data *scene_data) {
  texture_free(scene_data->tex);
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
