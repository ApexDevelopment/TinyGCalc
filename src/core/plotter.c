#include "plotter.h"
#include "hal/hal_display.h"
#include "tinyexpr.h"
#include "core/graph_utils.h"
#include <math.h>
#include <stdbool.h>

void plot_function(const char *expr, float x_min, float x_max, float y_min, float y_max)
{
	int width  = hal_display_get_width();
	int height = hal_display_get_height();

	double x = 0.0;

	te_variable vars[] = {{"x", &x}};

	int		 err;
	te_expr *compiled = te_compile(expr, vars, 1, &err);
	if (!compiled)
	{
		return;
	}

	float dx = (x_max - x_min) / width;

	int	 prev_px = 0, prev_py = 0;
	bool has_prev = false;

	for (int px = 0; px < width; px++)
	{
		x			  = x_min + px * dx;
		double result = te_eval(compiled);

		int py = screen_y((float) result, y_min, y_max, height);

		if (has_prev)
		{
			hal_display_draw_line(prev_px, prev_py, px, py, 0xFFFF); // white line
		}

		prev_px	 = px;
		prev_py	 = py;
		has_prev = true;
	}

	te_free(compiled);
}
