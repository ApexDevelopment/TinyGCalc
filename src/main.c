#include "hal/hal_display.h"
#include "hal/hal_input.h"
#include "hal/hal_time.h"

#include "core/types.h"
#include "core/ui/eqedit.h"
#include "core/ui/plot.h"
#include "core/ui/settings.h"
#include "core/ui/text.h"

#include <stdbool.h>
#include <string.h>

static char		 final_expr[256] = {0};
static ui_mode_t mode			 = MODE_TEXT;

static bool			  cursor_visible		   = true;
static uint32_t		  last_cursor_toggle	   = 0;
static const uint32_t cursor_blink_interval_ms = 500;

static void render(void)
{
	hal_display_fill_screen(0x0000);

	switch (mode)
	{
	case MODE_TEXT:
		ui_text_render();
		break;
	case MODE_GRAPH:
		ui_plot_render();
		break;
	case MODE_TABLE:
		hal_display_draw_text(0, 0, "Table view coming soon", 0xFFFF);
		break;
	case MODE_EQLIST:
		ui_eqedit_render();
		break;
	case MODE_SETTINGS:
		ui_settings_render();
		break;
	default:
		break;
	}

	hal_display_present();
}

int main(void)
{
	hal_display_init();
	hal_input_init();

	render();

	while (true)
	{
		hal_input_event_t event;
		bool			  need_redraw = false;

		if (hal_input_poll(&event))
		{
			if (event.type == INPUT_EVENT_CONTROL)
			{
				if (event.control == INPUT_F1)
				{
					mode		= MODE_EQLIST;
					need_redraw = true;
				}
				else if (event.control == INPUT_F2)
				{
					mode		= MODE_SETTINGS;
					need_redraw = true;
				}
				else
				{
					bool handled = false;

					switch (mode)
					{
					case MODE_TEXT:
						handled = ui_text_handle_control(event.control, &mode);
						break;
					case MODE_GRAPH:
						handled = ui_plot_handle_control(event.control, &mode);
						break;
					case MODE_TABLE:
						mode	= MODE_TEXT;
						handled = true;
						break;
					case MODE_EQLIST:
						handled = ui_eqedit_handle_control(event.control, &mode);
						break;
					case MODE_SETTINGS:
						handled = ui_settings_handle_control(event.control, &mode);
						break;
					default:
						break;
					}

					if (handled)
					{
						need_redraw = true;
					}
				}
			}
			else if (event.type == INPUT_EVENT_KEY)
			{
				bool handled = false;

				switch (mode)
				{
				case MODE_TEXT:
					ui_text_handle_key(event.key);
					handled = true;
					break;
				case MODE_EQLIST:
					handled = ui_eqedit_handle_key(event.key);
					break;
				default:
					break;
				}

				if (handled)
				{
					need_redraw = true;
				}
			}

			if (need_redraw)
			{
				render();
			}
		}

		uint32_t now = hal_time_millis();
		if (mode == MODE_TEXT && now - last_cursor_toggle >= cursor_blink_interval_ms)
		{
			cursor_visible	   = !cursor_visible;
			last_cursor_toggle = now;
			render();
		}
	}

	return 0;
}
