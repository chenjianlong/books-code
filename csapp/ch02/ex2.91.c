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

/* Compute |f|. If f is NaN, then return f. */
float_bits float_absval(float_bits f) {
    unsigned sign = f>>31;
    unsigned exp = f>>23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    if (exp != 0xFF || frac == 0) {
        sign = 0;
    }

    /* Reassemble bits */
    return (sign << 31) | (exp << 23) | frac;
}

int main() {
    float_bits fb = 0;
    for (; fb <= UINT_MAX; ++fb) {
        float_bits fbl = float_absval(fb);
        float_bits fbr = float_to_float_bits(fabsf(float_bits_to_f(fb)));
        if (((fbl & 0xFF800000) == 0xFF800000) && fb > 0x80000000) {
            fbr |= 0x80000000;
        }

        if (fbl != fbr) {
            printf("0x%X failure, float_absval=0x%X, fabsf=0x%X\n",
                fb, fbl, fbr);
            return 1;
        }

        if (fb == UINT_MAX) {
            break;
        }
    }

    return 0;
}