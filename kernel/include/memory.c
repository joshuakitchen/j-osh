#include "memory.h"

// Allocate memory based on 4KB pages.
u32 memory_blocks[256];

void init_memory()
{
  int i;
  for(i = 0; i < RESERVED_KERNEL_CHUNKS; i++) {
    memory_blocks[i] = 0xFFFFFFFF;
  }
}

u32 kmalloc(u32 size, int align, u32* phys_addr)
{
  return 0;
}

void memcpy(char* src, char* dst, int len)
{
  int i;
  for(i = 0; i < len; i++)
    *(dst + i) = *(src + i);
}
