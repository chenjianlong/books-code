#include <stdio.h>

int main() {
    int x = 0x89ABCDEF;
    int y = 0x765432EF;
    int z = (y & ~0xFF) | (x & 0xFF);
    printf("x=0x%X, y=0x%X, z=0x%X\n", x, y, z);
    return 0;
}