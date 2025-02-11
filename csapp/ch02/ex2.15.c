#include <stdio.h>
#include <stdlib.h>

int is_equal(int x, int y) {
    return !(x ^ y);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <num1> <num2>\n", argv[0]);
        exit(1);
    }

    int x = atoi(argv[1]);
    int y = atoi(argv[2]);

    printf("is_equal(%d,%d)=%d\n", x, y, is_equal(x, y));
    return 0;
}