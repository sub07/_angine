#pragma once

typedef struct Font Font;

Font *font_create(const char *path, int font_size);
void font_free(Font *font);
