#include <drivers/keyboard.h>
#include <drivers/io.h>
#include <cpu/isr.h>

keyboard_handler_t g_Keyboard_callback = 0;

static void keyboard_callback(registers_t regs)
{
  u8 scancode = port_byte_in(0x60);
  if(keyboard_callback != 0) {
    g_Keyboard_callback(scancode);
  }
}

void init_keyboard()
{
  register_interrupt_handler(IRQ1, keyboard_callback);
}

void set_keyboard_callback(keyboard_handler_t callback)
{
  g_Keyboard_callback = callback;
}
