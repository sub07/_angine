#include <core/image.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include <utils/stb_image.h>
#include <utils/log.h>

Image *image_create(int width, int height, image_format_ format) {
  Image *i = malloc(sizeof(Image));
  i->width = width;
  i->height = height;
  i->nb_channel = format;
  i->pixels = malloc(width * height * format);
  return i;
}

Image *image_create_from_data(void *data, int width, int height, image_format_ format) {
  Image *i = image_create(width, height, format);
  memcpy(i->pixels, data, width * height * format);
}

Image *image_create_from_file(const char *path) {
  Image *i = malloc(sizeof(Image));
  i->pixels = stbi_load(path, &i->width, &i->height, &i->nb_channel, 0);
  if (i->pixels == null) { log_abort("Failed to load image at %s", path); }
  return i;
}

void image_free(Image *image) {
  free(image->pixels);
  free(image);
}

void image_clear(Image *image, Color clear_color) {
  u8 *p = image->pixels;
  for (int i = 0; i < image->width * image->height * image->nb_channel; i += image->nb_channel) {
    for (int c = 0; c < image->nb_channel; c++) {
      p[i + c] = color_get_int_component(clear_color, c);
    }
  }
}

void image_draw_image(Image *dest, Image *src, int start_x, int start_y) {
  assert(dest->nb_channel == src->nb_channel);
  int sw = src->width;
  int sh = src->height;
  int dw = dest->width;
  int dh = dest->height;
  
  for (int x = start_x; x < start_x + sw; x++) {
    for (int y = start_y; y < start_y + sh; y++) {
      if (x < 0 || x >= dw || y < 0 || y >= dh) continue;
      int dest_i = (y * dw + x) * dest->nb_channel;
      int src_i = ((y - start_y) * sw + (x - start_x)) * src->nb_channel;
      for (int c = 0; c < dest->nb_channel; c++) {
        dest->pixels[dest_i + c] = src->pixels[src_i + c];
      }
    }
  }
}
