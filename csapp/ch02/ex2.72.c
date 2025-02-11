#include <stdio.h>
#include <string.h>
#include <assert.h>

/* Copy integer into buffer if space is available */
void copy_int(int val, void *buf, int maxbytes) {
    if (maxbytes >= sizeof(val))
        memcpy(buf, (void *) &val, sizeof(val));
}

int main() {
    char buf[4] = {'\0'};
    int x = 0x12345678;
    int n = 4;
    copy_int(x, buf, n);
    assert(memcmp(buf, &x, n) == 0);

    memset(buf, '\0', sizeof(buf));
    n = 3;
    copy_int(x, buf, n);
    assert(memcmp(buf, &x, n) != 0);

    memset(buf, '\0', sizeof(buf));
    n = 2;
    copy_int(x, buf, n);
    assert(memcmp(buf, &x, n) != 0);

    memset(buf, '\0', sizeof(buf));
    n = 1;
    copy_int(x, buf, n);
    assert(memcmp(buf, &x, n) != 0);
    return 0;
}