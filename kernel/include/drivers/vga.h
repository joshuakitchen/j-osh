#ifndef HGUARD_VGA
#define HGUARD_VGA

#define VIDEO_MEMORY (unsigned char*) 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

int get_offset(int, int);
int get_offset_col(int);
int get_offset_row(int);
int get_cursor_offset();
void set_cursor_offset(int);
void set_cursor_position(int, int);
void get_cursor_position(int*, int*);

#endif
