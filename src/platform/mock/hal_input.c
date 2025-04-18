#include "hal/hal_input.h"
#include <SDL2/SDL.h>

static uint8_t button_states[INPUT_BACK + 1] = {0};

void hal_input_init(void) {
    SDL_InitSubSystem(SDL_INIT_EVENTS);
}

bool hal_input_poll(input_event_t* event) {
    SDL_Event sdl_event;
    while (SDL_PollEvent(&sdl_event)) {
        if (sdl_event.type == SDL_QUIT) {
            exit(0);
        }
        if (sdl_event.type == SDL_KEYDOWN || sdl_event.type == SDL_KEYUP) {
            bool pressed = (sdl_event.type == SDL_KEYDOWN);
            input_event_t btn = INPUT_NONE;
            switch (sdl_event.key.keysym.sym) {
                case SDLK_LEFT:   btn = INPUT_LEFT; break;
                case SDLK_RIGHT:  btn = INPUT_RIGHT; break;
                case SDLK_UP:     btn = INPUT_UP; break;
                case SDLK_DOWN:   btn = INPUT_DOWN; break;
                case SDLK_RETURN: btn = INPUT_SELECT; break;
                case SDLK_ESCAPE: btn = INPUT_BACK; break;
                default: break;
            }
            if (btn != INPUT_NONE) {
                button_states[btn] = pressed;
                if (pressed && event) {
                    *event = btn;
                    return true;
                }
            }
        }
    }
    return false;
}

bool hal_input_is_pressed(input_event_t event) {
    return (event > INPUT_NONE && event <= INPUT_BACK) && button_states[event];
}
