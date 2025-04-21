#include "hal/hal_display.h"
#include "core/font6x8.h"
#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

static SDL_Window	*window	  = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture	*texture  = NULL;

static uint16_t framebuffer[SCREEN_HEIGHT][SCREEN_WIDTH];

void hal_display_init(void)
{
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("TinyGCalc", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
							  SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);					 // Clear the screen
	memset(framebuffer, 0, sizeof(framebuffer)); // Clear the framebuffer
	texture =
		SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB565, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
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

void hal_display_draw_pixel(int x, int y, uint16_t color)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		framebuffer[y][x] = color;
	}
}

void hal_display_draw_line(int x0, int y0, int x1, int y1, uint16_t color)
{
	// Bresenham’s line algorithm
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = dx + dy, e2;

	while (1)
	{
		hal_display_draw_pixel(x0, y0, color);

		if (x0 == x1 && y0 == y1) break;

		e2 = 2 * err;
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
	void *pixels;
	int	  pitch;
	SDL_LockTexture(texture, NULL, &pixels, &pitch);
	memcpy(pixels, framebuffer, sizeof(framebuffer));
	SDL_UnlockTexture(texture);

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void hal_display_draw_text(int x, int y, const char *text, uint16_t color)
{
	int char_width	= hal_display_get_font_width();
	int char_height = hal_display_get_font_height();

	int cx = x * char_width;
	int cy = y * char_height;

	for (int i = 0; text[i] != 0; ++i)
	{
		char c = text[i];
		// Printable ASCII range
		if (c < 32 || c > 127) continue;

		const uint8_t *glyph = font6x8[c];

		for (int col = 0; col < char_width; ++col)
		{
			uint8_t bits = glyph[col];
			for (int row = 0; row < char_height; ++row)
			{
				if (bits & (1 << row))
				{
					hal_display_draw_pixel(cx + col, cy + row, color);
				}
			}
		}

		cx += char_width;
	}
}

int hal_display_get_width(void) { return SCREEN_WIDTH; }

int hal_display_get_height(void) { return SCREEN_HEIGHT; }

int hal_display_get_font_width(void) { return FONT6X8_WIDTH; }

int hal_display_get_font_height(void) { return FONT6X8_HEIGHT; }

void hal_display_set_rotation(display_rotation_t rotation)
{
	// No rotation in this mock implementation
}
