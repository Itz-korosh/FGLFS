#include <stdint.h>
#include "../lib/vgaprint.h"
#include "../lib/pic.h"
#include "../lib/keyboard.h"

struct regs {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
};

void isr_handler(struct regs *r) {
    /* Hardware Interrupts (IRQs) are mapped to 32-47 */
    if (r->int_no >= 32 && r->int_no <= 47) {
        if (r->int_no == 33) {
            keyboard_handler(); /* Handle the keyboard */
        }
        
        pic_acknowledge(r->int_no); /* Tell the PIC we are done */
        return; /* MUST RETURN HERE! Otherwise it falls through to the crash screen */
    }

    /* CPU Exceptions (0-31) */
    put_string(12, 0, "Exception caught!", 0x0C);

    char buf[16];
    buf[0] = '0' + (r->int_no / 10);
    buf[1] = '0' + (r->int_no % 10);
    buf[2] = '\0';
    put_string(13, 0, "Int no: ", 0x0F);
    put_string(13, 8, buf, 0x0F);

    for (;;) __asm__ volatile ("hlt");
}