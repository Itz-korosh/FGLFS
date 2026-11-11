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
    if (r->int_no >= 32 && r->int_no <= 47) {
        
        /* Let's prove we made it here! */
        put_string(14, 0, "IRQ!", 0x0E);

        if (r->int_no == 33) {
            keyboard_handler(); 
        }
        
        pic_acknowledge(r->int_no); 
        return; 
    }

    put_string(12, 0, "Exception caught!", 0x0C);

    char buf[16];
    buf[0] = '0' + (r->int_no / 10);
    buf[1] = '0' + (r->int_no % 10);
    buf[2] = '\0';
    put_string(13, 0, "Int no: ", 0x0F);
    put_string(13, 8, buf, 0x0F);

    for (;;) __asm__ volatile ("hlt");
}