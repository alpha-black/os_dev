global loader                                       ; Entery symbol for ELF

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
    mov eax, 0xCAFEBABE
    mov esp, kernel_stack + KERNEL_STACK_SIZE

extern kmain
.load_kernel:
    ;push dword 1
    ;push dword 1
    ;push dword 1
    call kmain
    ;mov eax, 0xCAFEBABE
    jmp .load_kernel
