#ifndef UI_TEXT_H
#define UI_TEXT_H

#include <stddef.h>
#include <stdbool.h>
#include "hal/hal_input.h"

#define EXPR_BUF_LEN 256

extern char expr_buf[EXPR_BUF_LEN];
extern size_t expr_len;
extern size_t cursor_pos;

void ui_text_handle_key(char key);
void ui_text_handle_backspace(void);
void ui_text_render(void);
void ui_text_clear(void);

#endif // UI_TEXT_H
