#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <math.h>

/* Access bit-level representation floating-point number */
typedef unsigned float_bits;

static float float_bits_to_f(float_bits fb) {
    return *(float*)&fb;
}

float_bits float_to_float_bits(float f) {
    return *(float_bits*)&f;
}

/* Compute 0.5*f. If f is NaN, then return f */
float_bits float_half(float_bits f) {
    unsigned sign = f>>31;
    unsigned rest = f & 0x7FFFFFFF;
    unsigned exp = f>>23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    if (exp == 0xFF) {
        return f;
    }

    /*
     * round to even, we care about last 2 bits of frac
     *
     * 00 => 0 just >>1
     * 01 => 0 (round to even) just >>1
     * 10 => 1 just >>1
     * 11 => 1 + 1 (round to even) just >>1 and plus 1
     */
    int addition = (frac & 0x3) == 0x3;

    if (exp == 0) {
        frac >>= 1;
        frac += addition;
    } else if (exp == 1) {
        /* Normalized to denormalized */
        rest >>= 1;
        rest += addition;
        exp = rest >> 23 & 0xFF;
        frac = rest & 0x7FFFFF;
    } else {
        /* Normalized */
        exp -= 1;
    }

    /* Reassemble bits */
    return (sign << 31) | (exp << 23) | frac;
}

int main() {
    float_bits fb = 0;
    for (; fb <= UINT_MAX; ++fb) {
        float_bits fbl = float_half(fb);
        float_bits fbr = float_to_float_bits(0.5f*(float_bits_to_f(fb)));
        if ((fb & 0x7F800000) == 0x7F800000) {
            fbr = fb;
        }

        if (fbl != fbr) {
            printf("0x%X failure, float_half=0x%X, 0.5*f=0x%X\n",
                fb, fbl, fbr);
            return 1;
        }

        if (fb == UINT_MAX) {
            break;
        }
    }

    return 0;
}