/***********************************************************
    sqrt.c -- 平方根
***********************************************************/
#include <stdio.h>

double mysqrt(double x)  /* 自家版 $\sqrt{x}$ */
{
    double s, last;

    if (x > 0) {
        if (x > 1) s = x;  else s = 1;
        do {
            last = s;  s = (x / s + s) / 2;
        } while (s < last);
        return last;
    }
    if (x != 0) fprintf(stderr, "mysqrt: domain error\n");
    return 0;
}

long double lsqrt(long double x)  /* {\tt long double}版 $\sqrt{x}$ */
{
    long double s;

    if (x == 0) return 0;
    s = mysqrt(x);
    return (x / s + s) / 2;
}

#include <stdlib.h>
#include <float.h>

int main(void)
{
    int i;

    for (i = 0; i <= 20; i++)
        printf("%2d  %.*f %.*Lf\n",
            i, DBL_DIG - 1, mysqrt(i),
            LDBL_DIG - 1, lsqrt(i));
    return 0;
}
