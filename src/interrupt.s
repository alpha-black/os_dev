; Macro for defining all the interrupts. Taken from James Malloy
%macro ISR_NOERROR_CODE 1
    global isr%1
    isr%1:
        cli
        push byte 0
        push %1
        jmp isr_common_asm
%endmacro

%macro ISR_NOERROR_CODE 1
    global isr%1
    isr%1:
        cli
        push %1
        jmp isr_common_asm
%endmacro

ISR_NOERROR_CODE 0
ISR_NOERROR_CODE 1


global isr_common_asm
extern isr_handler

; From James Malloy kernel dev
isr_common_asm:
    pusha
    mov ax, ds              ; Lower 16-bits of eax = ds.
    push eax                ; save the data segment descriptor

    mov ax, 0x10            ; load the kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call isr_handler

    pop eax                 ; reload the original data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa                    ; Pops edi,esi,ebp...
    add esp, 8              ; Cleans up the pushed error code and pushed ISR number
    sti
    iret                    ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP
