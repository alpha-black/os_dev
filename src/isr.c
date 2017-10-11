#include "common.h"

void isr_handler(struct isr_registers reg)
{
    kprintf("Recvd int",reg.err_code);
    kprintf("Recvd int", 0);
}
