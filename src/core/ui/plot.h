#ifndef PLOT_H
#define PLOT_H

#include "core/types.h"
#include "hal/hal_input.h"

void ui_graph_render(float x_min, float x_max, float y_min, float y_max);
void ui_graph_zoom(float *min, float *max, float factor);
bool ui_graph_handle_control(input_event_t btn, mode_t *mode_out);

#endif // PLOT_H
