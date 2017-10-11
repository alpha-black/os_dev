#ifndef _INCLUDE_ASM_H_
#define _INCLUDE_ASM_H_

/****************************************************
 *  Extern functions implemented in asm.s
 *
 ****************************************************/
/****************************************************
 *  send to I/O port using out in asm
 *
 ****************************************************/
extern void outb(unsigned short port, unsigned char data);
/****************************************************
 *  read from I/O port using in in asm
 *
 ****************************************************/
extern unsigned char inb(unsigned short port);
/****************************************************
 *  Inform where to find the GDT
 *
 ****************************************************/
extern void gdt_flush(unsigned int);
/****************************************************
 *  Inform where to find the IDT
 *
 ****************************************************/
extern void idt_flush(unsigned int);
/****************************************************
 *  ISR definitions defined in asm
 *
 ****************************************************/
extern void isr0();
/****************************************************
 *  Trigger an interrupt, for testing
 *
 ****************************************************/
extern void trigger_int();

#endif /* _INCLUDE_ASM_H_ */
