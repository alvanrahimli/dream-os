#include "includes/string.h"
#include "../../kernel/includes/util.h"

int strlen(char* str) {
    int len = 0;
    while (*str++) {
        len++;
    }

    return len;
}

char* strcat(char* s1, char* s2) {
    int s1_len = strlen(s1);
    int s2_len = strlen(s2);

    for (int i = s1_len; i < s1_len + s2_len; i++) {
        s1[i] = s2[i - s1_len];
    }

    return s1;
}
