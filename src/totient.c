/***********************************************************
    totient.c -- Euler (オイラー) の関数
***********************************************************/

unsigned phi(unsigned x)
{
    unsigned d, t;

    t = x;
    if (x % 2 == 0) {
        t /= 2;
        do {  x /= 2;  } while (x % 2 == 0);
    }
    d = 3;
    while (x / d >= d) {
        if (x % d == 0) {
            t = t / d * (d - 1);
            do {  x /= d;  } while (x % d == 0);
        }
        d += 2;
    }
    if (x > 1) t = t / x * (x - 1);
    return t;
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i, j;

    printf("オイラーの関数 φ(1),…,φ(200)\n     ");
    for (j = 1; j <= 10; j++) printf("  +%2d", j);
    printf("\n     ");
    for (j = 1; j <= 10; j++) printf("-----");
    printf("\n");
    for (i = 0; i < 20; i++) {
        printf("%3d |", 10 * i);
        for (j = 1; j <= 10; j++) printf("%5d", phi(10 * i + j));
        printf("\n");
    }
    return 0;
}
