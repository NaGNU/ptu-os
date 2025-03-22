C = gcc
ASM = nasm
LD = ld

CFLAGS = -m32 -ffreestanding -nostdlib -Wall -Wextra
ASMFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T linker.ld

OBJS = kernel.o kernel_asm.o

all: kernel.bin

kernel.bin: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^  

kernel.o: kernel.c
	$(C) $(CFLAGS) -c $< -o $@  

kernel_asm.o: kernel.asm
	$(ASM) $(ASMFLAGS) $< -o $@  

clean:
	rm -f *.o *.bin
