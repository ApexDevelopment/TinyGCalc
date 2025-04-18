#ifndef HAL_INPUT_H
#define HAL_INPUT_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    INPUT_NONE = 0,
    INPUT_LEFT,
    INPUT_RIGHT,
    INPUT_UP,
    INPUT_DOWN,
    INPUT_SELECT,
    INPUT_BACK
} input_event_t;

void hal_input_init(void);
bool hal_input_poll(input_event_t* event); // Returns true if event was read

// Optional convenience function for state-based polling (e.g. for holding buttons)
bool hal_input_is_pressed(input_event_t event);

#ifdef __cplusplus
}
#endif

#endif // HAL_INPUT_H
