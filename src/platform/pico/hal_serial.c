#include "hal/hal_serial.h"
#include "pico/stdlib.h"

#include <stdint.h>
#include <stdio.h>

static int buffered_char = PICO_ERROR_TIMEOUT;

void hal_serial_init(void)
{
	stdio_init_all();

	// Flush any buffered input
	while (hal_serial_input_available())
	{
		(void) hal_serial_read_char();
	}
}

bool hal_serial_input_available(void)
{
	if (buffered_char == PICO_ERROR_TIMEOUT)
	{
		buffered_char = getchar_timeout_us(0);
	}
	return buffered_char != PICO_ERROR_TIMEOUT;
}

char hal_serial_read_char(void)
{
	int result;

	if (buffered_char != PICO_ERROR_TIMEOUT)
	{
		result		  = buffered_char;
		buffered_char = PICO_ERROR_TIMEOUT;
	}
	else
	{
		result = getchar(); // fallback if polled directly
		if (result == EOF)
		{
			return 0;
		}
	}

	return (char) (uint8_t) result;
}

void hal_serial_write_char(char c) { putchar(c); }

void hal_serial_write_string(const char *s) { printf("%s", s); }
