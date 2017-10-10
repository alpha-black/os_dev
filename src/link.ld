ENTRY(loader)

SECTIONS {
    .text 0x100000 :                            /* Start at 1 MB */
    {
        code = .; _code = .; __code = .;
        *(.text)
        . = ALIGN(0x1000);                        /* Align at 4096 */
    }

    .data :
    {
        data = .; _data = .; __data = .;
        *(.data)
        *(.rodata)
        . = ALIGN (0x1000);
    }

    .bss :
    {
        bss = .; _bss = .; __bss = .;
        *(COMMON)
        *(.bss)
        . = ALIGN (0x1000);
    }

    end = .; _end = .; __end = .;
}
