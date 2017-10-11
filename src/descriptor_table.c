#include "asm.h"
#include "common.h"

struct gdt_entry gdt_entries[5];
struct gdt gdt_ptr;
struct idt_entry idt_entries[256];
struct idt idt_ptr;

static void gdt_set_entry(struct gdt_entry * entry, unsigned int limit, unsigned int base,
                          unsigned char access, unsigned char granularity)
{
    entry->limit_low = limit & 0xFFFF;
    entry->base_low = base & 0xFFFF;
    entry->base_middle = (base >> 16) & 0xFF;
    entry->base_high = (base >> 24) & 0xFF;
    entry->access = access;
    entry->granularity = (limit >> 16) & 0x0F;
    entry->granularity |= granularity & 0xF0;
}

static void gdt_init()
{

    gdt_set_entry(&gdt_entries[0], 0, 0, 0, 0);                  /* Null segment */
    gdt_set_entry(&gdt_entries[1], 0xFFFFFF, 0, 0x9A, 0xCF);     /* Kernel code segment */
    gdt_set_entry(&gdt_entries[2], 0xFFFFFF, 0, 0x92, 0xCF);     /* Kernel data segment */
    gdt_set_entry(&gdt_entries[3], 0xFFFFFF, 0, 0xFA, 0xCF);     /* User mode code segment */
    gdt_set_entry(&gdt_entries[4], 0xFFFFFF, 0, 0xF2, 0xCF);     /* User mode data segment */

    gdt_ptr.base = (unsigned int)gdt_entries;
    gdt_ptr.limit = 8*5 - 1;                                     /* GDT entries are 8 bytes long */

    gdt_flush((unsigned int)&gdt_ptr);
}

static void idt_set_gate(struct idt_entry * entry, unsigned int offset, unsigned short selector,
                         unsigned char flag)
{
    entry->offset_low = offset & 0xFFFF;
    entry->offset_high = (offset >> 16) & 0xFFFF;
    entry->selector = selector;
    entry->unused = 0x00;
    entry->flags = flag;
}

static void idt_init()
{

    /* Code segment at 0x08, 0x8E (P=1, DPL=00b, S=0, type=1110b) */
    idt_set_gate(&idt_entries[0], (unsigned int)isr0, 0x08, 0x8E);

    idt_ptr.base = (unsigned int)idt_entries;
    idt_ptr.limit = 8*256 - 1;

    idt_flush((unsigned int)&idt_ptr);
}


void descriptor_tables_init()
{
    gdt_init();
    idt_init();
}
