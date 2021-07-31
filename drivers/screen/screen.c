#include "includes/screen.h"
#include "../../kernel/includes/util.h"
#include "../../kernel/includes/low_level.h"

void print_char(char character, int col, int row, char attribute_byte) {
    unsigned char *vid_mem = (unsigned char*) VIDEO_ADDRESS;

    // If attribute byte is 0, we set default
    if (!attribute_byte) {
        attribute_byte = WHITE_ON_BLACK;
    }

    int offset;
    if (col >= 0 && row >= 0) {
        offset = get_screen_offset(col ,row);
    } else {
        offset = get_cursor();
    }

    if (character == '\n') {
        int rows = offset / (2 * MAX_COLS);
        offset = get_screen_offset(79, rows);
    } else {
        vid_mem[offset] = character;            // Set character byte
        vid_mem[offset + 1] = attribute_byte;   // Set attribute byte
    }

    offset += 2;
    offset = handle_scrolling(offset);
    set_cursor(offset);
}

void clrscr() {
    int row = 0;
    int col = 0;

    for (row = 0; row < MAX_ROWS; row++) {
        for (col = 0; col < MAX_COLS; col++) {
            print_char(' ', col, row, WHITE_ON_BLACK);
        }
    }

    set_cursor(get_screen_offset(0, 0));
}

int get_screen_offset(int cols, int rows) {
    return (rows * MAX_COLS + cols) * 2;
}

int get_cursor() {
    port_byte_out(REG_SCREEN_CTRL, CLR_HIGH);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;
    port_byte_out(REG_SCREEN_CTRL, CLR_LOW);
    offset += port_byte_in(REG_SCREEN_DATA);
    
    return offset * 2;
}

void set_cursor(int offset) {
    offset /= 2;

    port_byte_out(REG_SCREEN_CTRL, CLR_HIGH);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, CLR_LOW);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)offset);
}

int handle_scrolling(int offset) {
    if (offset < MAX_ROWS * MAX_COLS * 2) {
        return offset;
    }

    int i;
    for (i = 1; i < MAX_ROWS; i++) {
        mem_copy((char *)get_screen_offset(0, i) + VIDEO_ADDRESS,
                 (char *)get_screen_offset(0, i - 1) + VIDEO_ADDRESS,
                 MAX_COLS * 2);
    }

    char* last_line = (char *)get_screen_offset(0, MAX_ROWS - 1) + VIDEO_ADDRESS;
    for (i = 0; i < MAX_COLS * 2; i++) {
        last_line[i] = 0;
    }

    offset -= 2 * MAX_COLS;
    return offset;
}