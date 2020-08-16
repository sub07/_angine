#pragma once

#include <maths/vec.h>
#include "texture.h"
#include "font.h"

typedef struct TextureBatch TextureBatch;

void batch_free(TextureBatch *batch);
void batch_begin(TextureBatch *batch);
void batch_end(TextureBatch *batch);

void batch_set_colors(TextureBatch *batch, Color c1, Color c2, Color c3, Color c4);
void batch_set_color(TextureBatch *batch, Color new_color);
void batch_texture(TextureBatch *b, Texture *tex, Transform *transform, Rect *sub_texture);
void batch_string(TextureBatch *b, Font *font, const char *string, Transform transform);
void batch_enable_alpha_blending(TextureBatch *b);
void batch_disable_alpha_blending(TextureBatch *b);
