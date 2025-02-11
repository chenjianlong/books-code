#include <stdio.h>

int testA(int x) {
    return !~x;
}

int testB(int x) {
    return !x;
}

int testC(int x) {
    return !(x & 0xffU ^ 0xffU);
    // or
    // return testA(x | ~0xff);
}

int testD(int x) {
    return !((x >> ((sizeof(int)-1) << 3)) & 0xff);
}