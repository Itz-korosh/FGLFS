#include <stdint.h>
#include "../lib/vgaprint.h"

/* Matches the layout pushed by isr_common */
struct regs {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
};

void isr_handler(struct regs *r) {
    put_string(7, 0, "Exception caught!", 0x0C);   /* light red */

    char buf[16];
    buf[0] = '0' + (r->int_no / 10);
    buf[1] = '0' + (r->int_no % 10);
    buf[2] = '\0';
    put_string(8, 0, "Parse no: ", 0x0F);
    put_string(8, 10, buf, 0x0F);

    for (;;) __asm__ volatile ("hlt");
}