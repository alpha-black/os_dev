#ifndef __COMMON_H__
#define __COMMON_H__

/****************************************************
 *  Frame Buffer
 *
 ****************************************************/
#define FB_TYPE_PORT                        0x3D4
#define FB_DATA_PORT                        0x3D5
#define FB_TYPE_HIGHER_BITS                 14
#define FB_TYPE_LOWER_BITS                  15


int kprintf(const char * message, int pos);

/****************************************************
 *  Serial Port
 *
 ****************************************************/
#define SERIAL_COM1_BASE                    0x3F8
#define SERIAL_DATA_PORT(base)              (base)
#define SERIAL_FIFO_COMMAND_PORT(base)      (base+2)
#define SERIAL_LINE_COMMAND_PORT(base)      (base+3)
#define SERIAL_MODEM_COMMAND_PORT(base)     (base+4)
#define SERIAL_LINE_STATUS_PORT(base)       (base+5)

void serial_write(unsigned short com, unsigned char val);
void serial_init();

/****************************************************
 *  GDT
 *
 ****************************************************/

struct gdt {
    unsigned short  limit;
    unsigned int    base;
}__attribute__((packed));

/* From James Malloy kernel development */
struct gdt_entry {
    unsigned short  limit_low;           // The lower 16 bits of the limit.
    unsigned short  base_low;            // The lower 16 bits of the base.
    unsigned char   base_middle;         // The next 8 bits of the base.
    unsigned char   access;              // Access flags, privilage
    unsigned char   granularity;
    unsigned char   base_high;           // The last 8 bits of the base.
}__attribute__((packed));


/****************************************************
 *  IDT
 *  http://wiki.osdev.org/Interrupt_Descriptor_Table
 ****************************************************/
struct idt {
    unsigned short  limit;
    unsigned int    base;
}__attribute__((packed));


struct idt_entry {
    unsigned short  offset_low;         // The lower 16 bits of the GDT selector.
    unsigned short  selector;           // Kernel segment selector in GDT.
    unsigned char   unused;             // Unused. Set to 0.
    unsigned char   flags;              // Type and attribute. Privilage set here
    unsigned short  offset_high;        // The upper 16 bits of GDT selector.
}__attribute__((packed));


/****************************************************
 *  Descriptor Table init
 *
 ****************************************************/
void descriptor_tables_init();

/****************************************************
 *  ISR
 *  From James Malloy
 ****************************************************/
struct isr_registers {
    unsigned int ds;                                        /* Data segment selector */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;    /* Other registers. */
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;              /* Pushed by the processor. */
}__attribute__((packed));

void isr_handler(struct isr_registers reg);

#endif /* __COMMON_H__ */
