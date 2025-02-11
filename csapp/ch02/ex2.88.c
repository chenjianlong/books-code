#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>

/*
 * most important thing is that all double number come from ints
 */

/* right */
int A(int x, double dx) {
  return (float)x == (float)dx;
}

/* wrong when sum is overflow */
int B(int x, double dx, int y, double dy) {
  return dx+dy == (double)(x+y);
}

/* right */
int C(double dx, double dy, double dz) {
  return dx+dy+dz == dz+dy+dx;
}

/* wrong
 *
 * 关键点在于 double 有 52 位小数位，最多能精确表示需要 53 位来表示的整数（比如二进制的：1000...(51)1）
 * 因此 double 最小的不能精确表述的整数是 2^53+1(这个数需要54位才能精确表示)（但是 double 可以精确表示 2^53或者2^53+2）
 * 当三个由 int 转成的 double 的乘积发生了舍入，并且左右两边舍弃的值不相等时，表达式返回 0
 * 考虑三个整数转换的 double dx:2^30+1、dy:2^23+1、dz:2^24
 * 先看左边 dx * dy * dz
 * dx * dy = (2^30+1)(2^23+1) = (2^53+2^30+2^23+1) 超出了 double 的精度范围，发生舍入，结果为：(2^53+2^30+2^23)
 * 这个结果再乘以 dz 结果为： 2^77+2^54+2^47
 * 再看右边：dz * dy * dx
 * dz * dy = 2^24(2^23+1) = 2^47+2^24
 * 这个结果再乘以 dx 结果为：(2^47+2^24)(2^30+1)=2^77+2^54+2^47+2^24，发生舍入，结果为：2^77+2^54+2^47
 * 可以看到看到左右表达式虽然都发生了舍入，但最终结果是相等的
 *
 * 再来看：dx:2^30+1、dy:2^23+1、dz:2^24+1 的情况
 * 先看左边 dx * dy * dz
 * dx * dy = (2^30+1)(2^23+1) = (2^53+2^30+2^23+1) 超出了 double 的精度范围，发生舍入，结果为：(2^53+2^30+2^23)
 * 这个结果再乘以 dz： (2^53+2^30+2^23)*(2^24+1)=2^77+2^54+2^47+2^53+2^30+2^23 舍入后结果为；2^77+2^54+2^53+2^47+2^30
 * 再看右边：dz * dy * dx
 * dz * dy = (2^24+1)(2^23+1) = 2^47+2^24+2^23+1
 * 这个结果再乘以 dx 结果为：(2^47+2^24+2^23+1)(2^30+1)=2^77+2^54+2^53+2^30+2^47+2^24+2^23+1
 * = 2^23(2^54+2^31+2^30+2^24+2^7+2+1)+1
 * 发生向上舍入，结果为：2^23(2^54+2^31+2^30+2^24+2^7+2+1+1)=2^77+2^54+2^53+2^47+2^30+2^25
 * 可以看到看到左右表达式发生了不同的舍入，最终结果是不相等的
 */
int D(double dx, double dy, double dz) {
  double left = dx*dy*dz;
  double right = dz*dy*dx;
  printf("dx: %f, dy: %f, dz: %f, left: %f, right: %f, right-left: %f\n",
    dx, dy, dz, left, right, right-left);
  return dx*dy*dz == dz*dy*dx;
}

/* wrong when dx != 0 and dz == 0 */
int E(double dx, double dz) {
  return dx/dx == dz/dz;
}

int powimpl(int x, int n) {
    if (n == 0) return 1;
    return x * powimpl(x, n - 1);
}

int main(int argc, char* argv[]) {
  srand(time(NULL));
  int x = rand();
  int y = rand();
  int z = rand();
  double dx = (double)x;
  double dy = (double)y;
  double dz = (double)z;

  printf("A: %d\n", A(x, dx));
  printf("B: %d\n", B(INT_MAX, (double)(INT_MAX), INT_MAX, (double)(INT_MAX)));
  printf("C: %d\n", C(dx, dy, dz));
  printf("D: %d\n", D((double)(powimpl(2, 30)+1), (double)(powimpl(2, 23)+1),
    (double)(powimpl(2, 24))));
  printf("D: %d\n", D((double)(powimpl(2, 30)+1), (double)(powimpl(2, 23)+1),
    (double)(powimpl(2, 24)+1)));
  printf("E: %d\n", E(dx, (double)(int)0));
  return 0;
}