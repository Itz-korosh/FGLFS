CC      = i686-elf-gcc
AS      = i686-elf-as
LD      = i686-elf-ld
CFLAGS  = -ffreestanding -nostdlib -O2 -Wall -Wextra
LDFLAGS = -T linker.ld

OBJS = bin/boot.o bin/kernel.o bin/VGAPrint.o

all: bin/fglfs.bin

bin:
	mkdir -p bin

bin/boot.o: boot/i386/boot.S | bin
	$(AS) $< -o $@

bin/kernel.o: src/kernel.c lib/vgaprint.h | bin
	$(CC) $(CFLAGS) -c $< -o $@

bin/VGAPrint.o: lib/VGAPrint.c lib/vgaprint.h | bin
	$(CC) $(CFLAGS) -c $< -o $@

bin/fglfs.bin: $(OBJS) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

run: bin/fglfs.bin
	qemu-system-i386 -kernel bin/fglfs.bin

clean:
	rm -f bin/*.o bin/*.bin

.PHONY: all run clean