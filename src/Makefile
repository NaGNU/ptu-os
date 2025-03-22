C=tcc
ASM=nasm
LD=ld

CFLAGS=-m32 -ffreestanding -nostdlib -Wall -Wextra
ASMFLAGS=-f elf32
LDFLAGS=-m elf_i386 -T linker.ld

OBJS=kernel.o kernel_asm.o

all: kernel.bin

kernel.bin: $(OBJS)
	@echo "LD Build..."
	@$(LD) $(LDFLAGS) -o $@ $^  

kernel.o: kernel.c
	@echo "Kernel Build..."
	@$(C) $(CFLAGS) -c $< -o $@  

kernel_asm.o: kernel.asm
	@echo "Asm Build..."
	@$(ASM) $(ASMFLAGS) $< -o $@  

clean:
	@echo "Clean..."
	@rm -f *.o *.bin
