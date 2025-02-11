#include <stdio.h>

/*
 * Mask with least signficant n bits set to 1
 * Examples: n = 6 --> 0x3F, n = 17 --> 0x1FFFF
 * Assume 1 <= n <= w
 */
int lower_one_mask(int n) {
    int x = 1 << (n - 1) << 1;
    return (x - 1);
}

int main() {
    printf("lower_one_mask(%d)=0x%X\n", 6, lower_one_mask(6));
    printf("lower_one_mask(%d)=0x%X\n", 17, lower_one_mask(17));
    printf("lower_one_mask(%d)=0x%X\n", 31, lower_one_mask(31));
    printf("lower_one_mask(%d)=0x%X\n", 32, lower_one_mask(32));
    return 0;
}