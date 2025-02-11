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

/* Compute 2*f. If f is NaN, then return f */
float_bits float_twice(float_bits f) {
    unsigned sign = f>>31;
    unsigned rest = f & 0x7FFFFFFF;
    unsigned exp = f>>23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    if (exp == 0xFF) {
        return f;
    }

    if (exp == 0xFE) {
        exp = 0xFF;
        frac = 0;
    } else if (exp > 0) {
        /* Normalized */
        exp += 1;
    } else {
        /* Denormalized */
        rest <<= 1;
        exp = rest >> 23 & 0xFF;
        frac = rest & 0x7FFFFF;
        //printf("exp=%d, frac=%d, rest=%d\n", exp, frac, rest);
    }

    /* Reassemble bits */
    return (sign << 31) | (exp << 23) | frac;
}

int main() {
    float_bits fb = 0;
    for (; fb <= UINT_MAX; ++fb) {
        float_bits fbl = float_twice(fb);
        float_bits fbr = float_to_float_bits(2.0f*float_bits_to_f(fb));
        if ((fb & 0x7F800000) == 0x7F800000) {
            fbr = fb;
        }

        if (fbl != fbr) {
            printf("0x%X failure, float_twice=0x%X, 2*f=0x%X\n",
                fb, fbl, fbr);
            return 1;
        }

        if (fb == UINT_MAX) {
            break;
        }
    }

    return 0;
}