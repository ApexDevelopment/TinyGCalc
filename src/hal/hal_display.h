#ifndef HAL_DISPLAY_H
#define HAL_DISPLAY_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void hal_display_init(void);
void hal_display_present(void);
void hal_display_draw_pixel(int x, int y, uint16_t color);
void hal_display_draw_line(int x0, int y0, int x1, int y1, uint16_t color);
void hal_display_fill_screen(uint16_t color);
void hal_display_draw_text(int x, int y, const char* text, uint16_t color);

int hal_display_get_width(void);
int hal_display_get_height(void);

int hal_display_get_font_width(void);
int hal_display_get_font_height(void);

#ifdef __cplusplus
}
#endif

#endif // HAL_DISPLAY_H
