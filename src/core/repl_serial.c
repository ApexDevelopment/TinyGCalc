#include "core/repl_serial.h"
#include "hal/hal_serial.h"
#include "tinyexpr.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

#define REPL_BUFFER_SIZE 128

static char	  buffer[REPL_BUFFER_SIZE] = {0};
static size_t len					   = 0;
static bool	  prompt_shown			   = false;

void repl_serial_init(void)
{
	hal_serial_init();
	hal_serial_write_string("TinyGCalc Serial REPL ready.\r\n");
	hal_serial_write_string("> ");
	prompt_shown = true;
}

void repl_serial_poll(void)
{
	if (!hal_serial_input_available()) return;

	char c = hal_serial_read_char();

	if (c == '\r' || c == '\n')
	{
		hal_serial_write_string("\r\n");

		if (len > 0)
		{
			buffer[len] = '\0';

			double		x	   = 0;
			te_variable vars[] = {{"x", &x}};
			int			err;
			te_expr	   *expr = te_compile(buffer, vars, 1, &err);

			if (expr)
			{
				double result = te_eval(expr);
				if (isnan(result) || isinf(result))
				{
					hal_serial_write_string("= [invalid]\r\n");
				}
				else
				{
					char out[64];
					snprintf(out, sizeof(out), "= %.8g\r\n", result);
					hal_serial_write_string(out);
				}
				te_free(expr);
			}
			else
			{
				hal_serial_write_string("= [syntax error]\r\n");
			}

			len = 0;
		}

		hal_serial_write_string("> ");
		prompt_shown = true;
		return;
	}

	if ((c == '\b' || c == 127) && len > 0)
	{
		len--;
		hal_serial_write_string("\b \b");
		return;
	}

	if (len < REPL_BUFFER_SIZE - 1 && c >= 32 && c <= 126)
	{
		buffer[len++] = c;
		hal_serial_write_char(c);
		prompt_shown = false;
	}
}
