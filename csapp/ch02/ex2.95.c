#include <stdio.h>
#include <limits.h>

/* Access bit-level representation floating-point number */
typedef unsigned float_bits;

float_bits float_to_float_bits(float f) {
    return *(float_bits*)&f;
}

unsigned leftmost_one(unsigned x) {
    x |= x >> 16;
    x |= x >> 8;
    x |= x >> 4;
    x |= x >> 2;
    x |= x >> 1;
    return (x >> 1) + 1;
}

/* Compute (float) i */
float_bits float_i2f(int i) {
    if (!i) return (float_bits)i;
    unsigned exp = 0x7F;
    unsigned sign = (unsigned)i >> 31;
    unsigned round_up = 0;

    if (i < 0) i = -i;

    unsigned leftmost = leftmost_one((unsigned)i);
    unsigned frac = i * (0x80000000 / leftmost);

    unsigned trunc = frac & 0xFF;
    if ((trunc > 0x80) || ((trunc & 0x80) && (frac & 0x100))) {
        round_up = 1;
    }

    frac = (frac >> 8) & 0x7FFFFF;

    leftmost >>= 1;
    while (leftmost != 0) {
        exp += 1;
        leftmost >>= 1;
    }

    return ((sign << 31) | (exp << 23) | frac) + round_up;
}

int main() {
    int i = INT_MIN;
    for (; i <= INT_MAX; ++i) {
        float_bits fbl = float_i2f(i);
        float_bits fbr = float_to_float_bits((float)i);
        if (fbl != fbr) {
            printf("%d(0x%X) failure, float_i2f=0x%X, (float)i=0x%X\n",
                i, (unsigned)i, fbl, fbr);
            return 1;
        }

        if (i == INT_MAX) {
            break;
        }
    }

    return 0;
}