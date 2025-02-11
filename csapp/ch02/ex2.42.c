#include <stdio.h>
#include <stdlib.h>

int div16(int x) {
    int bias = (x >> 31) & 0xF;
    return (x + bias) >> 4;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <number>\n", argv[0]);
        exit(1);
    }

    int x = atoi(argv[1]);
    int result = div16(x);
    printf("x=%d(0x%X), div16=%d(0x%X)\n", x, x, result, result);
    return 0;
}