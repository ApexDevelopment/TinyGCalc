#include "core/utils/display.h"

void transform_coords(int *x, int *y, int width, int height, display_rotation_t rotation)
{
	int tx = *x, ty = *y;
	switch (rotation)
	{
	case DISPLAY_ROTATE_90:
		*x = height - 1 - ty;
		*y = tx;
		break;
	case DISPLAY_ROTATE_180:
		*x = width - 1 - tx;
		*y = height - 1 - ty;
		break;
	case DISPLAY_ROTATE_270:
		*x = ty;
		*y = width - 1 - tx;
		break;
	default: // DISPLAY_ROTATE_0
		break;
	}
}
