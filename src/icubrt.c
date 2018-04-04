/***********************************************************
    icubrt.c -- 立方根
***********************************************************/

unsigned int icubrt(unsigned int x)
{
    unsigned int s, t;

    if (x == 0) return 0;
    s = 1;  t = x;
    while (s < t) {  s <<= 1;  t >>= 2;  }
    do {
        t = s;  s = (x / (s * s) + 2 * s) / 3;
    } while (s < t);
    return t;
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    unsigned int i;
    unsigned long s;

    printf("整数の立方根のテスト中\n");
    i = 0;
    do {
        if ((i & 0x3fff) == 0) printf("i = %u\n", i);
        s = icubrt(i);
        if (s * s * s > i || (s + 1) * (s + 1) * (s + 1) <= i) {
            printf("Error: i = %u, icubrt(i) = %lu\n", i, s);
            break;
        }
    } while (++i != 0);
    printf("テスト完了\n");
    return 0;
}
