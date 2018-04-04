/***********************************************************
    gamma.c -- ガンマ関数
            -- ベータ関数
***********************************************************/
#include <math.h>
#define PI      3.14159265358979324  /* $\pi$ */
#define LOG_2PI 1.83787706640934548  /* $\log 2\pi$ */
#define N       8

#define B0  1                 /* 以下はBernoulli数 */
#define B1  (-1.0 / 2.0)
#define B2  ( 1.0 / 6.0)
#define B4  (-1.0 / 30.0)
#define B6  ( 1.0 / 42.0)
#define B8  (-1.0 / 30.0)
#define B10 ( 5.0 / 66.0)
#define B12 (-691.0 / 2730.0)
#define B14 ( 7.0 / 6.0)
#define B16 (-3617.0 / 510.0)

double loggamma(double x)  /* ガンマ関数の対数 */
{
    double v, w;

    v = 1;
    while (x < N) {  v *= x;  x++;  }
    w = 1 / (x * x);
    return ((((((((B16 / (16 * 15))  * w + (B14 / (14 * 13))) * w
                + (B12 / (12 * 11))) * w + (B10 / (10 *  9))) * w
                + (B8  / ( 8 *  7))) * w + (B6  / ( 6 *  5))) * w
                + (B4  / ( 4 *  3))) * w + (B2  / ( 2 *  1))) / x
                + 0.5 * LOG_2PI - log(v) - x + (x - 0.5) * log(x);
}

double gamma(double x)  /* ガンマ関数 */
{
    if (x < 0)
        return PI / (sin(PI * x) * exp(loggamma(1 - x)));
    return exp(loggamma(x));
}

double beta(double x, double y)  /* ベータ関数 */
{
    return exp(loggamma(x) + loggamma(y) - loggamma(x + y));
}

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

int main(void)
{
    double x;

    printf("  x       Gamma(x)\n");
    for (x = -5.5; x <= 0.51; x += 1.0)
        printf("%4.1f  % .*g\n", x, DBL_DIG, gamma(x));
    for (x = 1; x <= 5.1; x += 1.0)
        printf("%4.1f  % .*g\n", x, DBL_DIG, gamma(x));
    for (x = 10; x <= 30.1; x += 5.0)
        printf("%4.1f  % .*g\n", x, DBL_DIG, gamma(x));
    return 0;
}
