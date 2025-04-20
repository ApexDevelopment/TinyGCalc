#include "core/ui/eqedit.h"
#include "core/eqlist.h"
#include "hal/hal_display.h"
#include <string.h>
#include <stdio.h>

static int cursor_row = 0;
static int cursor_col = 0;

void ui_eqedit_render(void)
{
	int font_w = hal_display_get_font_width();
	int font_h = hal_display_get_font_height();

	for (int i = 0; i < MAX_EQUATIONS; ++i)
	{
		char line[80];
		snprintf(line, sizeof(line), "Y%d=%s", i, eq_list[i].expr);
		hal_display_draw_text(0, i, line, 0xFFFF);
	}

	// Draw cursor
	hal_display_draw_text(3 + cursor_col, cursor_row, "_", 0xAAAA);
}

bool ui_eqedit_handle_key(char key)
{
	if (key == '\b' || key == 127)
	{
		if (cursor_col > 0)
		{
			char  *line = eq_list[cursor_row].expr;
			size_t len	= strlen(line);
			if (cursor_col <= len)
			{
				memmove(&line[cursor_col - 1], &line[cursor_col], len - cursor_col + 1);
				cursor_col--;

				if (len == 1)
				{
					eq_list[cursor_row].active = false; // Deactivate if empty
				}
			}
		}
		return true;
	}

	char  *line = eq_list[cursor_row].expr;
	size_t len	= strlen(line);
	if (len < EQUATION_LEN - 1)
	{
		memmove(&line[cursor_col + 1], &line[cursor_col], len - cursor_col + 1);
		line[cursor_col] = key;
		cursor_col++;

		// Activate this equation
		if (cursor_row < MAX_EQUATIONS)
		{
			eq_list[cursor_row].active = true;
		}

		return true;
	}

	return false;
}

bool ui_eqedit_handle_control(input_event_t btn, mode_t *mode_out)
{
	switch (btn)
	{
	case INPUT_UP:
		if (cursor_row > 0)
		{
			cursor_row--;
			cursor_col = strlen(eq_list[cursor_row].expr);
		}
		return true;
	case INPUT_DOWN:
		if (cursor_row < MAX_EQUATIONS - 1)
		{
			cursor_row++;
			cursor_col = strlen(eq_list[cursor_row].expr);
		}
		return true;
	case INPUT_LEFT:
		if (cursor_col > 0) cursor_col--;
		return true;
	case INPUT_RIGHT:
		if (cursor_col < strlen(eq_list[cursor_row].expr)) cursor_col++;
		return true;
	case INPUT_ENTER:
		*mode_out = MODE_GRAPH;
		return true;
	case INPUT_BACK:
		*mode_out = MODE_TEXT;
		return true;
	default:
		return false;
	}
}
