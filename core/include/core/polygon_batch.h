#pragma once

#include <maths/vec.h>
#include "color.h"

typedef struct PolygonBatch PolygonBatch;

void p_batch_free(PolygonBatch *batch);
void p_batch_begin(PolygonBatch *batch);
void p_batch_end(PolygonBatch *batch);
void p_batch_stroke_color(PolygonBatch *batch, Color new_color);
void p_batch_fill_color(PolygonBatch *batch, Color new_color);
void p_batch_enable_alpha_blending(PolygonBatch *b);
void p_batch_disable_alpha_blending(PolygonBatch *b);

void p_batch_draw_polygon(PolygonBatch *batch, float *vertices, int nb_vertex, Transform *transform);
void p_batch_draw_polyline(PolygonBatch *batch, float *vertices, int nb_vertex, Transform *transform);
void p_batch_draw_rect(PolygonBatch *batch, Vec size, Transform *transform);
void p_batch_draw_ellipse(PolygonBatch *batch, Vec size, Transform *transform);
void p_batch_draw_line(PolygonBatch *batch, Vec v1, Vec v2, Transform *transform);

void p_batch_fill_polygon(PolygonBatch *batch, float *vertices, int nb_vertex, Transform *transform);
void p_batch_fill_polyline(PolygonBatch *batch, float *vertices, int nb_vertex, Transform *transform);
void p_batch_fill_rect(PolygonBatch *batch, Vec size, Transform *transform);
void p_batch_fill_ellipse(PolygonBatch *batch, Vec size, Transform *transform);
