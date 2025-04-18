#include "hal/hal_display.h"
#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdlib.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;

void hal_display_init(void) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("TinyGCalc", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer); // Clear the screen once
    // Do not present here; let main/rendering logic decide when to flush
}

void hal_display_fill_screen(uint16_t color) {
    uint8_t r = (color >> 11) & 0x1F;
    uint8_t g = (color >> 5) & 0x3F;
    uint8_t b = color & 0x1F;
    r = (r << 3) | (r >> 2);
    g = (g << 2) | (g >> 4);
    b = (b << 3) | (b >> 2);

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void hal_display_draw_pixel(int x, int y, uint16_t color) {
    uint8_t r = (color >> 11) & 0x1F;
    uint8_t g = (color >> 5) & 0x3F;
    uint8_t b = color & 0x1F;
    r = (r << 3) | (r >> 2);
    g = (g << 2) | (g >> 4);
    b = (b << 3) | (b >> 2);

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderDrawPoint(renderer, x, y);
}

void hal_display_draw_line(int x0, int y0, int x1, int y1, uint16_t color) {
    uint8_t r = (color >> 11) & 0x1F;
    uint8_t g = (color >> 5) & 0x3F;
    uint8_t b = color & 0x1F;
    r = (r << 3) | (r >> 2);
    g = (g << 2) | (g >> 4);
    b = (b << 3) | (b >> 2);

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderDrawLine(renderer, x0, y0, x1, y1);
}

void hal_display_present(void) {
    SDL_RenderPresent(renderer);
}

int hal_display_get_width(void) {
    return SCREEN_WIDTH;
}

int hal_display_get_height(void) {
    return SCREEN_HEIGHT;
}
