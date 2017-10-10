#ifndef _INCLUDE_ASM_H_
#define _INCLUDE_ASM_H_

void outb(unsigned short port, unsigned char data);
unsigned char inb(unsigned short port);
void gdt_flush(unsigned int);

#endif /* _INCLUDE_ASM_H_ */
