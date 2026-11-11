#include <stdint.h>
#include "../lib/vgaprint.h"

void kernel_main(void) {
    clear_screen();
    put_string(0, 0, "Fire Glass Linux From Scratch", 0x0F);
    put_string(2, 0, "VGA text mode works!", 0x0A);
    for (;;) __asm__ volatile ("hlt");
}