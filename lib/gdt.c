#include "gdt.h"

/* The GDT itself — 3 entries: null, kernel code, kernel data */
static struct gdt_entry gdt[3];
static struct gdt_ptr   gp;

/* Set one GDT entry */
static void gdt_set_entry(int i, uint32_t base, uint32_t limit,
                          uint8_t access, uint8_t granularity) {
    gdt[i].base_low    = (uint16_t)(base & 0xFFFF);
    gdt[i].base_middle = (uint8_t)((base >> 16) & 0xFF);
    gdt[i].base_high   = (uint8_t)((base >> 24) & 0xFF);

    gdt[i].limit_low   = (uint16_t)(limit & 0xFFFF);
    gdt[i].granularity = (uint8_t)((limit >> 16) & 0x0F);
    gdt[i].granularity |= (granularity & 0xF0);

    gdt[i].access = access;
}

/* Assembly: load GDT and reload segment registers */
static void gdt_flush(void) {
    __asm__ volatile (
        "lgdt (%0)\n"
        "mov $0x10, %%ax\n"
        "mov %%ax, %%ds\n"
        "mov %%ax, %%es\n"
        "mov %%ax, %%fs\n"
        "mov %%ax, %%gs\n"
        "mov %%ax, %%ss\n"
        "ljmp $0x08, $1f\n"
        "1:\n"
        : : "r"(&gp) : "eax", "memory"
    );
}

void gdt_init(void) {
    /* Entry 0: null descriptor (required) */
    gdt_set_entry(0, 0, 0, 0, 0);

    /* Entry 1: kernel code — base 0, limit 4GB, ring 0, executable/readable */
    gdt_set_entry(1, 0, 0xFFFFF, 0x9A, 0xCF);

    /* Entry 2: kernel data — base 0, limit 4GB, ring 0, writable */
    gdt_set_entry(2, 0, 0xFFFFF, 0x92, 0xCF);

    /* Set up pointer and load */
    gp.limit = (uint16_t)(sizeof(gdt) - 1);
    gp.base  = (uint32_t)&gdt;

    gdt_flush();
}