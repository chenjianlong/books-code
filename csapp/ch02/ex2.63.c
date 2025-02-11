#include <stdio.h>
#include <assert.h>

int sra(int x, int k) {
    /* Perform shift logically */
    int xsrl = (unsigned) x >> k;
    int w = sizeof(int) << 3;
    int mask = -1 << (w - k);
    int m = 1 << (w - 1);
    mask &= !(m & x) - 1;
    return mask | xsrl;
}

unsigned srl(unsigned x, int k) {
    /* Perform shift arithmetically */
    unsigned xsra = (int) x >> k;
    int w = sizeof(int) << 3;
    int mask = -1 << (w - k);
    return xsra & ~mask;
}

int main() {
    unsigned test_unsigned = 0x12345678;
    int test_int = 0x12345678;

    assert(srl(test_unsigned, 4) == test_unsigned >> 4);
    assert(sra(test_int, 4) == test_int >> 4);

    test_unsigned = 0x87654321;
	test_int = 0x87654321;

	assert(srl(test_unsigned, 4) == test_unsigned >> 4);
	assert(sra(test_int, 4) == test_int >> 4);
    return 0;
}