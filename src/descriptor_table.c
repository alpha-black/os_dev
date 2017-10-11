#include "asm.h"
#include "common.h"

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
    struct gdt_entry gdt_entries[5];
    struct gdt gdt_ptr;

    gdt_set_entry(&gdt_entries[0], 0, 0, 0, 0);                  /* Null segment */
    gdt_set_entry(&gdt_entries[1], 0xFFFFFF, 0, 0x9A, 0xCF);     /* Kernel code segment */
    gdt_set_entry(&gdt_entries[2], 0xFFFFFF, 0, 0x92, 0xCF);     /* Kernel data segment */
    gdt_set_entry(&gdt_entries[3], 0xFFFFFF, 0, 0xFA, 0xCF);     /* User mode code segment */
    gdt_set_entry(&gdt_entries[4], 0xFFFFFF, 0, 0xF2, 0xCF);     /* User mode data segment */

    gdt_ptr.base = (unsigned int)gdt_entries;
    gdt_ptr.limit = 8*5 - 1;                                     /* GDT entries are 8 bytes long */

    gdt_flush((unsigned int)&gdt_ptr);
}

static void idt_init()
{

}


void descriptor_tables_init()
{
    gdt_init();

    idt_init();
}
