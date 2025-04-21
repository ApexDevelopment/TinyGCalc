#include "plotter.h"
#include "core/utils/graph.h"
#include "core/utils/trig.h"
#include "hal/hal_display.h"
#include "tinyexpr.h"
#include <math.h>
#include <stdbool.h>

static bool eval_safe(te_expr *expr, double *out)
{
	double result = te_eval(expr);
	if (isnan(result) || isinf(result))
	{
		return false;
	}
	*out = result;
	return true;
}

void plot_function(const char *expr, float x_min, float x_max, float y_min, float y_max, uint16_t color)
{
	int width  = hal_display_get_width();
	int height = hal_display_get_height();

	double		x	   = 0.0;
	te_variable vars[] = {
		{"x", &x},
		{"sin", sin_override, TE_FUNCTION1},
		{"cos", cos_override, TE_FUNCTION1},
		{"tan", tan_override, TE_FUNCTION1},
		{"asin", asin_override, TE_FUNCTION1},
		{"acos", acos_override, TE_FUNCTION1},
		{"atan", atan_override, TE_FUNCTION1},
		{"atan2", atan2_override, TE_FUNCTION2},
	};

	int		 err;
	te_expr *compiled = te_compile(expr, vars, sizeof(vars) / sizeof(vars[0]), &err);
	if (!compiled)
	{
		return;
	}

	float dx = (x_max - x_min) / width;

	int	 prev_px = 0, prev_py = 0;
	bool has_prev = false;

	for (int px = 0; px < width; px++)
	{
		x = x_min + px * dx;

		double result;
		if (!eval_safe(compiled, &result))
		{
			has_prev = false; // discontinuity
			continue;
		}

		int py = screen_y((float) result, y_min, y_max, height);

		if (has_prev)
		{
			hal_display_draw_line(prev_px, prev_py, px, py, color);
		}

		prev_px	 = px;
		prev_py	 = py;
		has_prev = true;
	}

	te_free(compiled);
}
