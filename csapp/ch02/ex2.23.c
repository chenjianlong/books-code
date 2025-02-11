#include <stdio.h>

int fun1(unsigned word) {
    return (int) ((word << 24) >> 24);
}

int fun2(unsigned word) {
    return ((int) word << 24) >> 24;
}

int main() {
    unsigned words[] = {
        0x00000076,
        0x87654321,
        0x000000C9,
        0xEDCBA987
    };

    for (int i = 0; i < sizeof(words) / sizeof(unsigned); ++i) {
        printf("0x%08X, fun1=0x%08X, fun2=0x%08X\n", words[i], fun1(words[i]), fun2(words[i]));
    }

    return 0;
}