global loader                                       ; Entery symbol for ELF
extern kmain                                        ; extern C function

section .data

MAGIC_NUMBER        equ 0x1BADB002
FLAGS               equ 0x0                         ; multiboot flags
CHECKSUM            equ -MAGIC_NUMBER               ; All three sum up to 0
KERNEL_STACK_SIZE   equ 4096

section .bss
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE

section .text
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

loader:                                             ; entry point, defined in the linker
    ;mov eax, 0xCAFEBABE
    mov esp, kernel_stack + KERNEL_STACK_SIZE
    mov ebx, 1
    push ebx
    call kmain
    jmp $
