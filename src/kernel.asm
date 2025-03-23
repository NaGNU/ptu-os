section .multiboot
align 4

; Multiboot 1 header
multiboot_header:
    dd 0x1BADB002              ; Magic number (Multiboot 1)
    dd 0x00000003              ; Flags (align modules on page boundaries + provide memory map)
    dd -(0x1BADB002 + 0x00000003) ; Checksum

section .text
bits 64                       
global _start

_start:
    cli                       
    mov rsp, stack_top        
    ; Вызов функции на C
    extern kernel_main
    call kernel_main

    ; Бесконечный цикл (на случай, если kernel_main вернётся)
    hlt
    jmp $

section .bss
align 16
stack_bottom:
    resb 16384                
stack_top:

.loop:
    in al, 0x64
    test al, 1
    jz .loop
    in al, 0x60
    jmp .loop
