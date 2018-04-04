/***********************************************************
    gray2.c -- Gray (グレイ) 符号
***********************************************************/
#define N  6  /* 桁数 */
#define HIGHBIT  (1U << (N - 1))

unsigned int num_to_Gray(unsigned int x)
{
    unsigned int mask;
    enum {Off, On} sw;

    sw = Off;
    for (mask = HIGHBIT; mask != 0; mask >>= 1)
        if (sw) {
            x ^= mask;  /* ビット反転 ($0 \leftrightarrow 1$) */
            if (x & mask) sw = Off;
        } else
            if (x & mask) sw = On;
    return x;
}

unsigned int Gray_to_num(unsigned int x)
{
    unsigned int mask;
    enum {Off, On} sw;

    sw = Off;
    for (mask = HIGHBIT; mask != 0; mask >>= 1)
        if (sw) {
            if (x & mask) sw = Off;
            x ^= mask;  /* ビット反転 ($0 \leftrightarrow 1$) */
        } else
            if (x & mask) sw = On;
    return x;
}

#include <stdio.h>
#include <stdlib.h>

void show(unsigned int x)
{
    unsigned int mask;

    for (mask = HIGHBIT; mask != 0; mask >>= 1)
        putchar((x & mask) ? '1' : '0');
    putchar(' ');
}

int main(void)
{
    unsigned int x, y, z;

    for (x = 0; x < (1U << N); x++) {
        printf("%3u: ", x);  show(x);
        y = num_to_Gray(x);  show(y);
        z = Gray_to_num(y);  show(z);  printf("\n");
        if (x != z) printf("Error\n");
    }
    return 0;
}
