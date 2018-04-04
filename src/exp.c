/***********************************************************
    exp.c -- 指数関数
***********************************************************/
#define LOG2 0.6931471805599453094172321214581765680755L  /* $\log_e{2}$ */

long double lldexp(long double x, int k)  /* $2^{k}x$ */
{
    long double w;

    if (k >= 0) w = 2;
    else {  w = 0.5;  k = - k;  }
    while (k) {
        if (k & 1) x *= w;
        w *= w;  k >>= 1;
    }
    return x;
}

long double lexp1(long double x)
{
    int i, k, neg;
    long double a, e, prev;

    k = (int)(x / LOG2 + (x >= 0 ? 0.5 : -0.5));
    x -= k * LOG2;
    if (x >= 0) neg = 0;  else {  neg = 1;  x = -x;  }
    e = 1 + x;  a = x;  i = 2;
    do {
        prev = e;  a *= x / i;  e += a;  i++;
    } while (e != prev);
    if (neg) e = 1 / e;
    return lldexp(e, k);
}

#define N  22  /* 本文参照 (6, 10, 14, 18, 22, 26, \ldots) */
long double lexp(long double x)
{
    int i, k;
    long double x2, w;

    k = (int)(x / LOG2 + (x >= 0 ? 0.5 : -0.5));
    x -= k * LOG2;
    x2 = x * x;  w = x2 / N;
    for (i = N - 4; i >= 6; i -= 4) w = x2 / (w + i);
    return lldexp((2 + w + x) / (2 + w - x), k);
}

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

int main(void)
{
    int i;
    long double x;

    for (i = -10; i <= 10; i++) {
        x = i / 4.0L;
        printf("exp(%5.2Lf * log(2))  %*.*Lf  %*.*Lf\n",
            x, LDBL_DIG + 2, LDBL_DIG, lexp1(LOG2 * x),
               LDBL_DIG + 2, LDBL_DIG, lexp(LOG2 * x));
    }
    return 0;
}
