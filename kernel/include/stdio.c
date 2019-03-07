#include "stdio.h"
#include "drivers/tty.h"
#include "string.h"
#include <stdarg.h>

int printf(const char* format, ...)
{
  va_list parameters;
  va_start(parameters, format);

  int written = 0;

  while(*format != '\0') {

    if(format[0] != '%' || format[1] == '%') {
      if(format[0] == '%')
        format++;
      int amount = 1;

      while(format[amount] && format[amount] != '%')
        amount++;

      tty_print((char*)format, amount);
      format += amount;
      written += amount;
      continue;
    }

    const char* format_begun_at = format++;

    if(*format == 'c') {
      format++;
      char c = (char) va_arg(parameters, int);
      tty_print(c, sizeof(c));
      written++;
    } else if(*format == 's') {
      format++;
      const char* str = va_arg(parameters, const char*);
      int len = strlen(str);
      tty_print(str, len);
      written += len;
    } else if(*format == 'd') {
      format++;
      int i = va_arg(parameters, int);
      char s[21];
      int_to_ascii(i, s);
      int len = strlen(s);
      tty_print(s, len);
      written += len;
    }
  }
}
