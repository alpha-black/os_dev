global loader
extern kmain                                                                ; extern C function
extern code
extern bss
extern end

section .data

MBOOT_PAGE_ALIGN        equ 1<<0
MBOOT_MEM_INFO          equ 1<<1

MBOOT_HEADER_MAGIC      equ 0x1BADB002
MBOOT_HEADER_FLAGS      equ (MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO)             ; multiboot flags
MBOOT_HEADER_CHECKSUM   equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)      ; All three sum up to 0

KERNEL_STACK_SIZE       equ 4096


section .bss
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE

section .text
bits 32
mboot:
    dd MBOOT_HEADER_MAGIC
    dd MBOOT_HEADER_FLAGS
    dd MBOOT_HEADER_CHECKSUM
    dd mboot

    dd code
    dd bss
    dd end
    dd loader

loader:                                                                     ; entry point, defined in the linker
    mov esp, kernel_stack + KERNEL_STACK_SIZE
    cli
    call kmain
    jmp $
