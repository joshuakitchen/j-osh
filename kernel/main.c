#include <cpu/isr.h>
#include <drivers/tty.h>
#include <drivers/keyboard.h>
#include <memory.h>
#include <string.h>
#include <stdio.h>

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
      printf(s);
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
  init_memory();

  tty_clear();
  pmemory_region_t* memory_regions = (pmemory_region_t*) 0x8004;
  int* count = (int*) 0x8000;

  int i;
  char s[32];
  for(i = 0; i < *count; i++) {
    if(memory_regions[i].type != 1)
      continue;
    printf("\n\nDiscovered memory region: \n");
    printf("\nStarts at: %d, %d", memory_regions[i].baseL, memory_regions[i].baseH);
    printf("\nWith length of: %d, %d", memory_regions[i].lengthL, memory_regions[i].lengthH);
  }

  printf("\n\n\n");
  printf("Welcome to J-OSH\n");
  printf("Test\n");
  init_keyboard();
  set_keyboard_callback(*keyboard_handler);
}
