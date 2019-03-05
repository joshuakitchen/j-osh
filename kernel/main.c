

void kernel_entry(void)
{
    char* video_memory = (char*) 0xb8000;
    *video_memory = 'X';
    video_memory[1] = 0x0f;
}
