CC = gcc
ASM = nasm
LD = ld

CFLAGS = -m64 -ffreestanding -nostdlib -Wall -Wextra -fno-builtin
ASMFLAGS = -f elf64
LDFLAGS = -m elf_x86_64 -T linker.ld

OBJS = kernel.o kernel_asm.o

all: kernel.bin

kernel.bin: $(OBJS)
	@$(LD) $(LDFLAGS) -o $@ $^

kernel.o: kernel.c
	@$(CC) $(CFLAGS) -c $< -o $@

kernel_asm.o: kernel.asm
	@$(ASM) $(ASMFLAGS) $< -o $@

clean:
	@rm -f *.o *.bin

qemu: all
	@echo "Starting qemu"
	@qemu-system-x86_64 -kernel kernel.bin
