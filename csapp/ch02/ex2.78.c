/*
 * mul3div4.c
 */
#include <stdio.h>
#include <assert.h>
#include <limits.h>

/*
 * code from 2.77
 *
 * Divide by power of 2, -> x/2^k
 * Assume 0 <= k < w-1
 */
int divide_power2(int x, int k) {
    int sig_mask = INT_MIN;
    // (x<0 ? x+(1<<k)-1 : x) >> k
    (x & sig_mask) && (x += (1 << k) - 1);
    return x >> k;
}

int mul5div8(int x) {
  int mul5 = (x << 2) + x;
  return divide_power2(mul5, 3);
}

int main(int argc, char* argv[]) {
  int x = 0x87654321;
  assert(mul5div8(x) == x * 5 / 8);
  return 0;
}


