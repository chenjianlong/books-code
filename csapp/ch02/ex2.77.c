#include <stdio.h>
#include <limits.h>
#include <assert.h>

/* Divide by power of two. Assume 0 <= k < w-1 */
int divide_power2(int x, int k) {
    int sig_mask = INT_MIN;
    // (x<0 ? x+(1<<k)-1 : x) >> k
    (x & sig_mask) && (x += (1 << k) - 1);
    return x >> k;
}

int main() {
    assert(divide_power2(5, 1) == 2);
    assert(divide_power2(-5, 1) == -2);
    return 0;
}