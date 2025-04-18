#include "hal/hal_time.h"
#include "pico/time.h"

uint32_t hal_time_millis(void) { return to_ms_since_boot(get_absolute_time()); }
