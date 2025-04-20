#ifndef DISPLAY_H
#define DISPLAY_H

#include "core/types.h"
#include <stdint.h>

// Transforms coordinates (x, y) in-place based on rotation.
void transform_coords(int* x, int* y, int width, int height, display_rotation_t rotation);

#endif // DISPLAY_H
