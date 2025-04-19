#include "hal/hal_display.h"
#include "hal/hal_input.h"
#include "hal/hal_time.h"

#include "core/types.h"
#include "core/ui_text.h"
#include "core/ui_graph.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static char final_expr[256] = {0};
static mode_t mode = MODE_TEXT;

static float x_min = -10.0f;
static float x_max = 10.0f;
static float y_min = -1.5f;
static float y_max = 1.5f;

static bool cursor_visible = true;
static uint32_t last_cursor_toggle = 0;
static const uint32_t cursor_blink_interval_ms = 500;

static void render(void) {
    hal_display_fill_screen(0x0000);

    switch (mode) {
        case MODE_TEXT:
            ui_text_render();
            break;
        case MODE_GRAPH:
            ui_graph_render(final_expr, x_min, x_max, y_min, y_max);
            break;
        case MODE_TABLE:
            hal_display_draw_text(0, 0, "Table view coming soon", 0xFFFF);
            break;
    }

    hal_display_present();
}

int main(void) {
    hal_display_init();
    hal_input_init();

    render();

    while (true) {
        hal_input_event_t event;
        bool need_redraw = false;

        if (hal_input_poll(&event)) {
            if (event.type == INPUT_EVENT_CONTROL) {
                switch (event.control) {
                    case INPUT_LEFT:
                        x_min -= 0.5f; x_max -= 0.5f;
                        need_redraw = true;
                        break;
                    case INPUT_RIGHT:
                        x_min += 0.5f; x_max += 0.5f;
                        need_redraw = true;
                        break;
                    case INPUT_UP:
                        y_min += 0.5f; y_max += 0.5f;
                        need_redraw = true;
                        break;
                    case INPUT_DOWN:
                        y_min -= 0.5f; y_max -= 0.5f;
                        need_redraw = true;
                        break;
                    case INPUT_SELECT: // Zoom in
                        ui_graph_zoom(&x_min, &x_max, 0.8f);
                        ui_graph_zoom(&y_min, &y_max, 0.8f);
                        need_redraw = true;
                        break;
                    case INPUT_BACK: // Zoom out
                        ui_graph_zoom(&x_min, &x_max, 1.25f);
                        ui_graph_zoom(&y_min, &y_max, 1.25f);
                        need_redraw = true;
                        break;
                    case INPUT_ENTER: // Evaluate and switch to graph
                        snprintf(final_expr, sizeof(final_expr), "%s", expr_buf);
                        ui_text_clear();
                        mode = MODE_GRAPH;
                        need_redraw = true;
                        break;
                }
            } else if (event.type == INPUT_EVENT_KEY) {
                if (event.key == '\b' || event.key == 127) {
                    ui_text_handle_backspace();
                } else {
                    ui_text_handle_key(event.key);
                }

                if (mode != MODE_TEXT) {
                    mode = MODE_TEXT;
                }
                need_redraw = true;
            }

            if (need_redraw) {
                render();
            }
        }

        uint32_t now = hal_time_millis();
        if (mode == MODE_TEXT && now - last_cursor_toggle >= cursor_blink_interval_ms) {
            cursor_visible = !cursor_visible;
            last_cursor_toggle = now;
            render();
        }
    }

    return 0;
}
