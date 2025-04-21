#include "core/ui/settings.h"
#include "hal/hal_display.h"

#include <stdio.h>

typedef enum
{
	SETTING_BOOL,
	SETTING_ENUM
} setting_type_t;

typedef struct
{
	const char	  *label;
	setting_type_t type;
	void		  *value;
} setting_entry_t;

bool			   angle_mode_deg = false;
display_rotation_t rotation_mode  = DISPLAY_ROTATE_0;

static setting_entry_t settings[] = {{"Use Degrees", SETTING_BOOL, &angle_mode_deg},
									 {"Screen Rotation", SETTING_ENUM, &rotation_mode}};

static const int settings_count = 2;

int ui_settings_cursor = 0;

void ui_settings_render(void)
{
	hal_display_fill_screen(0x0000);
	hal_display_draw_text(0, 0, "SETTINGS", 0xFFFF);

	for (int i = 0; i < settings_count; ++i)
	{
		char				   line[32];
		const setting_entry_t *s = &settings[i];

		switch (s->type)
		{
		case SETTING_BOOL:
			snprintf(line, sizeof(line), "(%c) %s", *(bool *) s->value ? 'x' : ' ', s->label);
			break;
		case SETTING_ENUM:
			int v = *(uint8_t *) s->value; // technically not a safe cast from enum but works fine in practice
			snprintf(line, sizeof(line), "(%d) %s", v, s->label);
			break;
		}

		uint16_t color = (i == ui_settings_cursor) ? 0xFFE0 : 0xFFFF;
		hal_display_draw_text(0, i + 2, line, color);
	}
}

bool ui_settings_handle_control(input_event_t control, ui_mode_t *mode_out)
{
	switch (control)
	{
	case INPUT_UP:
		if (ui_settings_cursor > 0) ui_settings_cursor--;
		return true;
	case INPUT_DOWN:
		if (ui_settings_cursor < settings_count - 1) ui_settings_cursor++;
		return true;
	case INPUT_ENTER:
		switch (ui_settings_cursor)
		{
		case 0: // Angle Mode
			angle_mode_deg = !angle_mode_deg;
			break;

		case 1: // Rotation Mode
			rotation_mode = (rotation_mode + 1) % 4;
			hal_display_set_rotation(rotation_mode);
			break;
		default:
			break;
		}
		return true;
	case INPUT_BACK:
		*mode_out = MODE_TEXT;
		return true;
	default:
		return false;
	}
}
