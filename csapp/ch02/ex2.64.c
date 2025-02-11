#include <stdio.h>

/* Return 1 when any even bit of x equals 1; 0 otherwise.
   Assume w=32 */
int any_even_one(unsigned x) {
    unsigned mask = 0x99999999;
    return !!(x & mask);
}

int main() {
    unsigned x = 1;
    printf("any_even_one(%u)=%d\n", x, any_even_one(x));

    x = 2;
    printf("any_even_one(%u)=%d\n", x, any_even_one(x));

    x = 0xF;
    printf("any_even_one(%u)=%d\n", x, any_even_one(x));
    return 0;
}