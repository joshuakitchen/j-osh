#ifndef HGUARD_MEMORY
#define HGUARD_MEMORY

#include "types.h"

typedef struct pmemory_region {
  u32 baseL;
  u32 baseH;
  u32 lengthL;
  u32 lengthH;
  u32 type;
  u32 acpi;
} pmemory_region_t;

#define UPPER_LOWER_MEMORY 0x9FFFF
#define RESERVED_KERNEL_CHUNKS 20

/// <summary>
/// Reserves some memory for the initial kernel.
/// </summary>
void init_memory();

/// <summary>
/// Allocates Physical memory by checking the heap.
/// </summary>
u32 kmalloc(u32 size, int align, u32 *phys_addr);

/// <summary>
/// Copies memory from one location to another.
/// </summary>
void memcpy(char* src, char* dest, int len);

#endif
