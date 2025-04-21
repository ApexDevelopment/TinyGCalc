#include "hal/hal_input.h"
#include "hal/hal_serial.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define I2C_PORT i2c1
#define I2C_SDA_PIN 7 // GP7, pin 10
#define I2C_SCL_PIN 6 // GP6, pin 9
#define I2C_FREQ 100000
#define KBD_ADDR 0x1F
#define KBD_REG_KEY 0x09

static bool wait_for_byte(uint32_t max_loops)
{
	while (!hal_serial_input_available() && --max_loops)
		;
	return hal_serial_input_available();
}

static int parse_two_digits(char a, char b)
{
	int result = 0;
	if (a >= '0' && a <= '9') result = (a - '0');
	if (b >= '0' && b <= '9') result = result * 10 + (b - '0');
	return result;
}

static bool try_parse_ansi(hal_input_event_t *event)
{
	// we already consumed the first 0x1B
	// wait for next byte
	while (!wait_for_byte(1000))
		;
	char c1 = hal_serial_read_char();

	if (c1 == '[')
	{
		// CSI – could be arrow or F‑key
		while (!wait_for_byte(1000))
			;
		char c2 = hal_serial_read_char();

		switch (c2)
		{
		// Arrow keys:
		case 'A':
			event->type	   = INPUT_EVENT_CONTROL;
			event->control = INPUT_UP;
			return true;
		case 'B':
			event->type	   = INPUT_EVENT_CONTROL;
			event->control = INPUT_DOWN;
			return true;
		case 'C':
			event->type	   = INPUT_EVENT_CONTROL;
			event->control = INPUT_RIGHT;
			return true;
		case 'D':
			event->type	   = INPUT_EVENT_CONTROL;
			event->control = INPUT_LEFT;
			return true;
		}

		// If it wasn’t A–D, maybe it’s a two‑digit F‑key (e.g. 11~, 12~…)
		if (c2 >= '0' && c2 <= '9')
		{
			char d1 = c2;
			while (!wait_for_byte(1000))
				;
			char d2 = hal_serial_read_char();
			while (!wait_for_byte(1000))
				;
			char term = hal_serial_read_char(); // should be '~'
			if (term == '~')
			{
				int code	= (d1 - '0') * 10 + (d2 - '0');
				event->type = INPUT_EVENT_CONTROL;
				switch (code)
				{
				case 11:
					event->control = INPUT_F1;
					return true;
				case 12:
					event->control = INPUT_F2;
					return true;
				case 13:
					event->control = INPUT_F3;
					return true;
				case 14:
					event->control = INPUT_F4;
					return true;
				case 15:
					event->control = INPUT_F5;
					return true;
				case 17:
					event->control = INPUT_F6;
					return true;
				}
			}
			else
			{
				// Flush and bail!
				while (hal_serial_input_available())
				{
					hal_serial_read_char();
				}

				hal_serial_write_string("BAD ESC SEQ\n");
				return false;
			}
		}
	}
	else if (c1 == 'O')
	{
		// SS3 – the old “ESC O P…U” for F1–F6
		while (!wait_for_byte(1000))
			;
		char c2		= hal_serial_read_char();
		event->type = INPUT_EVENT_CONTROL;
		switch (c2)
		{
		case 'P':
			event->control = INPUT_F1;
			return true;
		case 'Q':
			event->control = INPUT_F2;
			return true;
		case 'R':
			event->control = INPUT_F3;
			return true;
		case 'S':
			event->control = INPUT_F4;
			return true;
		case 'T':
			event->control = INPUT_F5;
			return true;
		case 'U':
			event->control = INPUT_F6;
			return true;
		}
	}

	// If we get here, it was a lone ESC (or something unrecognized).
	event->type	   = INPUT_EVENT_CONTROL;
	event->control = INPUT_BACK;
	return true;
}

void hal_input_init(void)
{
	i2c_init(I2C_PORT, I2C_FREQ);
	gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
	gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
	gpio_pull_up(I2C_SDA_PIN);
	gpio_pull_up(I2C_SCL_PIN);
	hal_serial_init();
}

bool hal_input_poll(hal_input_event_t *event)
{
	static uint8_t last_key = 0;

	// First: check serial input
	if (hal_serial_input_available())
	{
		char c = hal_serial_read_char();
		if (c == 0x1B)
		{
			// try to parse a full ANSI sequence
			return try_parse_ansi(event);
		}

		// Otherwise, treat it as a normal character
		event->type = INPUT_EVENT_KEY;

		if (c > 0x1F && c < 0x7F) // Printable ASCII
		{
			event->key = c;
		}
		else if (c == '\b' || c == 0x7F) // Backspace
		{
			event->key = '\b';
		}
		else if (c == '\n' || c == '\r') // Enter
		{
			event->type	   = INPUT_EVENT_CONTROL;
			event->control = INPUT_ENTER;
		}
		else
		{
			event->key = '?';
		}

		hal_serial_write_char(c); // Echo
		return true;
	}

	// Then: check I2C keyboard
	uint8_t raw[2];
	uint8_t reg = KBD_REG_KEY;

	int result = i2c_write_blocking(I2C_PORT, KBD_ADDR, &reg, 1, true);
	if (result != 1) return false;

	result = i2c_read_blocking(I2C_PORT, KBD_ADDR, raw, 2, false);
	if (result != 2) return false;

	uint8_t keycode = raw[0];

	// No key pressed: clear last_key
	if (keycode == 0)
	{
		last_key = 0;
		return false;
	}

	// Debounce: ignore repeated key holds
	if (keycode == last_key) return false;

	last_key = keycode;

	event->type = INPUT_EVENT_KEY;
	event->key	= (char) keycode;
	return true;
}
