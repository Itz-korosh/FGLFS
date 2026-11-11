#include <stdint.h>
#include "vgaprint.h"

void put_char(int row, int col, char c, uint8_t color) {
    volatile uint8_t *video = (volatile uint8_t *)0xB8000;
    int offset = (row * 80 + col) * 2;
    video[offset] = c;
    video[offset + 1] = color;
}

void clear_screen(void) {
    volatile uint8_t *video = (volatile uint8_t *)0xB8000;
    for (int i = 0; i < 80 * 25; i++) {
        video[i * 2] = ' ';
        video[i * 2 + 1] = 0x07;
    }
}

void put_string(int row, int col, const char *str, uint8_t color) {
    volatile uint8_t *video = (volatile uint8_t *)0xB8000;
    int offset = (row * 80 + col) * 2;
    for (int i = 0; str[i] != '\0'; i++) {
        video[offset + i * 2] = str[i];
        video[offset + i * 2 + 1] = color;
    }
}