#include <stdio.h>

int main()
{
    float f1 = (3.14 + 1e20) - 1e20;
    float f2 = 3.14 + (1e20 - 1e20);

    printf("result, f1: %f, f2: %f\n", f1, f2);
}