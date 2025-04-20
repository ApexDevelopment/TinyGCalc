#include "tinyexpr.h"
#include "core/repl.h"
#include "core/ui/text.h"
#include "hal/hal_display.h"
#include <math.h>
#include <stdio.h>

char   expr_buf[EXPR_BUF_LEN] = {0};
size_t expr_len				  = 0;
size_t cursor_pos			  = 0;

void ui_text_handle_key(char key)
{
	if (key == '\b' || key == 127)
	{
		ui_text_handle_backspace();
		return;
	}

	if (expr_len >= EXPR_BUF_LEN - 1) return;

	for (size_t i = expr_len + 1; i > cursor_pos; --i)
	{
		expr_buf[i] = expr_buf[i - 1];
	}

	expr_buf[cursor_pos] = key;
	expr_len++;
	cursor_pos++;
}

bool ui_text_handle_control(input_event_t btn, ui_mode_t *mode_out)
{
	switch (btn)
	{
	case INPUT_ENTER:
	{
		if (expr_len == 0) return false;

		int			err	   = 0;
		double		x	   = 0;
		te_variable vars[] = {{"x", &x}};
		te_expr	   *expr   = te_compile(expr_buf, vars, 1, &err);

		char out_expr[REPL_LINE_MAX];
		char out_result[REPL_LINE_MAX];

		snprintf(out_expr, sizeof(out_expr), "%s", expr_buf);

		if (expr)
		{
			double result = te_eval(expr);
			if (isnan(result) || isinf(result))
			{
				snprintf(out_result, sizeof(out_result), "= [invalid]");
			}
			else
			{
				snprintf(out_result, sizeof(out_result), "= %.8g", result);
			}
			te_free(expr);
		}
		else
		{
			snprintf(out_result, sizeof(out_result), "= [syntax error]");
		}

		repl_add_entry(out_expr, out_result);
		ui_text_clear();
		return true;
	}

	default:
		return false;
	}
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
	repl_render();

	int y = repl_line_count();
	hal_display_draw_text(0, y, expr_buf, 0xFFFF);
	hal_display_draw_text((int) cursor_pos, y, "_", 0xAAAA);
}
