/*
 * tsub-ok.c
 */
#include <stdio.h>
#include <assert.h>
#include <limits.h>

/* Determine whether subtracted arguments will cause overflow */
int tsub_ovf(int x, int y) {
    int sig_mask = INT_MIN;
    
    int sub  = x - y;
    // x >= 0 && y < 0 && sub < 0
    int pos_over = !(x & sig_mask) && (y & sig_mask) && (sub & sig_mask);
    // x < 0 && y >= 0 && sub >= 0
    int neg_over = (x & sig_mask) && !(y & sig_mask) && !(sub & sig_mask);
    return pos_over || neg_over;
}

int main(int argc, char* argv[]) {
  assert(tsub_ovf(0x00, INT_MIN));
  assert(!tsub_ovf(0x00, 0x00));
  assert(!tsub_ovf(-1, INT_MIN));
  assert(!tsub_ovf(INT_MIN, INT_MIN));
  return 0;
}

