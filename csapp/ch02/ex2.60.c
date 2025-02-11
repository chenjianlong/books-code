#include <stdio.h>

unsigned replace_byte(unsigned x, unsigned char b, int i) {
    unsigned shift_bits = (i << 3);
    unsigned mask = ~(0xFF << shift_bits);
    unsigned repalce = (unsigned)(b) << shift_bits;
    return (x & mask) | repalce;
}

int main() {
    unsigned x = 0x12345678;
    unsigned char c = 0xAB;
    for (int i = 0; i < sizeof(x); ++i) {
        unsigned result = replace_byte(x, c, i);
        printf("x=0x%X, char=0x%X, i=%d, result=0x%X\n", x, c, i, result);
    }

    return 0;
}