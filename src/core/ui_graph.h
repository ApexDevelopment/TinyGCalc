#ifndef UI_GRAPH_H
#define UI_GRAPH_H

#include "core/types.h"

void ui_graph_render(const char* expr, float x_min, float x_max, float y_min, float y_max);
void ui_graph_zoom(float *min, float *max, float factor);

#endif // UI_GRAPH_H
