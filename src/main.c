#include "hal/hal_display.h"
#include "hal/hal_input.h"
#include "hal/hal_time.h"
#include "core/plotter.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef enum {
    MODE_TEXT = 0,
    MODE_GRAPH,
    MODE_TABLE
} mode_t;

uint32_t last_cursor_toggle = 0;
bool cursor_visible = true;
const uint32_t cursor_blink_interval_ms = 500;
size_t cursor_pos = 0;

char final_expr[256] = {0};
char expr_buf[256] = {0};
size_t expr_len = 0;

void render(mode_t mode, float x_min, float x_max, float y_offset) {
    hal_display_fill_screen(0x0000);

    switch (mode) {
        case MODE_TEXT:
            hal_display_draw_text(0, 0, expr_buf, 0xFFFF);
            break;
        case MODE_GRAPH:
            hal_display_draw_text(0, 0, final_expr, 0xFFFF); // optional header
            plot_function(final_expr, x_min, x_max, y_offset);
            break;
        case MODE_TABLE:
            hal_display_draw_text(0, 0, "Table view coming soon", 0xFFFF);
            break;
    }

    if (mode == MODE_TEXT) {
        hal_display_draw_text(0, 0, expr_buf, 0xFFFF);
    
        if (cursor_visible) {
            // Draw a blinking underscore cursor after the text
            size_t col = expr_len;
            hal_display_draw_text((int)cursor_pos, 0, "_", 0xAAAA);
        }
    }    

    hal_display_present();
}

int main(void) {
    mode_t mode = MODE_TEXT;

    hal_display_init();
    hal_input_init();

    float x_min = -10.0f;
    float x_max = 10.0f;
    float y_offset = 0.0f;

    render(mode, x_min, x_max, y_offset);

    while (true) {
        uint32_t now = hal_time_millis();
        bool need_redraw = false;
        
        hal_input_event_t event;

        if (hal_input_poll(&event)) {
            if (event.type == INPUT_EVENT_CONTROL) {
                switch (event.control) {
                    case INPUT_LEFT:
                        if (mode == 0) {
                            if (cursor_pos > 0) cursor_pos--;
                        }
                        else if (mode == 1) {
                            x_min -= 0.5f;
                            x_max -= 0.5f;
                        }
                        need_redraw = true;
                        break;
                    case INPUT_RIGHT:
                        if (mode == 0) {
                            if (cursor_pos < expr_len) cursor_pos++;
                        }
                        else if (mode == 1) {
                            x_min += 0.5f;
                            x_max += 0.5f;
                        }
                        need_redraw = true;
                        break;
                    case INPUT_UP:    y_offset -= 0.5f; need_redraw = true; break;
                    case INPUT_DOWN:  y_offset += 0.5f; need_redraw = true; break;
                    case INPUT_SELECT:
                        printf("Select pressed\n");
                        break;
                    case INPUT_ENTER:
                        snprintf(final_expr, sizeof(final_expr), "%s", expr_buf);
                        expr_len = 0;
                        expr_buf[0] = '\0';
                        cursor_pos = 0;
                        mode = 1;
                        need_redraw = true;
                        break;
                    case INPUT_BACK:
                        printf("Exiting...\n");
                        return 0;
                }
            }
            else if (event.type == INPUT_EVENT_KEY) {
                if (event.key == '\b' || event.key == 127) {  // backspace
                    if (cursor_pos > 0 && expr_len > 0) {
                        // Shift characters left from cursor
                        memmove(&expr_buf[cursor_pos - 1], &expr_buf[cursor_pos], expr_len - cursor_pos + 1);
                        cursor_pos--;
                        expr_len--;
                    }
                } else if (expr_len < sizeof(expr_buf) - 1) {
                    // Shift characters right from cursor
                    memmove(&expr_buf[cursor_pos + 1], &expr_buf[cursor_pos], expr_len - cursor_pos + 1);
                    expr_buf[cursor_pos] = event.key;
                    cursor_pos++;
                    expr_len++;
                }
            
                mode = 0;
                need_redraw = true;
            }

            if (need_redraw) {
                render(mode, x_min, x_max, y_offset);
            }
        }

        if (now - last_cursor_toggle >= cursor_blink_interval_ms) {
            cursor_visible = !cursor_visible;
            last_cursor_toggle = now;
            if (mode == 0) {
                render(mode, x_min, x_max, y_offset);
            }
        }
    }

    return 0;
}
