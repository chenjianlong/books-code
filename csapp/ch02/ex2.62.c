#include <stdio.h>

int int_shifts_are_logical() {
    int i = 1;
    int bits = (sizeof(i) << 3) - 1;
    i <<= bits;
    i >>= bits;
    return i == 1;

    /* other method: https://dreamanddead.github.io/CSAPP-3e-Solutions/chapter2/2.62/
      int num = -1;
      return !(num ^ (num >> 1));
    */
}

int main() {
    printf("int_shifts_are_logical=%d\n", int_shifts_are_logical());
    return 0;
}