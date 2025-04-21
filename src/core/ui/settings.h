#ifndef SETTINGS_H
#define SETTINGS_H

#include "core/types.h"
#include "hal/hal_input.h"
#include <stdbool.h>

extern bool				  angle_mode_deg;
extern display_rotation_t rotation_mode;
extern int ui_settings_cursor;

void ui_settings_render(void);
bool ui_settings_handle_control(input_event_t event, ui_mode_t *mode_out);

#endif // SETTINGS_H
