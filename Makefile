C=gcc
CFLAGS=-o main

all:
	@echo "Build..."
	@$(C) $(CFLAGS) src/

qemu: all
	@echo "Starting qemu..."
	@qemu-system-x86_64 -kernel

clean:
	@echo "Cleaning..."
	@rm src/main
