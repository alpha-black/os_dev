global outb                                         ; Refernced from C

; data - unsigned char  [esp + ]
; port - unsigned short [esp + ]


outb:
    mov al, [esp + 8]
    mov dx, [esp + 4]
    out dx, al
    ret
