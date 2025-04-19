#include "core/ui_text.h"
#include "hal/hal_display.h"

char   expr_buf[EXPR_BUF_LEN] = {0};
size_t expr_len				  = 0;
size_t cursor_pos			  = 0;

void ui_text_handle_key(char key)
{
	if (expr_len >= EXPR_BUF_LEN - 1) return;

	for (size_t i = expr_len + 1; i > cursor_pos; --i)
	{
		expr_buf[i] = expr_buf[i - 1];
	}

	expr_buf[cursor_pos] = key;
	expr_len++;
	cursor_pos++;
}

void ui_text_handle_backspace(void)
{
	if (cursor_pos == 0 || expr_len == 0) return;

	for (size_t i = cursor_pos - 1; i < expr_len; ++i)
	{
		expr_buf[i] = expr_buf[i + 1];
	}

	expr_len--;
	cursor_pos--;
}

void ui_text_clear(void)
{
	expr_buf[0] = '\0';
	expr_len	= 0;
	cursor_pos	= 0;
}

void ui_text_render(void)
{
	hal_display_draw_text(0, 0, expr_buf, 0xFFFF);
	hal_display_draw_text((int) cursor_pos, 0, "_", 0xAAAA);
}
