#include <stdio.h>
#include <assert.h>
#include <limits.h>

/* Access bit-level representation floating-point number */
typedef unsigned float_bits;

static float float_bits_to_f(float_bits fb) {
    return *(float*)&fb;
}

float_bits float_to_float_bits(float f) {
    return *(float_bits*)&f;
}

/*
 * Assume i > 0
 * calculate i's bit length
 *
 * e.g.
 * 0x3 => 2
 * 0xFF => 8
 * 0x80 => 8
 */
int bits_length(int i) {
  if ((i & INT_MIN) != 0) {
    return 32;
  }

  unsigned u = (unsigned)i;
  int length = 0;
  while (u >= (1<<length)) {
    length++;
  }
  return length;
}

/*
 * generate mask
 * 00000...(32-l) 11111....(l)
 *
 * e.g.
 * 3  => 0x00000007
 * 16 => 0x0000FFFF
 */
unsigned bits_mask(int l) {
  return (unsigned) -1 >> (32-l);
}


/*
 * Compute (float) i
 */
float_bits float_i2f(int i) {
  unsigned sig, exp, frac, rest, exp_sig /* except sig */, round_part;
  unsigned bits, fbits;
  unsigned bias = 0x7F;

  if (i == 0) {
    sig = 0;
    exp = 0;
    frac = 0;
    return sig << 31 | exp << 23 | frac;
  }
  if (i == INT_MIN) {
    sig = 1;
    exp = bias + 31;
    frac = 0;
    return sig << 31 | exp << 23 | frac;
  }

  sig = 0;
  /* 2's complatation */
  if (i < 0) {
    sig = 1;
    i = -i;
  }

  bits = bits_length(i);
  fbits = bits - 1;
  exp = bias + fbits;

  rest = i & bits_mask(fbits);
  if (fbits <= 23) {
    frac = rest << (23 - fbits);
    exp_sig = exp << 23 | frac;
  } else {
    int offset = fbits - 23;
    int round_mid = 1 << (offset - 1);

    round_part = rest & bits_mask(offset);
    frac = rest >> offset;
    exp_sig = exp << 23 | frac;

    /* round to even */
    if (round_part < round_mid) {
      /* nothing */
    } else if (round_part > round_mid) {
      exp_sig += 1;
    } else {
      /* round_part == round_mid */
      if ((frac & 0x1) == 1) {
        /* round to even */
        exp_sig += 1;
      }
    }
  }

  return sig << 31 | exp_sig;
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