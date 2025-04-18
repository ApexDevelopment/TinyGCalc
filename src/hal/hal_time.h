#ifndef HAL_TIME_H
#define HAL_TIME_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Returns milliseconds since system start
uint32_t hal_time_millis(void);

#ifdef __cplusplus
}
#endif

#endif // HAL_TIME_H
