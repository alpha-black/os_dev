global outb                                         ; Refernced from C
global inb
global gdt_flush
global idt_flush

global trigger_int

; data - unsigned char  [esp + ]
; port - unsigned short [esp + ]

outb:
    mov al, [esp + 8]
    mov dx, [esp + 4]
    out dx, al
    ret


inb:
    mov dx, [esp + 4]
    in al, dx
    ret


gdt_flush:
    mov eax, [esp + 4]
    lgdt [eax]                                    ; load GDT
    mov ax, 0x10
    mov ds, ax                                  ; GDT entries are 8 bytes. Kernel data starts at
                                                ; 16 bytes = 0x10
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp 0x08:.flush                             ; Far jump for code segment. It is at 8 bytes
.flush:
    ret


idt_flush:
    mov eax, [esp + 4]
    lidt [eax]
    ret


trigger_int:
    int 0x0
    ret
