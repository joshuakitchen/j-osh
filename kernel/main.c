#include <cpu/isr.h>
#include <drivers/tty.h>
#include <drivers/keyboard.h>
#include <memory.h>
#include <string.h>
#include <stdio.h>

static char key_buffer[20] = "";
static u8 modifier = 0;
const char prefix[3] = "$ ";

#define SC_MAX 57
#define VK_BACKSPACE 14
#define VK_ENTER 28
#define VK_LSHIFT 42
#define VK_RSHIFT 54
#define VK_CTRL 29
#define VK_ALT 56
#define MOD_LSHIFT 0x1
#define MOD_RSHIFT 0x2
const char sc_ascii[] = {
  '\0', '\0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\0',
  '\0', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\0',
  '\0', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '#',
  '\0', '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', '\0',
  '\0', '\0', ' '
};
const char sc_ascii_upper[] = {
  '\0', '\0', '!', '"', '\0', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\0',
  '\0', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\0',
  '\0', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '@', '~',
  '\0', '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', '\0',
  '\0', '\0', ' '
};

void handle_input(char* input)
{

}

void keyboard_handler(u8 scancode)
{
  u8 event = scancode & 0x80;
  u8 keycode = scancode & 0x7F;
  if(event == 0) {
    char c = ((modifier & 0x3) > 0) ? sc_ascii_upper[(int)keycode] : sc_ascii[(int)keycode];
    if(c != '\0') {
      if(strlen(&key_buffer) < 20) {
        append(&key_buffer, c);
        printf("%c", c);
      }
    } else if(keycode == VK_ENTER) {
      printf("\n");
      handle_input(&key_buffer);
      printf(&prefix);
      key_buffer[0] = '\0';
    } else if(keycode == VK_LSHIFT) {
      modifier |= MOD_LSHIFT;
    } else if(keycode == VK_RSHIFT) {
      modifier |= MOD_RSHIFT;
    } else if(keycode == VK_BACKSPACE) {
      int len = strlen(&key_buffer);
      if(len > 0) {
        key_buffer[len-1] = '\0';
        printf("\b");
      }
    }
  } else if(event == 0x80) {
    if(keycode == VK_LSHIFT) {
      modifier &= ~(MOD_LSHIFT);
    } else if(keycode == VK_RSHIFT) {
      modifier &= ~(MOD_RSHIFT);
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

  printf("Welcome to J-OSH\n\n");
  printf(&prefix);
  init_keyboard();
  set_keyboard_callback(*keyboard_handler);
}
