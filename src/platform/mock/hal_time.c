#include "hal/hal_time.h"
#include <SDL2/SDL.h>

uint32_t hal_time_millis(void) { return SDL_GetTicks(); }
