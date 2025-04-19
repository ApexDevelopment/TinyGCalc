#ifndef PLOTTER_H
#define PLOTTER_H

#include <stdint.h>

void plot_function(const char* expr, float x_min, float x_max, float y_min, float y_max, uint16_t color);

#endif // PLOTTER_H
