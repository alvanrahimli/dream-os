#include "includes/text.h"
#include "includes/screen.h"
#include "../../lib/string/includes/string.h"


void print_at(char* message, int col, int row) {
    if (col >= 0 && row >= 0) {
        set_cursor(get_screen_offset(col, row));
    }

    int i = 0;
    while (message[i] != 0)
    {
        print_char(message[i], col, row, WHITE_ON_BLACK);
        i++;
    }
}

void print(char* message) {
    print_at(message, -1, -1);
}

void println(char* message) {
    char final[1024] = "";
    strcat(final, message);
    strcat(final, "\n");
    print(final);
}