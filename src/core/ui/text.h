#ifndef TEXT_H
#define TEXT_H

#include "core/types.h"
#include "hal/hal_input.h"
#include <stddef.h>
#include <stdbool.h>

#define EXPR_BUF_LEN 256

extern char expr_buf[EXPR_BUF_LEN];
extern size_t expr_len;
extern size_t cursor_pos;

void ui_text_handle_key(char key);
bool ui_text_handle_control(input_event_t btn, ui_mode_t* mode_out);
void ui_text_handle_backspace(void);
void ui_text_render(void);
void ui_text_clear(void);

#endif // TEXT_H
