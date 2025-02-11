#include <stdio.h>

int main() {
    int x = 0x3FFFFFFF;
    int y = (int)(float)x;
    int result = (x==y);
    printf("B. x=%d(0x%X), y=%d(0x%X), (x==y)=%d\n", x, x, y, y, result);

    double d = 2147483647.0;
    double d2 = (double)(float)d;
    result = (d == d2);
    printf("C. d=%f, d2=%f, (x==y)=%d\n", d, d2, result);

    d = 1.0;
    float f = 1.0e20;
    printf("H. f=%f, d=%f, (f+d)-f=%f\n", f, d, ((f+d)-f));
    return 0;
}