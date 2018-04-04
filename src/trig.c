/***********************************************************
    trig.c -- 三角関数
***********************************************************/
#include <stdio.h>
#include <math.h>
#include <limits.h>
#define PI 3.1415926535897932384626433832795
#define N  19  /* 奇数 (本文参照) */
#define D  4.4544551033807686783083602485579e-6

long double lfabs(long double x)  /* 絶対値 */
{
    if (x >= 0) return x;  else return -x;
}

static long double ur_tan(long double x, int *k)  /* tan(x)の元 */
{
    int i;
    long double t, x2;

    *k = (int)(x / (PI / 2) + (x >= 0 ? 0.5 : -0.5));
    x = +(x - (3217.0 / 2048) * *k) + D * *k;
    x2 = x * x;  t = 0;
    for (i = N; i >= 3; i -= 2) t = x2 / (i - t);
    return x / (1 - t);
}

long double ltan(long double x)  /* tan(x) */
{
    int k;
    long double t;

    t = ur_tan(x, &k);
    if (k % 2 == 0) return t;
    if (t != 0)     return -1 / t;
    /* overflow */  return HUGE_VAL;
}

long double lsin(long double x)  /* sin(x) */
{
    int k;
    long double t;

    t = ur_tan(x / 2, &k);
    t = 2 * t / (1 + t * t);
    if (k % 2 == 0) return  t;
    /* else */      return -t;
}

long double lcos(long double x)  /* cos(x) */
{
    return lsin(PI / 2 - lfabs(x));
}

long double lcos1(long double x)  /* 1 - cos(x) */
{
    int k;
    long double t;

    t = ur_tan(lfabs(x / 2), &k);  t *= t;
    if (k % 2 == 0) return 2 * t / (1 + t);
    /* else */      return 2     / (1 + t);
}

#include <stdlib.h>
#define EPS 0.000001

int main(void)  /* テスト用 */
{
    int i, err;
    long double x, s, c, c1, t;

    printf("x(deg) %12s %17s %17s %17s\n",
        "sin(x)", "cos(x)", "1-cos(x)", "tan(x)");
    for (i = -720; i <= 720; i += 15) {
        err = 0;
        x = i * (PI / 180);
        s = lsin(x);  c = lcos(x);  c1 = lcos1(x);
        if (fabs((double)s - sin(x)) > EPS
         || fabs((double)c - cos(x)) > EPS
         || fabs((double)c + (double)c1 - 1) > EPS) err = 1;
        printf("%4d %17.14Lf %17.14Lf %17.14Lf", i, s, c, c1);
        if ((i + 90) % 180 != 0) {
            t = ltan(x);
            if (fabs((double)t - tan(x)) > EPS) err = 1;
            printf(" %17.14Lf", t);
        }
        printf("\n");
        if (err) printf("|error| > %g\n", EPS);
    }
    return 0;
}
