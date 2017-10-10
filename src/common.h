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
    unsigned char   access;              // Access flags, determine what ring this segment can be used in.
    unsigned char   granularity;
    unsigned char   base_high;           // The last 8 bits of the base.
}__attribute__((packed));


void gdt_init();

#endif /* __COMMON_H__ */
