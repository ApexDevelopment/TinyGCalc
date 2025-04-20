#ifndef TYPES_H
#define TYPES_H

typedef enum {
    MODE_TEXT = 0,
    MODE_GRAPH,
    MODE_TABLE,
	MODE_EQLIST
} ui_mode_t;

typedef enum {
    DISPLAY_ROTATE_0,
    DISPLAY_ROTATE_90,
    DISPLAY_ROTATE_180,
    DISPLAY_ROTATE_270
} display_rotation_t;

#endif // TYPES_H
