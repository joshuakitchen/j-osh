#ifndef HGUARD_KEYBOARD
#define HGUARD_KEYBOARD

#include "../types.h"

typedef void (*keyboard_handler_t)(u8 scancode);

void init_keyboard();
void set_keyboard_callback(keyboard_handler_t);

#endif
