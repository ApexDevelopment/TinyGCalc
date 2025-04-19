#include "pico/stdlib.h"
#include "hal/hal_display.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 320

#define SPI_PORT spi1
#define PIN_MOSI 11 // GP11, pin 15
#define PIN_SCK 10	// GP10, pin 14
#define PIN_CS 13	// GP13, pin 17
#define PIN_DC 14	// GP14, pin 19
#define PIN_RST 15	// GP15, pin 20

static uint16_t framebuffer[SCREEN_HEIGHT][SCREEN_WIDTH];

static void st7789_write_command(uint8_t cmd)
{
	gpio_put(PIN_DC, 0);
	gpio_put(PIN_CS, 0);
	spi_write_blocking(SPI_PORT, &cmd, 1);
	gpio_put(PIN_CS, 1);
}

static void st7789_write_data(const uint8_t *data, size_t len)
{
	gpio_put(PIN_DC, 1);
	gpio_put(PIN_CS, 0);
	spi_write_blocking(SPI_PORT, data, len);
	gpio_put(PIN_CS, 1);
}

static void st7789_set_addr_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
	uint8_t data[4];

	st7789_write_command(0x2A); // CASET
	data[0] = x0 >> 8;
	data[1] = x0 & 0xFF;
	data[2] = x1 >> 8;
	data[3] = x1 & 0xFF;
	st7789_write_data(data, 4);

	st7789_write_command(0x2B); // RASET
	data[0] = y0 >> 8;
	data[1] = y0 & 0xFF;
	data[2] = y1 >> 8;
	data[3] = y1 & 0xFF;
	st7789_write_data(data, 4);

	st7789_write_command(0x2C); // RAMWR
}

void hal_display_init(void)
{
	spi_init(SPI_PORT, 62 * 1000 * 1000); // 62 MHz for fast transfer
	gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
	gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);

	gpio_init(PIN_CS);
	gpio_set_dir(PIN_CS, GPIO_OUT);
	gpio_put(PIN_CS, 1);

	gpio_init(PIN_DC);
	gpio_set_dir(PIN_DC, GPIO_OUT);

	gpio_init(PIN_RST);
	gpio_set_dir(PIN_RST, GPIO_OUT);

	// Hardware reset
	gpio_put(PIN_RST, 0);
	sleep_ms(50);
	gpio_put(PIN_RST, 1);
	sleep_ms(50);

	// Basic ST7789 init sequence (partial)
	st7789_write_command(0x36);				  // MADCTL
	st7789_write_data((uint8_t[]) {0x00}, 1); // Adjust for orientation if needed

	st7789_write_command(0x3A);				  // COLMOD
	st7789_write_data((uint8_t[]) {0x05}, 1); // 16-bit color

	st7789_write_command(0x21); // INVON (optional: turn on inversion for better contrast)
	st7789_write_command(0x11); // SLPOUT
	sleep_ms(120);
	st7789_write_command(0x29); // DISPON

	memset(framebuffer, 0, sizeof(framebuffer));
}

void hal_display_draw_pixel(int x, int y, uint16_t color)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		framebuffer[y][x] = color;
	}
}

void hal_display_fill_screen(uint16_t color)
{
	for (int y = 0; y < SCREEN_HEIGHT; ++y)
	{
		for (int x = 0; x < SCREEN_WIDTH; ++x)
		{
			framebuffer[y][x] = color;
		}
	}
}

void hal_display_draw_line(int x0, int y0, int x1, int y1, uint16_t color)
{
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = dx + dy;

	while (true)
	{
		hal_display_draw_pixel(x0, y0, color);
		if (x0 == x1 && y0 == y1) break;
		int e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void hal_display_present(void)
{
	st7789_set_addr_window(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

	gpio_put(PIN_DC, 1);
	gpio_put(PIN_CS, 0);
	for (int y = 0; y < SCREEN_HEIGHT; ++y)
	{
		for (int x = 0; x < SCREEN_WIDTH; ++x)
		{
			uint16_t color	 = framebuffer[y][x];
			uint8_t	 hi		 = color >> 8;
			uint8_t	 lo		 = color & 0xFF;
			uint8_t	 data[2] = {hi, lo};
			spi_write_blocking(SPI_PORT, data, 2);
		}
	}
	gpio_put(PIN_CS, 1);
}

void hal_display_draw_text(int x, int y, const char *text, uint16_t color)
{
	// Stub: font rendering not implemented yet
}

int hal_display_get_width(void) { return SCREEN_WIDTH; }

int hal_display_get_height(void) { return SCREEN_HEIGHT; }

int hal_display_get_font_width(void) { return FONT6X8_WIDTH; }

int hal_display_get_font_height(void) { return FONT6X8_HEIGHT; }
