#pragma once

#include <maths/vec.h>

typedef struct Font Font;

Font *font_create(const char *path, int font_size);
Vec font_string_size(Font *font, const char *string);
void font_free(Font *font);
