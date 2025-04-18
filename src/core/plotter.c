#include "plotter.h"
#include "hal/hal_display.h"
#include "tinyexpr.h"
#include <stdio.h>
#include <math.h>

void plot_function(const char* expr, float x_min, float x_max, float y_offset) {
    int width = hal_display_get_width();
    int height = hal_display_get_height();

    double x = 0.0;
    double y = y_offset;

    te_variable vars[] = {
        {"x", &x},
        {"y", &y}
    };

    int err;
    te_expr* compiled = te_compile(expr, vars, 2, &err);
    if (!compiled) return;

    float y_min = -1.5f, y_max = 1.5f;
    float dx = (x_max - x_min) / width;

    int prev_px = 0, prev_py = 0;
    for (int px = 0; px < width; px++) {
        x = x_min + px * dx;
        double y = te_eval(compiled);

        int py = height - (int)((y - y_min) / (y_max - y_min) * height);

        if (px > 0) {
            hal_display_draw_line(prev_px, prev_py, px, py, 0xFFFF); // white line
        }

        prev_px = px;
        prev_py = py;
    }

    te_free(compiled);
}
