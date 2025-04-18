#include "hal/hal_display.h"
#include "hal/hal_input.h"
#include "core/plotter.h"
#include <stdio.h>
#include <stdbool.h>

void render(char mode, const char* expr_buf, const char* final_expr, float x_min, float x_max, float y_offset) {
    hal_display_fill_screen(0x0000);

    switch (mode) {
        case 0:
            // Text entry mode
            hal_display_draw_text(0, 0, expr_buf, 0xFFFF);
            break;
        case 1:
            // Graph mode
            hal_display_draw_text(0, 0, final_expr, 0xFFFF); // optional header
            plot_function(final_expr, x_min, x_max, y_offset);
            break;
        case 2:
            // Table mode placeholder
            hal_display_draw_text(0, 0, "Table view coming soon", 0xFFFF);
            break;
    }

    hal_display_present();
}

int main(void) {
    char mode = 0;
    char final_expr[256] = {0};
    char expr_buf[256] = {0};
    size_t expr_len = 0;

    hal_display_init();
    hal_input_init();

    float x_min = -10.0f;
    float x_max = 10.0f;
    float y_offset = 0.0f;

    render(mode, expr_buf, final_expr, x_min, x_max, y_offset);

    while (true) {
        hal_input_event_t event;
        bool need_redraw = false;

        if (hal_input_poll(&event)) {
            if (event.type == INPUT_EVENT_CONTROL) {
                switch (event.control) {
                    case INPUT_LEFT:  x_min -= 0.5f; x_max -= 0.5f; need_redraw = true; break;
                    case INPUT_RIGHT: x_min += 0.5f; x_max += 0.5f; need_redraw = true; break;
                    case INPUT_UP:    y_offset -= 0.5f; need_redraw = true; break;
                    case INPUT_DOWN:  y_offset += 0.5f; need_redraw = true; break;
                    case INPUT_SELECT:
                        printf("Select pressed\n");
                        break;
                    case INPUT_ENTER:
                        snprintf(final_expr, sizeof(final_expr), "%s", expr_buf);
                        expr_len = 0;
                        expr_buf[0] = '\0';
                        mode = 1;
                        need_redraw = true;
                        break;
                    case INPUT_BACK:
                        printf("Exiting...\n");
                        return 0;
                }
            } else if (event.type == INPUT_EVENT_KEY) {
                if (expr_len < sizeof(expr_buf) - 1) {
                    expr_buf[expr_len++] = event.key;
                    expr_buf[expr_len] = 0;
                    mode = 0;
                    need_redraw = true;
                }
            }

            if (need_redraw) {
                render(mode, expr_buf, final_expr, x_min, x_max, y_offset);
            }
        }
    }

    return 0;
}
