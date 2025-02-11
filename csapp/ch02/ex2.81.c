#include <stdio.h>
#include <limits.h>

int A() {
    int x = INT_MIN;
    int y = 0;
    int res = (x > y) == (-x < -y);
    printf("A: %d\n",  res);
}

int C() {
    int x = 1;
    int y = 1;

    int res = ~x+~y == ~(x+y);
    printf("C: %d\n", res);
}

int main() {
    A();
    C();

    return 0;
}