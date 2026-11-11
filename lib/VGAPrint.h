#ifndef VGAPRINT_H
#define VGAPRINT_H

#include <stdint.h>

void put_char(int row, int col, char c, uint8_t color);
void clear_screen(void);
void put_string(int row, int col, const char *str, uint8_t color);

#endif