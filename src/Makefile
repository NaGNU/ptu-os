CC=ldc2
DFLAGS=-c kernel.d -betterC -O3

all:
	@echo "Build..."
	@$(CC) $(DFLAGS)
	@echo "LD Build..."
	@ld -T linker.ld -o kernel.elf kernel.o

grub_prepare:
	@echo "Grub preparing..."
	@mkdir -p grub/boot/grub
	@cp kernel.elf grub/boot/kernel
	@cp grub.cfg grub/boot/grub/grub.cfg
	@grub-mkrescue -o ptu.iso grub

qemu: all grub_prepare
	@echo "Starting qemu..."
	@qemu-system-x86_64 -cdrom ptu.iso

grub_mkfont:
	@echo "Make fonts for grub... (NaGNU)"
	@grub-mkfont -o unicode.pf2 -s 16 /usr/share/fonts/TTF/TerminusTTF-Bold-4.49.2.ttf
	@sudo mkdir -p /boot/grub/fonts
	@sudo mv unicode.pf2 /usr/share/grub/unicode.pf2

clean:
	@echo "Cleaning..."
	@rm -rf *.elf *.o 
