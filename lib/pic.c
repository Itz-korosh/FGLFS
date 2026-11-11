#include "pic.h"
#include "io.h"

#define PIC1_COMMAND 0x20
#define PIC1_DATA    0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA    0xA1
#define PIC_EOI      0x20

#define ICW1_ICW4    0x01
#define ICW1_INIT    0x10
#define ICW4_8086    0x01

void pic_remap(void) {
    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4); io_wait();
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4); io_wait();
    
    /* Map Master PIC to 32-39, Slave PIC to 40-47 */
    outb(PIC1_DATA, 0x20); io_wait(); 
    outb(PIC2_DATA, 0x28); io_wait(); 
    
    /* Tell Master about Slave, and Slave its identity */
    outb(PIC1_DATA, 0x04); io_wait(); 
    outb(PIC2_DATA, 0x02); io_wait(); 
    
    outb(PIC1_DATA, ICW4_8086); io_wait();
    outb(PIC2_DATA, ICW4_8086); io_wait();
    
    /* Unmask IRQ0 (Timer) and IRQ1 (Keyboard) */
    outb(PIC1_DATA, 0xFC); 
    outb(PIC2_DATA, 0xFF);
}

void pic_acknowledge(unsigned int interrupt) {
    if (interrupt < 0x20 || interrupt > 0x2F) return;
    
    if (interrupt > 0x27) {
        outb(PIC2_COMMAND, PIC_EOI);
    }
    outb(PIC1_COMMAND, PIC_EOI);
}