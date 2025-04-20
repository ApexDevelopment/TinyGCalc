#include "core/utils/graph.h"

// Converts world X to screen X
int screen_x(float x, float x_min, float x_max, int width)
{
	float x_range = x_max - x_min;
	return (int) (((x - x_min) / x_range) * width);
}

// Converts world Y to screen Y
int screen_y(float y, float y_min, float y_max, int height)
{
	float y_range = y_max - y_min;
	return (int) (((y_max - y) / y_range) * height);
}

float compute_tick_spacing(float pixels_per_unit, int screen_size_px)
{
	float target_px = screen_size_px / 10.0f; // Aim for ~10 ticks across
	float units		= target_px / pixels_per_unit;

	float scale = 1.0f;
	while (units >= 10.0f)
	{
		units /= 10.0f;
		scale *= 10.0f;
	}
	if (units >= 5.0f) return 5.0f * scale;
	if (units >= 2.0f) return 2.0f * scale;
	return 1.0f * scale;
}
