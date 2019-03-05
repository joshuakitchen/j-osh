#ifndef HGUARD_TTY
#define HGUARD_TTY

#include "vga.h"

void print(char* message);
void print_at(char* message, int, int);
void tty_clear();

#endif
