#include "hal/hal_display.h"
#include "hal/hal_input.h"
#include "hal/hal_time.h"
#include "core/plotter.h"
#include "core/graph_utils.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

uint32_t	   last_cursor_toggle		= 0;
bool		   cursor_visible			= true;
const uint32_t cursor_blink_interval_ms = 500;
size_t		   cursor_pos				= 0;

char   final_expr[256] = {0};
char   expr_buf[256]   = {0};
size_t expr_len		   = 0;

typedef enum
{
	MODE_TEXT = 0,
	MODE_GRAPH,
	MODE_TABLE
} mode_t;

void zoom(float *min, float *max, float factor)
{
	float center	 = (*min + *max) / 2.0f;
	float half_range = (*max - *min) / 2.0f * factor;
	*min			 = center - half_range;
	*max			 = center + half_range;
}

void render(mode_t mode, float x_min, float x_max, float y_min, float y_max)
{
	hal_display_fill_screen(0x0000);

	switch (mode)
	{
	case MODE_TEXT:
		hal_display_draw_text(0, 0, expr_buf, 0xFFFF);
		break;
	case MODE_GRAPH:
	{
		hal_display_draw_text(0, 0, final_expr, 0xFFFF);

		int width  = hal_display_get_width();
		int height = hal_display_get_height();

		float x_scale = width / (x_max - x_min);
		float y_scale = x_scale; // lock aspect ratio

		int x_axis = screen_x(0.0f, x_min, x_max, width);
		int y_axis = screen_y(0.0f, y_min, y_max, height);

		// Draw Y axis
		if (x_axis >= 0 && x_axis < width) hal_display_draw_line(x_axis, 0, x_axis, height - 1, 0x7BEF);

		// Draw X axis
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
		float last_y_tick  = y_max + y_tick_spacing;
		bool  labeled_y	   = false;

		for (float y = first_y_tick; y <= last_y_tick; y += y_tick_spacing)
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

		plot_function(final_expr, x_min, x_max, y_min, y_max);
		break;
	}
	case MODE_TABLE:
		hal_display_draw_text(0, 0, "Table view coming soon", 0xFFFF);
		break;
	}

	if (mode == MODE_TEXT)
	{
		hal_display_draw_text(0, 0, expr_buf, 0xFFFF);
		if (cursor_visible)
		{
			hal_display_draw_text((int) cursor_pos, 0, "_", 0xAAAA);
		}
	}

	hal_display_present();
}

int main(void)
{
	mode_t mode = MODE_TEXT;

	float x_min = -10.0f;
	float x_max = 10.0f;
	float y_min = -1.5f;
	float y_max = 1.5f;

	hal_display_init();
	hal_input_init();

	render(mode, x_min, x_max, y_min, y_max);

	while (true)
	{
		hal_input_event_t event;
		bool			  need_redraw = false;

		if (hal_input_poll(&event))
		{
			if (event.type == INPUT_EVENT_CONTROL)
			{
				switch (event.control)
				{
				case INPUT_LEFT:
					x_min -= 0.5f;
					x_max -= 0.5f;
					need_redraw = true;
					break;
				case INPUT_RIGHT:
					x_min += 0.5f;
					x_max += 0.5f;
					need_redraw = true;
					break;
				case INPUT_UP:
					y_min += 0.5f;
					y_max += 0.5f;
					need_redraw = true;
					break;
				case INPUT_DOWN:
					y_min -= 0.5f;
					y_max -= 0.5f;
					need_redraw = true;
					break;
				case INPUT_SELECT:
					printf("Select pressed\n");
					break;
				case INPUT_ENTER:
					snprintf(final_expr, sizeof(final_expr), "%s", expr_buf);
					expr_len	= 0;
					expr_buf[0] = '\0';
					cursor_pos	= 0;
					mode		= MODE_GRAPH;
					need_redraw = true;
					break;
				case INPUT_BACK:
					printf("Exiting...\n");
					return 0;
				}
			}
			else if (event.type == INPUT_EVENT_KEY)
			{
				if (event.key == '\b' || event.key == 127)
				{
					if (cursor_pos > 0 && expr_len > 0)
					{
						memmove(&expr_buf[cursor_pos - 1], &expr_buf[cursor_pos], expr_len - cursor_pos + 1);
						cursor_pos--;
						expr_len--;
					}
				}
				else if (expr_len < sizeof(expr_buf) - 1)
				{
					memmove(&expr_buf[cursor_pos + 1], &expr_buf[cursor_pos], expr_len - cursor_pos + 1);
					expr_buf[cursor_pos] = event.key;
					cursor_pos++;
					expr_len++;
				}
				mode		= MODE_TEXT;
				need_redraw = true;
			}

			if (need_redraw)
			{
				render(mode, x_min, x_max, y_min, y_max);
			}
		}

		uint32_t now = hal_time_millis();
		if (now - last_cursor_toggle >= cursor_blink_interval_ms)
		{
			cursor_visible	   = !cursor_visible;
			last_cursor_toggle = now;
			if (mode == MODE_TEXT)
			{
				render(mode, x_min, x_max, y_min, y_max);
			}
		}
	}

	return 0;
}
