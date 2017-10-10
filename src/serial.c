#include "common.h"
#include "asm.h"

static void serial_configure_baud_rate(unsigned short com, unsigned short divisor)
{
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x80);                  // Enable DLAB
    outb(SERIAL_DATA_PORT(com), (divisor & 0x00FF));
    outb(SERIAL_DATA_PORT(com)+1, (divisor & 0xFF00) >> 8);
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x00);                  // Disable DLAB
}

static void serial_configure_buffer(unsigned short com, unsigned char val)
{
    outb(SERIAL_FIFO_COMMAND_PORT(com), val);
}

static void serial_configure_modem(unsigned short com, unsigned char val)
{
    outb(SERIAL_LINE_COMMAND_PORT(com), val);
}

static int serial_check_buffer(unsigned short com)
{
    return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

void serial_write(unsigned short com, unsigned char val)
{
    /* Check buffer before wrting */
    while(serial_check_buffer(SERIAL_COM1_BASE) == 0);
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
