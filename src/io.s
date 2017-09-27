global outb                                         ; Refernced from C
global inb

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

