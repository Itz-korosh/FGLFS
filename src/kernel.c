#include <stdint.h>
#include "../lib/vgaprint.h"
#include "../lib/gdt.h"
#include "../lib/idt.h"
#include "../lib/pic.h"
#include "../lib/keyboard.h"

void kernel_main(void) {
    clear_screen();
    put_string(0, 0, "Fire Glass Linux From Scratch", 0x0F);

    /* 1. Load GDT */
    gdt_init();

    /* 2. Load IDT */
    idt_init();

    /* 3. Remap the PIC so hardware interrupts don't collide with exceptions */
    pic_remap();

    /* 4. Initialize Keyboard */
    keyboard_init();

    put_string(2, 0, "System ready. Type something!", 0x0A);

    /* 5. Enable hardware interrupts! */
    __asm__ volatile ("sti");

    /* 6. Halt loop: wait for the next interrupt */
    for (;;) {
        __asm__ volatile ("hlt");
    }
}