#include "asm.h"
#include "common.h"

void interrupt_handler(struct interrupt_registers reg)
{
    kprintf("Received interrupt %d\n", reg.int_no);

    if ((reg.int_no >= 0x20) && (reg.int_no < 0x30)) {

        kprintf("Received IRQ\n");
        if (reg.int_no >= 0x28)
            outb(PIC_SLAVE_COMMAND_PORT, 0x20);
        outb(PIC_MASTER_COMMAND_PORT, 0x20);
    }
}
