#include "../drivers/screen/includes/text.h"

void mem_copy(char* source, char* dest, int no_bytes) {
    int i;
    for (i = 0; i < no_bytes; i++) {
        *(dest + i) = *(source + i);
    }
}

void memset(char* start, char byte, unsigned long size) {
    unsigned long i = 0;
    while (i < size) {
        *(start + i) = byte;
        i++;
    }
}

// TODO: implement malloc here...