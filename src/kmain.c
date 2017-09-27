#include "io.h"

#define FB_TYPE_PORT                        0x3D4
#define FB_DATA_PORT                        0x3D5
#define FB_TYPE_HIGHER_BITS                 14
#define FB_TYPE_LOWER_BITS                  15

#define SERIAL_COM1_BASE                    0x3F8
#define SERIAL_DATA_PORT(base)              (base)
#define SERIAL_FIFO_COMMAND_PORT(base)      (base+2)
#define SERIAL_LINE_COMMAND_PORT(base)      (base+3)
#define SERIAL_MODEM_COMMAND_PORT(base)     (base+4)
#define SERIAL_LINE_STATUS_PORT(base)       (base+5)

void serial_configure_baud_rate(unsigned short com, unsigned short divisor)
{
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x80);                  // Enable DLAB
    outb(SERIAL_DATA_PORT(com), (divisor & 0x00FF));
    outb(SERIAL_DATA_PORT(com)+1, (divisor & 0xFF00) >> 8);
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x00);                  // Disable DLAB
}

void serial_configure_buffer(unsigned short com, unsigned char val)
{
    outb(SERIAL_FIFO_COMMAND_PORT(com), val);
}

void serial_configure_modem(unsigned short com, unsigned char val)
{
    outb(SERIAL_LINE_COMMAND_PORT(com), val);
}

int serial_check_buffer(unsigned short com)
{
    return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

void serial_write(unsigned short com, unsigned char val)
{
    outb(SERIAL_DATA_PORT(com), val);
}

void serial_init()
{
    outb(SERIAL_COM1_BASE+1, 0x00);                         //Disable interrupts
    serial_configure_baud_rate(SERIAL_COM1_BASE, 0x0003);
    serial_configure_modem(SERIAL_COM1_BASE, 0x03);
    serial_configure_buffer(SERIAL_COM1_BASE, 0xC7);
    outb(SERIAL_COM1_BASE+4, 0x0B);
}

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

int kmain(int arg1)
{
    int fb_cursor_pos = kprintf("Welcome!", 0);

    while(serial_check_buffer(SERIAL_COM1_BASE) == 0);
    serial_write(SERIAL_COM1_BASE, 0x30);

    return arg1+0x1+fb_cursor_pos;
}
