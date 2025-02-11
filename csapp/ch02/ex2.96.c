#include <stdio.h>
#include <limits.h>

typedef unsigned float_bits;

float float_bits_to_f(float_bits f) {
    return *(float*)&f;
}

/*
 * Compute (int) f
 * If conversion causes overflow or f is NaN, return 0x80000000
 */
int float_f2i(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = (f & 0x7F800000) >> 23;
    unsigned frac = f & 0x7FFFFF;
    if (exp < 127) {
        return 0;
    } else if (exp >= 158) { /* >= 2^31 */
        return 0x80000000;
    } else {
        exp -= 127;
        frac |= 0x800000;
        unsigned result = 0;
        if (exp >= 23) {
            exp -= 23;
            result = frac << exp;
        } else {
            result = frac >> (23 - exp);
        }

        if (sign) {
            result = -result;
        }

        return result;
    }
}

int main() {
    float_bits f = 0;
    for (; f <= UINT_MAX; ++f) {
        int il = float_f2i(f);
        int ir = (int)float_bits_to_f(f);
        if (il != ir) {
            printf("f: 0x%X il=0x%X ir=0x%X\n", f, il, ir);
            return 1;
        }

        if (f == UINT_MAX) {
            break;
        }
    }

    return 0;
}