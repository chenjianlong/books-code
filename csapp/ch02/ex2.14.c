#include <stdio.h>

int main() {
    unsigned char x = 0x66;
    unsigned char y = 0x39;

    printf("x&y=0x%X\n", x&y);
    printf("x|y=0x%X\n", x|y);
    printf("~x|~y=0x%X\n", (unsigned char)(~x)|(unsigned char)(~y));
    printf("x&!y=0x%X\n", x&!y);

    printf("x&&y=0x%X\n", x&&y);
    printf("x||y=0x%X\n", x||y);
    printf("!x||!y=0x%X\n", !x||!y);
    printf("x&&~y=0x%X\n", x&&~y);
    return 0;
}