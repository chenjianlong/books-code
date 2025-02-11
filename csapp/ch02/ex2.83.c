#include <stdio.h>
#include <assert.h>

unsigned f2u(float x) {
  return *(unsigned*)&x;
}

int float_ge(float x, float y) {
    unsigned ux = f2u(x);
    unsigned uy = f2u(y);
    /* Get the sign bits */
    unsigned sx = ux >> 31;
    unsigned sy = uy >> 31;

    /* Give an expression using only ux, uy, sx, and sy */
    return (!(ux << 1) && !(uy << 1)) || /* both zeros */
        (!sx && sy) ||                   /* x >= 0, y <= 0 */
        (!sx && !sy && ux >= uy) ||      /* x >= 0, y >= 0 */
        (sx && sy && ux <= uy);          /* x <= 0, y <= 0 */
}

int main(int argc, char* argv[]) {
  assert(float_ge(-0, +0));
  assert(float_ge(+0, -0));
  assert(float_ge(3, 0));
  assert(float_ge(-0, -4));
  assert(float_ge(4, -4));
  return 0;
}


