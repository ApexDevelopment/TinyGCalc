#include "hal/hal_input.h"
#include <SDL2/SDL.h>
#include <stdlib.h>

static uint8_t button_states[INPUT_BACK + 1] = {0};

void hal_input_init(void) { SDL_InitSubSystem(SDL_INIT_EVENTS); }

bool hal_input_poll(hal_input_event_t *event)
{
	SDL_Event sdl_event;
	while (SDL_PollEvent(&sdl_event))
	{
		if (sdl_event.type == SDL_QUIT)
		{
			exit(0);
		}
		if (sdl_event.type == SDL_KEYDOWN || sdl_event.type == SDL_KEYUP)
		{
			bool		  pressed = (sdl_event.type == SDL_KEYDOWN);
			input_event_t btn	  = INPUT_NONE;
			switch (sdl_event.key.keysym.sym)
			{
			case SDLK_LEFT:
				btn = INPUT_LEFT;
				break;
			case SDLK_RIGHT:
				btn = INPUT_RIGHT;
				break;
			case SDLK_UP:
				btn = INPUT_UP;
				break;
			case SDLK_DOWN:
				btn = INPUT_DOWN;
				break;
			case SDLK_RETURN:
				btn = INPUT_ENTER;
				break;
			case SDLK_ESCAPE:
				btn = INPUT_BACK;
				break;
			default:
				break;
			}
			if (btn != INPUT_NONE)
			{
				button_states[btn] = pressed;
				if (pressed && event)
				{
					event->type	   = INPUT_EVENT_CONTROL;
					event->control = btn;
					return true;
				}
			}
			else if (pressed && event)
			{
				SDL_Keycode sym = sdl_event.key.keysym.sym;
				char		ch	= 0;

				switch (sym)
				{
				case SDLK_KP_PLUS:
					ch = '+';
					break;
				case SDLK_KP_MINUS:
					ch = '-';
					break;
				case SDLK_KP_MULTIPLY:
					ch = '*';
					break;
				case SDLK_KP_DIVIDE:
					ch = '/';
					break;
				default:
				{
					bool shift = (sdl_event.key.keysym.mod & KMOD_SHIFT);

					if (sym >= SDLK_a && sym <= SDLK_z)
					{
						ch = (char) (sym);
						if (shift) ch -= 32; // a-z → A-Z
					}
					else if (sym >= SDLK_0 && sym <= SDLK_9)
					{
						if (shift)
						{
							// Shift+0..9 → )!@#$%^&*(
							static const char shifted_nums[] = {')', '!', '@', '#', '$', '%', '^', '&', '*', '('};
							ch								 = shifted_nums[sym - SDLK_0];
						}
						else
						{
							ch = '0' + (sym - SDLK_0);
						}
					}
					else
					{
						switch (sym)
						{
						case SDLK_MINUS:
							ch = shift ? '_' : '-';
							break;
						case SDLK_EQUALS:
							ch = shift ? '+' : '=';
							break;
						case SDLK_LEFTBRACKET:
							ch = shift ? '{' : '[';
							break;
						case SDLK_RIGHTBRACKET:
							ch = shift ? '}' : ']';
							break;
						case SDLK_BACKSLASH:
							ch = shift ? '|' : '\\';
							break;
						case SDLK_SEMICOLON:
							ch = shift ? ':' : ';';
							break;
						case SDLK_QUOTE:
							ch = shift ? '"' : '\'';
							break;
						case SDLK_COMMA:
							ch = shift ? '<' : ',';
							break;
						case SDLK_PERIOD:
							ch = shift ? '>' : '.';
							break;
						case SDLK_SLASH:
							ch = shift ? '?' : '/';
							break;
						case SDLK_BACKQUOTE:
							ch = shift ? '~' : '`';
							break;
						case SDLK_SPACE:
							ch = ' ';
							break;
						case SDLK_BACKSPACE:
							ch = '\b';
							break;
						default:
							break;
						}
					}
					break;
				}
				}

				if (ch)
				{
					event->type = INPUT_EVENT_KEY;
					event->key	= ch;
					return true;
				}
			}
		}
	}
	return false;
}

bool hal_input_is_pressed(input_event_t event)
{
	return (event > INPUT_NONE && event <= INPUT_BACK) && button_states[event];
}
