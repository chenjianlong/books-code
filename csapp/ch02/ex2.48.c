#include <stdio.h>
#include <string.h>

int main() {
    int x = 0x00359141;
    int y = 0x4A564504;
    float f = 0;
    memcpy(&f, &y, sizeof(y));

    printf("x(0x%X): %d, float(0x%X): %f\n", x, x, y, f);
    return 0;
}