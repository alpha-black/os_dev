#include "io.h"

#define FB_TYPE_PORT            0x3D4
#define FB_DATA_PORT            0x3D5
#define FB_TYPE_HIGHER_BITS     14
#define FB_TYPE_LOWER_BITS      15

void framebuffer_move_cursor(unsigned short pos)
{
    outb(FB_TYPE_PORT, FB_TYPE_HIGHER_BITS);
    outb(FB_DATA_PORT, ((pos & 0xFF00) >> 8));
    outb(FB_TYPE_PORT, FB_TYPE_LOWER_BITS);
    outb(FB_DATA_PORT, (pos & 0x00FF));
}

void framebuffer_write_cell(unsigned int cell, char val, unsigned char foreground_c, unsigned char background_c)
{
    char *fb = (char *)0x00B8000;
    fb[cell*16] = val;
    fb[cell*16+1] = (((foreground_c & 0x0F) << 4) | (background_c & 0x0F));
    framebuffer_move_cursor(79);
}

int kmain(int arg1)
{
    framebuffer_write_cell(79, 'A', 0x02, 0x08);
    return arg1+0x1;
}
