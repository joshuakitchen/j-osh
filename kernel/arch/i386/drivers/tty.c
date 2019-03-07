#include <drivers/io.h>
#include <drivers/tty.h>
#include <drivers/vga.h>
#include <memory.h>

int print_char(char, int, int, char);

void tty_clear()
{
  u32 size = MAX_COLS * MAX_ROWS;
  unsigned char* vmem = VIDEO_MEMORY;
  int i;

  for(i = 0; i < size; i++) {
    vmem[i*2] = ' ';
    vmem[i*2+1] = 0x0f;
  }
  set_cursor_position(0, 0);
}

int print_char(char c, int col, int row, char attr)
{
  unsigned char* vidmem = VIDEO_MEMORY;
  if (!attr) attr = 0x0f;

  if(col >= MAX_COLS || row >= MAX_ROWS) {
    vidmem[2 * (MAX_COLS) * (MAX_ROWS) - 2] = 'E';
    vidmem[2 * (MAX_COLS) * (MAX_ROWS) - 1] = 0xf4;
    return get_offset(col, row);
  }

  int offset;
  if(col >= 0 && row >= 0)
    offset = get_offset(col, row);
  else
    offset = get_cursor_offset();

  if (c == '\n') {
    row = get_offset_row(offset);
    offset = get_offset(0, row+1);
  } else {
    vidmem[offset] = c;
    vidmem[offset+1] = attr;
    offset += 2;
  }

  if(offset >= MAX_ROWS * MAX_COLS * 2) {
    int i;
    for(i = 1; i < MAX_ROWS; i++)
      memcpy(get_offset(0, i) + VIDEO_MEMORY,
             get_offset(0, i-1) + VIDEO_MEMORY,
             MAX_COLS * 2);

    char* last_line = get_offset(0, MAX_ROWS - 1) + VIDEO_MEMORY;
    for (i = 0; i < MAX_COLS * 2; i++) last_line[i] = 0;

    offset -= 2 * MAX_COLS;
  }
  set_cursor_offset(offset);
  return offset;
}

void print_at(char* message, int len, int col, int row)
{
  int offset;
  if (col >= 0 && row >= 0) {
    offset = get_offset(col, row);
  } else {
    offset = get_cursor_offset();
    row = get_offset_row(offset);
    col = get_offset_col(offset);
  }

  int i;
  for(i = 0; i < len; i++) {
    offset = print_char(message[i], col, row, 0x0f);
    row = get_offset_row(offset);
    col = get_offset_col(offset);
  }
}

void tty_print(char* message, int len)
{
  print_at(message, len, -1, -1);
}
