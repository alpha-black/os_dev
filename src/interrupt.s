; Macro for defining all the interrupts.
%macro ISR_NOERROR_CODE 1
    global isr%1
    isr%1:
        cli
        push byte 0
        push %1
        jmp interrupt_common_asm
%endmacro

%macro ISR_NOERROR_CODE 1
    global isr%1
    isr%1:
        cli
        push %1
        jmp interrupt_common_asm
%endmacro

; Macro for IRQ re-mapped interrupt number
%macro IRQ 2
    global irq%1
    irq%1:
        cli
        push byte 0
        push %2
        jmp interrupt_common_asm
%endmacro


ISR_NOERROR_CODE 0
ISR_NOERROR_CODE 1

IRQ 0, 32
IRQ 1, 33
IRQ 2, 34

extern interrupt_handler

; From James Malloy kernel dev
interrupt_common_asm:
    pusha
    mov ax, ds              ; Lower 16-bits of eax = ds.
    push eax                ; save the data segment descriptor

    mov ax, 0x10            ; load the kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call interrupt_handler

    pop eax                 ; reload the original data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa                    ; Pops edi,esi,ebp...
    add esp, 8              ; Cleans up the pushed error code and pushed ISR number
    sti
    iret
