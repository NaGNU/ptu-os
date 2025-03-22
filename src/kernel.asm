section .multiboot
align 4

; Multiboot 1 header
multiboot_header:
    dd 0x1BADB002              ; Magic number (Multiboot 1)
    dd 0x00000003               ; Flags (align modules on page boundaries + provide memory map)
    dd -(0x1BADB002 + 0x00000003) ; Checksum

section .text
global _start

_start:
    cli                         
    mov esp, stack_top          

    extern kernel_main
    call kernel_main

    hlt
    jmp $

section .bss
align 16
stack_bottom:
    resb 16384                  
stack_top:
