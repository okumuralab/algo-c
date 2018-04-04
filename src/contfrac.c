/***********************************************************
    contfrac.c -- 連分数
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>   /* floor */

void contfrac(double x, int n, long b[])
{
    int i;

    b[0] = floor(x);
    for (i = 1; i <= n; i++) {
        x = 1 / (x - b[i - 1]);
        b[i] = floor(x);
    }
}

long gcd(long x, long y)
{
    long t;

    while (y != 0) {
        t = x % y;  x = y;  y = t;
    }
    return x;
}

void reduce_cf(int n, long b[])
{
    int i;
    long f, g, temp, d;

    f = b[n];  g = 1;
    for (i = n - 1; i >= 0; i--) {
        temp = b[i] * f + g;  g = f;  f = temp;
        d = gcd(f, g);  f /= d;  g /= d;
    }
    printf("%ld / %ld = %g\n", f, g, (double)f / g);
}

#define N 17

int main(void)
{
    int i;
    long b[N + 1];

    /* e = 2.718...の連分数展開 */
    contfrac(2.71828182845904524, N, b);
    printf("e = [");
    for (i = 0; i <= N; i++) printf("%ld,", b[i]);
    printf("...]\n");

    /* ふつうの分数と実数に直す */
    reduce_cf(N, b);

    return 0;
}
