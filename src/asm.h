#ifndef _INCLUDE_ASM_H_
#define _INCLUDE_ASM_H_

/****************************************************
 *  Extern functions implemented in asm.s
 *
 ****************************************************/
extern void outb(unsigned short port, unsigned char data);
extern unsigned char inb(unsigned short port);
extern void gdt_flush(unsigned int);
extern void idt_flush(unsigned int);

extern void isr0();

#endif /* _INCLUDE_ASM_H_ */
