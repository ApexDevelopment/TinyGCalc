#include "hal/hal_input.h"
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

void hal_input_init(void)
{
	i2c_init(I2C_PORT, I2C_FREQ);
	gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
	gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
	gpio_pull_up(I2C_SDA_PIN);
	gpio_pull_up(I2C_SCL_PIN);
}

bool hal_input_poll(hal_input_event_t *event)
{
	static uint8_t last_key = 0;
	uint8_t		   raw[2];
	uint8_t		   reg = KBD_REG_KEY;

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

	// Register the key press
	event->type = INPUT_EVENT_KEY;
	event->key	= (char) keycode;
	return true;
}
