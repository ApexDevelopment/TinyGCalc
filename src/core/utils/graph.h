#ifndef GRAPH_H
#define GRAPH_H

// Returns the screen X coordinate for a given world X
int screen_x(float x, float x_min, float x_max, int width);

// Returns the screen Y coordinate for a given world Y
int screen_y(float y, float y_min, float y_max, int height);

// Computes the tick spacing for a given pixel density and screen size
float compute_tick_spacing(float pixels_per_unit, int screen_size_px);

#endif // GRAPH_H
