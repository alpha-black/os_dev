#include "asm.h"
#include "common.h"

void framebuffer_move_cursor(unsigned short pos)
{
    outb(FB_TYPE_PORT, FB_TYPE_HIGHER_BITS);
    outb(FB_DATA_PORT, ((pos & 0xFF00) >> 8));
    outb(FB_TYPE_PORT, FB_TYPE_LOWER_BITS);
    outb(FB_DATA_PORT, (pos & 0x00FF));
}

void framebuffer_write_cell(unsigned int cell, char val, unsigned char foreground_c, unsigned char background_c)
{
    char * fb = (char *)0x00B8000;
    fb[cell*2] = val;
    fb[cell*2+1] = (((foreground_c & 0x0F) << 4) | (background_c & 0x0F));
}

int kprintf(const char * message, int pos)
{
    int i = 0;
    while(*(message+i) != '\0') {
        framebuffer_write_cell(i, message[i], 0x02, 0x08);
        i++;
    }
    framebuffer_move_cursor(pos+i);
    return pos+i;
}

int kmain(void)
{
    /* int fb_cursor_pos = */ kprintf("Welcome!", 0);
    serial_init();
    serial_write(SERIAL_COM1_BASE, 0x30);

    gdt_init();

    return 0xDEADBABA;
}
