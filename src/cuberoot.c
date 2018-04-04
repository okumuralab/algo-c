/***********************************************************
    cuberoot.c -- 立方根
***********************************************************/

double cuberoot(double x)  /* $\sqrt[3]{x}$ */
{
    double s, prev;
    int positive;

    if (x == 0) return 0;
    if (x > 0) positive = 1;  else {  positive = 0;  x = -x;  }
    if (x > 1) s = x;  else s = 1;
    do {
        prev = s;  s = (x / (s * s) + 2 * s) / 3;
    } while (s < prev);
    if (positive) return prev;  else return -prev;
}

double cuberoot2(double x)  /* $\sqrt[3]{x}$ */
{
    double s, t, prev;
    int positive;

    if (x == 0) return 0;
    if (x > 0) positive = 1;  else {  positive = 0;  x = -x;  }
    if (x > 1) s = x;  else s = 1;
    do {
        prev = s;  t = s * s;  s += (x - t * s) / (2 * t + x / s);
    } while (s < prev);
    if (positive) return prev;  else return -prev;
}

long double lcuberoot(long double x)
{
    long double s;

    if (x == 0) return 0;
    s = cuberoot(x);
    return (x / (s * s) + 2 * s) / 3;
}

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

int main(void)
{
    int i;

    for (i = 0; i <= 20; i++)
        printf("%2d  %.*f %.*Lf\n",
            i, DBL_DIG - 1, cuberoot(i),
            LDBL_DIG - 1, lcuberoot(i));
    return 0;
}
