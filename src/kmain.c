#include "asm.h"
#include "common.h"

int kmain(void)
{
    descriptor_tables_init();

    kprintf("%dWelcome!\n", 1);

    /* serial_init();
    serial_write(SERIAL_COM1_BASE, 0x30);

    trigger_int(); */

    return 0xDEADBABA;
}
