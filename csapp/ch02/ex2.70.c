#include <stdio.h>

/*
 * Return 1 when x can be represented as an n-bit, 2’s complement
 * number; 0 otherwise
 * Assume 1 <= n <= w
 */
int fits_bits(int x, int n) {
    int w = sizeof(int) << 3;
    return (x << (w-n) >> (w-n)) == x;
}

int main() {
    int x = 0x1;
    int n  = 1;
    printf("fits_bits(0x%X, %d)=%d\n", x, n, fits_bits(x, n));

    n  = 2;
    printf("fits_bits(0x%X, %d)=%d\n", x, n, fits_bits(x, n));

    x = -1;
    printf("fits_bits(0x%X, %d)=%d\n", x, n, fits_bits(x, n));
    return 0;
}