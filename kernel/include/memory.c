#include "memory.h"

void memcpy(char* src, char* dst, int len)
{
  int i;
  for(i = 0; i < len; i++)
    *(dst + i) = *(src + i);
}
