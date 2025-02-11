#include <stdio.h>

/* Declarations of functions implementing operations bis and bic */
int bis(int x, int m);
int bic(int x, int m);

/* Compute x|y using only calls to functions bis and bic */
int bool_or(int x, int y) {
    int result = bis(x, y);
    return result;
}

/* Compute x^y using only calls to functions bis and bic */
int bool_xor(int x, int y) {
    int result = bis(bic(x,y), bic(y,x));
    return result;
}

int bis(int x, int m) {
    return x | m;
}

int bic(int x, int m) {
    return x & ~m;
}

int main() {
    int x = 0x12345678;
    int y = 0x87654321;
    printf("x|y=0x%X\n", bool_or(x, y));
    printf("x^y=0x%X\n", bool_xor(x, y));
    return 0;
}