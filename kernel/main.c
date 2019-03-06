#include <cpu/isr.h>
#include <drivers/tty.h>
#include <drivers/keyboard.h>
#include <memory.h>
#include <string.h>

static char key_buffer[20] = "\0";

#define SC_MAX 57
const char sc_ascii[] = {
  '?', '?', '1', '2', '3', '4', '5', '6',
  '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
  'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G',
  'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
  'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '
};

void keyboard_handler(u8 scancode)
{
  u8 modifier = scancode & 0x80;
  u8 keycode = scancode & 0x7F;
  if(modifier == 0) {
    char c = sc_ascii[(int)keycode];
    if(c != '?') {
      char s[2] = {c, '\0'};
      print(s);
    }
  }
}

/// <summary>
/// The Kernel Entry point as defined in the boot loader.
/// </summary>
void kernel_entry(void)
{
  isr_install();
  asm volatile ("sti");

  tty_clear();
  print("\n");
  print("Welcome to J-OSH\n");
  init_keyboard();
  set_keyboard_callback(*keyboard_handler);
}
