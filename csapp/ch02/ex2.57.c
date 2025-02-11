#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    size_t i;
    for (i = 0; i < len; i++)
	printf(" %.2x", start[i]);    //line:data:show_bytes_printf
    printf("\n");
}

void show_short(short int x) {
    show_bytes((byte_pointer) &x, sizeof(short int));
}

void show_long(long int x) {
    show_bytes((byte_pointer) &x, sizeof(long int));
}

void show_double(double x) {
    show_bytes((byte_pointer) &x, sizeof(double));
}

int main() {
    short int x = 0x1234;
    printf("short int x = 0x%X\n", x);
    show_short(x);

    long int y = 0x1234567898765432;
    printf("long int y = 0x%lX\n", y);
    show_long(y);

    double d = 0.1;
    printf("double d=0.1\n");
    show_double(d);

    return 0;
}