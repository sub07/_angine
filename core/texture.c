#include <core/texture.h>
#include <stdlib.h>
#include <graphics/graphics.h>

typedef struct {
  float width;
  float height;
  Handle handle;
} TextureImpl;

Texture *texture_create(void *data, int width, int height, int nb_channel) {
  TextureImpl *t = malloc(sizeof(TextureImpl));
  t->width = (float) width;
  t->height = (float) height;
  t->handle = create_texture(Nearest, width, height, nb_channel, data);
  return (Texture *) t;
}

Texture *texture_create_from_img(Image *image) {
  return texture_create(image->pixels, image->width, image->height, image->nb_channel);
}

Texture *texture_create_from_file(const char *path) {
  Image *i = image_create_from_file(path);
  Texture *t = texture_create_from_img(i);
  image_free(i);
  return t;
}

void texture_bind(Texture *texture) {
  texture_bind_texture_unit(texture, 0);
}

void texture_bind_texture_unit(Texture *texture, unsigned int texture_unit) {
  TextureImpl *t = (TextureImpl *) texture;
  bind_texture_unit(t->handle, texture_unit);
}

Handle texture_handle(Texture *texture) {
  TextureImpl *t = (TextureImpl *) texture;
  return t->handle;
}

void texture_free(Texture *texture) {
  TextureImpl *t = (TextureImpl *) texture;
  delete_texture(t->handle);
  free(texture);
}
