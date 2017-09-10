global loader                       ; Entery symbol for ELF

MAGIC_NUMBER equ 0x1BADB002
FLAGS        equ 0x0                ; multiboot flags
CHECKSUM     equ -MAGIC_NUMBER      ; All three sum up to 0

section .text:
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

loader:                             ; entry point, defined in the linker
    mov eax, 0xCAFEBABE

.loop:
    jmp .loop
