CC      = i686-elf-gcc
AS      = i686-elf-as
LD      = i686-elf-ld
CFLAGS  = -ffreestanding -nostdlib -O2 -Wall -Wextra
LDFLAGS = -T linker.ld

OBJS = bin/boot.o bin/kernel.o bin/VGAPrint.o bin/gdt.o \
       bin/idt.o bin/idt_load.o bin/isr.o bin/isr_stubs.o

all: bin/fglfs.bin

bin:
	mkdir -p bin

bin/boot.o: boot/i386/boot.S | bin
	$(AS) $< -o $@

bin/kernel.o: src/kernel.c lib/vgaprint.h lib/gdt.h lib/idt.h | bin
	$(CC) $(CFLAGS) -c $< -o $@

bin/VGAPrint.o: lib/VGAPrint.c lib/vgaprint.h | bin
	$(CC) $(CFLAGS) -c $< -o $@

bin/gdt.o: lib/gdt.c lib/gdt.h | bin
	$(CC) $(CFLAGS) -c $< -o $@

bin/idt.o: lib/idt.c lib/idt.h lib/vgaprint.h | bin
	$(CC) $(CFLAGS) -c $< -o $@

bin/idt_load.o: boot/i386/idt_load.S | bin
	$(AS) $< -o $@

bin/isr.o: lib/isr.c lib/vgaprint.h | bin
	$(CC) $(CFLAGS) -c $< -o $@

bin/isr_stubs.o: boot/i386/isr.S | bin
	$(AS) $< -o $@

bin/fglfs.bin: $(OBJS) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

run: bin/fglfs.bin
	qemu-system-i386 -kernel bin/fglfs.bin

clean:
	rm -f bin/*.o bin/*.bin

.PHONY: all run clean