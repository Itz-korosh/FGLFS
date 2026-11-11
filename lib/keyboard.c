#include "keyboard.h"
#include "io.h"
#include "vgaprint.h"

/* US QWERTY keyboard scancode to ASCII map */
static const char kbd_us[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
  '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0,  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',   0,
  '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0, '*',   0, ' ',
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
};

static int cursor_row = 10; /* Start typing at row 10 */
static int cursor_col = 0;

void keyboard_init(void) {
    /* Nothing to do yet, PIC remap handles the enabling */
}

void keyboard_handler(void) {
    uint8_t scancode = inb(0x60);
    
    /* If the highest bit is set, it's a key release. Ignore it. */
    if (scancode & 0x80) {
        return;
    }
    
    char c = kbd_us[scancode];
    
    /* Ignore Escape for now */
    if (c == 27) {
        return;
    }
    
    /* Handle Enter */
    if (c == '\n') {
        cursor_col = 0;
        cursor_row++;
    } 
    /* Handle Backspace */
    else if (c == '\b') {
        if (cursor_col > 0) {
            cursor_col--;
            /* Erase the character by printing a space */
            put_char(cursor_row, cursor_col, ' ', 0x0F);
        }
    }
    /* Handle normal characters */
    else if (c != 0) {
        put_char(cursor_row, cursor_col, c, 0x0F);
        cursor_col++;
    }

    /* If we hit the right edge of the screen, wrap to the next line */
    if (cursor_col >= 80) {
        cursor_col = 0;
        cursor_row++;
    }
}