/*
 * 2.77.c
 */
#include <stdio.h>
#include <assert.h>

/* K = 5 */
int A(int x) {
  return (x << 2) + x;
}

/* K = 9 */
int B(int x) {
  return (x << 3) + x;
}

/* K = 30 */
int C(int x) {
  return (x << 5) - (x << 1);
}

/* K = -56 */
int D(int x) {
  return (x << 3) - (x << 6);
}

int main(int argc, char* argv[]) {
  int x = 0x87654321;
  assert(A(x) == 5 * x);
  assert(B(x) == 9 * x);
  assert(C(x) == 30 * x);
  assert(D(x) == -56 * x);
  return 0;
}

