/***********************************************************
    isqrt.c -- 平方根
***********************************************************/

unsigned int isqrt(unsigned int x)
{
    unsigned int s, t;

    if (x == 0) return 0;
    s = 1;  t = x;
    while (s < t) {  s <<= 1;  t >>= 1;  }
    do {
        t = s;
        s = (x / s + s) >> 1;
    } while (s < t);
    return t;
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    unsigned int i;
    unsigned long s;

    printf("整数の平方根のテスト中\n");
    i = 0;
    do {
        if ((i & 0x3fff) == 0) printf("i = %u\n", i);
        s = isqrt(i);
        if (s * s > i || (s + 1) * (s + 1) <= i) {
            printf("Error: i = %u, isqrt(i) = %lu\n", i, s);
            break;
        }
    } while (++i != 0);
    printf("テスト完了\n");
    return 0;
}
