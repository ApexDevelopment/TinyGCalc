#include "hal/hal_display.h"
#include "core/plotter.h"
#include "core/graph_utils.h"
#include "core/ui_graph.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

void ui_graph_zoom(float *min, float *max, float factor)
{
	float		center	   = (*min + *max) / 2.0f;
	float		half_range = (*max - *min) / 2.0f * factor;
	const float min_range  = 0.0001f;
	if (half_range < min_range) return;
	*min = center - half_range;
	*max = center + half_range;
}

void ui_graph_render(const char *expr, float x_min, float x_max, float y_min, float y_max)
{
	hal_display_draw_text(0, 0, expr, 0xFFFF);

	int width  = hal_display_get_width();
	int height = hal_display_get_height();

	float x_scale = width / (x_max - x_min);
	float y_scale = x_scale;

	int x_axis = screen_x(0.0f, x_min, x_max, width);
	int y_axis = screen_y(0.0f, y_min, y_max, height);

	if (x_axis >= 0 && x_axis < width) hal_display_draw_line(x_axis, 0, x_axis, height - 1, 0x7BEF);
	if (y_axis >= 0 && y_axis < height) hal_display_draw_line(0, y_axis, width - 1, y_axis, 0x7BEF);

	float x_tick_spacing = compute_tick_spacing(x_scale, width);
	float y_tick_spacing = compute_tick_spacing(y_scale, height);

	float first_x_tick = x_min - fmodf(x_min, x_tick_spacing);
	bool  labeled_x	   = false;

	for (float x = first_x_tick; x <= x_max; x += x_tick_spacing)
	{
		int px = screen_x(x, x_min, x_max, width);
		if (px >= 0 && px < width)
		{
			hal_display_draw_line(px, y_axis - 2, px, y_axis + 2, 0x7BEF);

			if (!labeled_x && x > 0.0f)
			{
				char label[16];
				snprintf(label, sizeof(label), "%.2g", x);
				hal_display_draw_text(px / 6, (y_axis / 8) + 1, label, 0xFFFF);
				labeled_x = true;
			}
		}
	}

	float first_y_tick = y_min - fmodf(y_min, y_tick_spacing);
	bool  labeled_y	   = false;

	for (float y = first_y_tick; y <= y_max; y += y_tick_spacing)
	{
		int py = screen_y(y, y_min, y_max, height);
		if (py < 0 || py >= height) continue;

		hal_display_draw_line(x_axis - 2, py, x_axis + 2, py, 0x7BEF);

		if (!labeled_y && y > 0.0f)
		{
			char label[16];
			snprintf(label, sizeof(label), "%.2g", y);
			hal_display_draw_text((x_axis / 6) + 1, py / 8, label, 0xFFFF);
			labeled_y = true;
		}
	}

	plot_function(expr, x_min, x_max, y_min, y_max);
}
