#ifndef GDT_H
#define GDT_H

#include <stdint.h>

/* One GDT entry (descriptor) — exactly 8 bytes */
struct gdt_entry {
    uint16_t limit_low;     /* limit bits 0-15 */
    uint16_t base_low;      /* base bits 0-15 */
    uint8_t  base_middle;   /* base bits 16-23 */
    uint8_t  access;        /* access flags */
    uint8_t  granularity;   /* limit bits 16-19 + flags */
    uint8_t  base_high;     /* base bits 24-31 */
} __attribute__((packed));

/* Pointer passed to lgdt — exactly 6 bytes */
struct gdt_ptr {
    uint16_t limit;         /* size of GDT minus 1 */
    uint32_t base;          /* address of GDT array */
} __attribute__((packed));

void gdt_init(void);

#endif