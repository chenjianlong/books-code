#include <stdio.h>

/*
 * Do rotating right shift. Assume 0 <= n < w
 * Examples when x = 0x12345678 and w = 32:
 * n=4 -> 0x81234567, n=20 -> 0x45678123
 */
unsigned rotate_right(unsigned x, int n) {
    int w = sizeof(unsigned) << 3;
    unsigned mask = (unsigned)(-1) >> (w - n - 1) >> 1;
    unsigned leftmost = (x & mask) << (w - n - 1) << 1;
    return (x >> n) | leftmost;
}

int main() {
    unsigned x = 0x12345678;
    int n = 4;
    printf("rotate_right(0x%X, %d)=0x%X\n", x, n, rotate_right(x, n));
    n = 20;
    printf("rotate_right(0x%X, %d)=0x%X\n", x, n, rotate_right(x, n));
    n = 31;
    printf("rotate_right(0x%X, %d)=0x%X\n", x, n, rotate_right(x, n));
    n = 0;
    printf("rotate_right(0x%X, %d)=0x%X\n", x, n, rotate_right(x, n));
    return 0;
}