/***********************************************************
    log.c -- 対数
***********************************************************/
#include <stdio.h>
#include <math.h>
#define LOG2  0.693147180559945309417232121458L /* log(2) */
#define SQRT2 1.41421356237309504880168872421L /* sqrt(2) */

long double llog(long double x)  /* 自然対数 (級数展開版) */
{
    int i, k;
    long double x2, s, last;

    if (x <= 0) {
        fprintf(stderr, "llog(x): x <= 0\n");  return 0;
    }
    frexp(x / SQRT2, &k);  /* 1/2<=(x/SQRT2)/pow(2,k)<1 */
    x /= ldexp(1, k);      /* x = x / pow(2,k) */
    x = (x - 1) / (x + 1);  x2 = x * x;  i = 1;  s = x;
    do {
        x *= x2;  i += 2;  last = s;  s += x / i;
    } while (last != s);
    return LOG2 * k + 2 * s;
}

#define N  9  /* 本文参照 */
long double llog_cf(long double x)  /* 自然対数 (連分数版) */
{
    int i, k;
    long double s;

    if (x <= 0) {
        fprintf(stderr, "llog_cf(x): x <= 0\n");  return 0;
    }
    frexp(x / SQRT2, &k);  /* 1/2<=(x/SQRT2)/pow(2,k)<1 */
    x /= ldexp(1, k);      /* x = x / pow(2,k) */
    x--;  s = 0;
    for (i = N; i >= 1; i--)
        s = i * x / (2 + i * x / (2 * i + 1 + s));
    return LOG2 * k + x / (1 + s);
}

#include <stdlib.h>
#include <float.h>

int main(void)
{
    int i;
    long double x;

    printf("%5s  %-*s  %s\n",
        "x", LDBL_DIG + 3, "llog(x)", "llog_cf(x)");
    for (i = 1; i <= 20; i++) {
        x = i / 5.0;
        printf("%5.1Lf  %*.*Lf  %*.*Lf\n",
            x, LDBL_DIG + 3, LDBL_DIG, llog(x),
               LDBL_DIG + 3, LDBL_DIG, llog_cf(x));
    }
    return 0;
}
