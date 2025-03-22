ENTRY(_start)

SECTIONS {
    . = 1M;  

    .text : {
        *(.multiboot)
        *(.text)
    }

    .bss : {
        *(.bss)
    }

    .rodata : {
        *(.rodata)
    }

    .data : {
        *(.data)
    }
}
