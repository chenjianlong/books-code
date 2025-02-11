#include <stdio.h>

/*
 * Generate mask indicating leftmost 1 in x. Assume w=32.
 * For example 0xFF00 -> 0x8000, and 0x6600 --> 0x4000.
 * If x = 0, then return 0.
 */
int leftmost_one(unsigned x) {
    x |= x >> 16;
    x |= x >> 8;
    x |= x >> 4;
    x |= x >> 2;
    x |= x >> 1;
    return (x >> 1) + 1;
}

int main() {
    unsigned x = 0xFF00;
    printf("leftmost_one(0x%X)=0x%X\n", x, leftmost_one(x));
    x = 0x6600;
    printf("leftmost_one(0x%X)=0x%X\n", x, leftmost_one(x));
    return 0;
}