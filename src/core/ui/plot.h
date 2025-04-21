#ifndef PLOT_H
#define PLOT_H

#include "core/types.h"
#include "hal/hal_input.h"

void ui_plot_zoom(float *min, float *max, float factor);
void ui_plot_render();
bool ui_plot_handle_control(input_event_t btn, ui_mode_t *mode_out);

#endif // PLOT_H
