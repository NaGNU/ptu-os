C=gcc
ASM=nasm
LD=ld

CFLAGS=-m64 -ffreestanding -nostdlib -Wall -Wextra -fno-builtin
ASMFLAGS=-f elf64
LDFLAGS=-m elf_x86_64 -T linker.ld

OBJS=kernel.o kernel_asm.o

all: kernel.bin

kernel.bin: $(OBJS)
	@echo "Build..."
	@$(LD) $(LDFLAGS) -o $@ $^

kernel.o: kernel.c
	@echo "Build..."
	$(C) $(CFLAGS) -c $< -o $@

kernel_asm.o: kernel.asm
	@echo "Build..."
	@$(ASM) $(ASMFLAGS) $< -o $@

clean:
	@echo "Build..."
	@rm -f *.o *.bin
