#include <stdio.h>

/* Declaration of data type where 4 bytes are packed
   into an unsigned */
typedef unsigned packed_t;

/* Extract byte from word. Return as signed integer */
int xbyte(packed_t word, int bytenum) {
    int w = 24;
    int n = 24 - (bytenum << 3);
    return (int)(word << n) >> w;
    
    /* extend solution, worked well on packed_t is 2 bytes & 8 bytes also
    int w = (sizeof(packed_t) - 1) << 3;
    int n = bytenum << 3;
    return (int)((word >> n)  << w) >> w;
    */
}

int main() {
    packed_t word = 0x3456789A;
    int num  = 0;
    int r = xbyte(word, num);
    printf("xbyte(0x%X, %d)=%d(0x%X)\n", word, num, r, r);

    num  = 1;
    r = xbyte(word, num);
    printf("xbyte(0x%X, %d)=%d(0x%X)\n", word, num, r, r);

    num  = 2;
    r = xbyte(word, num);
    printf("xbyte(0x%X, %d)=%d(0x%X)\n", word, num, r, r);

    num  = 3;
    r = xbyte(word, num);
    printf("xbyte(0x%X, %d)=%d(0x%X)\n", word, num, r, r);
    return 0;
}