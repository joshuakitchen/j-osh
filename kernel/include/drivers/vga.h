#ifndef HGUARD_VGA
#define HGUARD_VGA

#define VIDEO_MEMORY (unsigned char*) 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

#endif
