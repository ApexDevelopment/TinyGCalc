#include "core/repl.h"
#include "hal/hal_display.h"
#include <string.h>

static repl_entry_t history[REPL_HISTORY_SIZE];
static int			history_len = 0;

void repl_clear(void) { history_len = 0; }

int repl_line_count(void)
{
	return history_len * 2; // 2 lines per entry: expr + result
}

void repl_add_entry(const char *expr, const char *result)
{
	if (history_len >= REPL_HISTORY_SIZE)
	{
		memmove(&history[0], &history[1], sizeof(repl_entry_t) * (REPL_HISTORY_SIZE - 1));
		history_len = REPL_HISTORY_SIZE - 1;
	}

	strncpy(history[history_len].expr, expr, REPL_LINE_MAX);
	strncpy(history[history_len].result, result, REPL_LINE_MAX);
	history_len++;
}

void repl_render(void)
{
	int y			 = 0;
	int screen_width = hal_display_get_width();
	int char_width	 = hal_display_get_font_width();

	for (int i = 0; i < history_len; ++i)
	{
		// Draw input expression on the left, result on the right
		hal_display_draw_text(0, y++, history[i].expr, 0xFFFF);

		size_t result_len = strlen(history[i].result);
		int	   result_px  = (int) (screen_width - result_len * char_width);
		int	   result_col = result_px / char_width;

		if (result_col < 0) result_col = 0; // Clamp in case of overflow

		hal_display_draw_text(result_col, y++, history[i].result, 0xCFFF);
	}
}
