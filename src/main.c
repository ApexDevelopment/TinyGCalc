#include "hal/hal_display.h"
#include "hal/hal_input.h"
#include "core/plotter.h"
#include <stdio.h>
#include <stdbool.h>

int main(void) {
    char expr_buf[256] = {0};
    size_t expr_len = 0;
    hal_display_init();
    hal_input_init();

    float x_min = -10.0f;
    float x_max = 10.0f;
    float y_offset = 0.0f;

    // Initial draw
    hal_display_fill_screen(0x0000);
    plot_function("sin(x) + y", x_min, x_max, y_offset);
    hal_display_present();

    while (true) {
        hal_input_event_t event;

        if (hal_input_poll(&event)) {
            if (event.type == INPUT_EVENT_CONTROL) {
                switch (event.control) {
                    case INPUT_LEFT:
                        x_min -= 0.5f;
                        x_max -= 0.5f;
                        break;
                    case INPUT_RIGHT:
                        x_min += 0.5f;
                        x_max += 0.5f;
                        break;
                    case INPUT_UP:
                        y_offset -= 0.5f;
                        break;
                    case INPUT_DOWN:
                        y_offset += 0.5f;
                        break;
                    case INPUT_SELECT:
                        printf("Select pressed\n");
                        break;
                    case INPUT_BACK:
                        printf("Exiting...\n");
                        return 0;
                    default:
                        break;
                }

                hal_display_fill_screen(0x0000);
                plot_function("sin(x) + y", x_min, x_max, y_offset);
                hal_display_present();
            }
            else if (event.type == INPUT_EVENT_KEY) {
                if (expr_len < sizeof(expr_buf) - 1) {
                    expr_buf[expr_len++] = event.key;
                    expr_buf[expr_len] = 0;
                }
                hal_display_fill_screen(0x0000);
                plot_function("sin(x) + y", x_min, x_max, y_offset);
                hal_display_draw_text(0, 0, expr_buf, 0xFFFF);
                hal_display_present();
            }
        }
    }


    return 0;
}
