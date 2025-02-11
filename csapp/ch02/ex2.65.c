#include <stdio.h>

/* Return 1 when x contains an even number of 1s; 0 otherwise.
   Assume w=32 */
int even_ones(unsigned x) {
    x ^= x >> 16;
    x ^= x >> 8;
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    return !(x&0x1);
}

int main() {
    unsigned x = 0x10101010;
    printf("even_ones(%u)=%d\n", x, even_ones(x));
    x = 0x10101011;
    printf("even_ones(%u)=%d\n", x, even_ones(x));
    return 0;
}