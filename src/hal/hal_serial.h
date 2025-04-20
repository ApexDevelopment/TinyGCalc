#ifndef HAL_SERIAL_H
#define HAL_SERIAL_H

#include <stdbool.h>

void hal_serial_init(void);
bool hal_serial_input_available(void);
char hal_serial_read_char(void);
void hal_serial_write_char(char c);
void hal_serial_write_string(const char* s);

#endif // HAL_SERIAL_H
