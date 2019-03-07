#ifndef HGUARD_TTY
#define HGUARD_TTY

#include "vga.h"

void tty_print(char* message, int);
void print_at(char* message, int, int, int);
void tty_clear();

#endif
