#include <stdio.h>

float u2f(unsigned x) {
    return *(float*)(&x);
}

/*
 * 分配给你一个任务，编写一个 C 函数来计算 2<sup>x</sup> 的浮点表示。
 * 你意识到完成这个任务的最好方法是直接创建结果的 IEEE 单精度表示。
 * 当 x 太小时，你的程序将返回 0.0。
 * 当 x 太大时，它会返回 +∞。
 * 填写下列代码的空白部分，以计算出正确的结果。
 * 假设函数 u2f 返回的浮点值与它的无符号参数有相同的位表示
 */
float fpwr2(int x) {
    /* Result exponent and fraction */
    unsigned exp, frac;
    unsigned u;

    if (x < -149) {
        /* Too small. Return 0.0 */
        exp = 0;
        frac = 0;
    } else if (x < -126) {
        /* Denormalized result */
        exp = 0;
        frac = 1 << (x + 149);
    } else if (x < 128) {
        /* Normalized result. */
        exp = x+127;
        frac = 0;
    } else {
        /* Too big. Return +oo */
        exp = 0xFF;
        frac = 0;
    }

    /* Pack exp and frac into 32 bits */
    u = exp << 23 | frac;
    /* Return as float */
    return u2f(u);
}

int main() {
    int i = -150;
    for (;i < 130; ++i) {
        float f = fpwr2(i);
        printf("i=%d, f=%f(0x%X)\n", i, f, *((unsigned*)&f));
    }

    return 0;
}