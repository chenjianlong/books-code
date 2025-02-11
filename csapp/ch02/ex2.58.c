#include <stdio.h>

int is_little_endian() {
    int x = 1;
    char c = *((char*)&x);
    return c == 1;
}

int main() {
    printf("is_little_endian=%d\n", is_little_endian());
    return 0;
}