#include <stdint.h>
#include "../lib/vgaprint.h"
#include "../lib/gdt.h"
#include "../lib/idt.h"

void kernel_main(void) {
    clear_screen();
    put_string(0, 0, "Fire Glass Linux From Scratch", 0x0F);

    put_string(2, 0, "Initializing GDT...", 0x0E);
    gdt_init();
    put_string(3, 0, "GDT loaded.", 0x0A);

    put_string(4, 0, "Initializing IDT...", 0x0E);
    idt_init();
    put_string(5, 0, "IDT loaded.", 0x0A);

    /* trigger a divide-by-zero to test the IDT */
    put_string(6, 0, "Triggering int 0 (divide by zero)...", 0x0E);
    __asm__ volatile ("int $0");

    put_string(7, 0, "Should not reach here!", 0x0C);
    for (;;) __asm__ volatile ("hlt");
}