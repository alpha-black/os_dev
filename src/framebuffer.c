#include <stdarg.h>
#include "asm.h"
#include "common.h"

static void framebuffer_move_cursor(unsigned short pos)
{
    outb(FB_TYPE_PORT, FB_TYPE_HIGHER_BITS);
    outb(FB_DATA_PORT, ((pos & 0xFF00) >> 8));
    outb(FB_TYPE_PORT, FB_TYPE_LOWER_BITS);
    outb(FB_DATA_PORT, (pos & 0x00FF));
}

static void framebuffer_write_cell(unsigned int cell, char val, unsigned char foreground_c,
                                   unsigned char background_c)
{
    char * fb = (char *)0x00B8000;
    fb[cell*2] = val;
    fb[cell*2+1] = (((foreground_c & 0x0F) << 4) | (background_c & 0x0F));
}

static unsigned int _kprintf_int(int val, unsigned int pos)
{
    if (val > 9)
        pos = _kprintf_int(val/10, pos);

    char val_ascii = '0'+val%10;
    framebuffer_write_cell(pos, val_ascii, 0x00, 0x0F);
    return pos+1;
}

void clear_screen()
{
    for (int i = 0; i < 80*25; ++i) {
        framebuffer_write_cell(i, 0, 0, 0);
    }
}

void kprintf(const char * message, ...)
{
    static unsigned int pos = 0;
    va_list args;
    int ival, i = 0;

    if (pos == 0) clear_screen();

    va_start(args, message);

    while(*(message+i) != '\0') {
        if (*(message+i) == '\n') {
            pos += (80 - pos%80 - 1);
        }
        if (*(message+i) == '%') {
            i++;
            switch(*(message+i)) {
                case 'd':
                    ival = va_arg(args, int);
                    pos += _kprintf_int(ival, pos);
                    i++;
                    break;
                default:
                    goto EXIT;
            }
        }
        framebuffer_write_cell(pos, message[i], 0x00, 0x0F);
        i++; pos++;
    }
EXIT:
    framebuffer_move_cursor(pos+i);
}
