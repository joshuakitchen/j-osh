#include <drivers/tty.h>

/// <summary>
/// The Kernel Entry point as defined in the boot loader.
/// </summary>
void kernel_entry(void)
{
  tty_clear();
  print("Welcome to J-OSH\n");
  int i;
  for(i = 0; i < 50; i++)
    print("Test\n");
}
