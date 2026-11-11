#ifndef IDT_H
#define IDT_H

#include <stdint.h>

struct idt_entry {
    uint16_t base_low;      /* handler address bits 0-15 */
    uint16_t selector;      /* code segment selector (0x08) */
    uint8_t  always_zero;   /* must be 0 */
    uint8_t  flags;         /* type + privilege */
    uint16_t base_high;     /* handler address bits 16-31 */
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;         /* size of IDT minus 1 */
    uint32_t base;          /* address of IDT array */
} __attribute__((packed));

void idt_init(void);
void idt_set_gate(int n, uint32_t handler, uint16_t selector, uint8_t flags);

#endif