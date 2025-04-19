#ifndef UI_EQEDIT_H
#define UI_EQEDIT_H

#include "hal/hal_input.h"
#include "core/types.h"

void ui_eqedit_render(void);
bool ui_eqedit_handle_key(char key);
bool ui_eqedit_handle_control(input_event_t btn, mode_t* mode_out);

#endif // UI_EQEDIT_H
