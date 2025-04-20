#include "core/font6x8.h"
#include "hal/hal_display.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <string.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_BUFFER_SIZE (OLED_WIDTH * OLED_HEIGHT / 8)

#define OLED_SPI spi0
#define OLED_SPI_BAUDRATE 1000000
#define OLED_MOSI 19
#define OLED_SCK 18
#define OLED_CS 17
#define OLED_DC 21
#define OLED_RST 20

static uint8_t buffer[OLED_BUFFER_SIZE];

static inline void oled_command(uint8_t cmd)
{
	gpio_put(OLED_DC, 0);
	gpio_put(OLED_CS, 0);
	spi_write_blocking(OLED_SPI, &cmd, 1);
	gpio_put(OLED_CS, 1);
}

static inline void oled_data(uint8_t *data, size_t len)
{
	gpio_put(OLED_DC, 1);
	gpio_put(OLED_CS, 0);
	spi_write_blocking(OLED_SPI, data, len);
	gpio_put(OLED_CS, 1);
}

void hal_display_init(void)
{
	spi_init(OLED_SPI, OLED_SPI_BAUDRATE);
	gpio_set_function(OLED_SCK, GPIO_FUNC_SPI);	 // SCK
	gpio_set_function(OLED_MOSI, GPIO_FUNC_SPI); // MOSI

	gpio_init(OLED_CS);
	gpio_set_dir(OLED_CS, GPIO_OUT);
	gpio_put(OLED_CS, 1);
	gpio_init(OLED_DC);
	gpio_set_dir(OLED_DC, GPIO_OUT);
	gpio_init(OLED_RST);
	gpio_set_dir(OLED_RST, GPIO_OUT);

	gpio_put(OLED_RST, 0);
	sleep_ms(10);
	gpio_put(OLED_RST, 1);
	sleep_ms(10);

	// SH1106 init sequence (basic)
	oled_command(0xAE); // Display OFF
	oled_command(0xA1); // Segment remap
	oled_command(0xC8); // COM scan dir
	oled_command(0xDA);
	oled_command(0x12); // COM pins
	oled_command(0x81);
	oled_command(0xFF); // Contrast
	oled_command(0xA4); // Resume to RAM content display
	oled_command(0xA6); // Normal display
	oled_command(0xD5);
	oled_command(0x80); // Clock
	oled_command(0x8D);
	oled_command(0x14); // Charge pump
	oled_command(0xAF); // Display ON

	sleep_ms(100); // give it time to wake up

	hal_display_fill_screen(0x0000);
	hal_display_present();
}

void hal_display_fill_screen(uint16_t color) { memset(buffer, color ? 0xFF : 0x00, OLED_BUFFER_SIZE); }

void hal_display_present(void)
{
	for (uint8_t page = 0; page < 8; ++page)
	{
		oled_command(0xB0 + page); // page address
		oled_command(0x02);		   // lower column start address (SH1106 quirk)
		oled_command(0x10);		   // higher column start address
		oled_data(&buffer[OLED_WIDTH * page], OLED_WIDTH);
	}
}

void hal_display_draw_pixel(int x, int y, uint16_t color)
{
	if (x < 0 || x >= OLED_WIDTH || y < 0 || y >= OLED_HEIGHT) return;
	int byte_index = x + (y / 8) * OLED_WIDTH;
	if (color)
	{
		buffer[byte_index] |= (1 << (y % 8));
	}
	else
	{
		buffer[byte_index] &= ~(1 << (y % 8));
	}
}

void hal_display_draw_text(int x_char, int y_char, const char *text, uint16_t color)
{
	int px = x_char * hal_display_get_font_width();
	int py = y_char * hal_display_get_font_height();

	while (*text)
	{
		char		   c	 = *text++;
		const uint8_t *glyph = font6x8[(uint8_t) c];

		for (int col = 0; col < 6; ++col)
		{
			uint8_t bits = glyph[col];
			for (int row = 0; row < 8; ++row)
			{
				bool on = bits & (1 << row);
				hal_display_draw_pixel(px + col, py + row, on ? color : 0x0000);
			}
		}

		px += 6;
	}
}

void hal_display_draw_line(int x0, int y0, int x1, int y1, uint16_t color)
{
	// STUB: Bresenham or naive implementation can go here later
}

int hal_display_get_width(void) { return OLED_WIDTH; }

int hal_display_get_height(void) { return OLED_HEIGHT; }

int hal_display_get_font_width(void) { return 6; }

int hal_display_get_font_height(void) { return 8; }
