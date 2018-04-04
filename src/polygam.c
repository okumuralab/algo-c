/***********************************************************
    polygam.c -- プサイ関数, ポリガンマ関数
***********************************************************/
#include <math.h>
#define N  8

#define B0  1  /* 以下はBernoulli数 */
#define B1  (-1.0 / 2.0)
#define B2  ( 1.0 / 6.0)
#define B4  (-1.0 / 30.0)
#define B6  ( 1.0 / 42.0)
#define B8  (-1.0 / 30.0)
#define B10 ( 5.0 / 66.0)
#define B12 (-691.0 / 2730.0)
#define B14 ( 7.0 / 6.0)
#define B16 (-3617.0 / 510.0)

double psi(double x)  /* $\psi(x)$ */
{
    double v, w;

    v = 0;
    while (x < N) {  v += 1 / x;  x++;  }
    w = 1 / (x * x);
    v += ((((((((B16 / 16)  * w + (B14 / 14)) * w
              + (B12 / 12)) * w + (B10 / 10)) * w
              + (B8  /  8)) * w + (B6  /  6)) * w
              + (B4  /  4)) * w + (B2  /  2)) * w + 0.5 / x;
    return log(x) - v;
}

double polygamma(int n, double x)  /* $\psi^{(n)}(x)$ */
{
    int k;
    double t, u, v, w;

    u = 1;
    for (k = 1 - n; k < 0; k++)
        u *= k;  /* $u = (-1)^{n-1}(n-1)!$ */
    v = 0;
    while (x < N) {  v += 1 / pow(x, n + 1);  x++;  }
    w = x * x;
    t = (((((((B16
        * (n + 15.0) * (n + 14) / (16 * 15 * w) + B14)
        * (n + 13.0) * (n + 12) / (14 * 13 * w) + B12)
        * (n + 11.0) * (n + 10) / (12 * 11 * w) + B10)
        * (n +  9.0) * (n +  8) / (10 *  9 * w) + B8)
        * (n +  7.0) * (n +  6) / ( 8 *  7 * w) + B6)
        * (n +  5.0) * (n +  4) / ( 6 *  5 * w) + B4)
        * (n +  3.0) * (n +  2) / ( 4 *  3 * w) + B2)
        * (n +  1.0) *  n       / ( 2 *  1 * w)
        + 0.5 * n / x + 1;
    return u * (t / pow(x, n) + n * v);
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    double x;

    printf("  x       %-22s %-22s %-22s\n",
        "psi(x)", "psi'(x)", "psi''(x)");
    for (x = -5.5; x <= 0.5; x++)
        printf("%4.1f  % -22.15g % -22.15g % -22.15g\n",
            x, psi(x), polygamma(1, x), polygamma(2, x));
    for (x = 1; x <= 5; x++)
        printf("%4.1f  % -22.15g % -22.15g % -22.15g\n",
            x, psi(x), polygamma(1, x), polygamma(2, x));
    for (x = 10; x <= 40; x += 10)
        printf("%4.1f  % -22.15g % -22.15g % -22.15g\n",
            x, psi(x), polygamma(1, x), polygamma(2, x));
    printf("\n  x       %-22s %-22s %-22s\n",
        "psi3(x)", "psi4(x)", "psi5(x)");
    for (x = -5.5; x <= 0.5; x++)
        printf("%4.1f  % -22.15g % -22.15g % -22.15g\n",
            x, polygamma(3, x), polygamma(4, x), polygamma(5, x));
    for (x = 1; x <= 5; x++)
        printf("%4.1f  % -22.15g % -22.15g % -22.15g\n",
            x, polygamma(3, x), polygamma(4, x), polygamma(5, x));
    for (x = 10; x <= 40; x += 10)
        printf("%4.1f  % -22.15g % -22.15g % -22.15g\n",
            x, polygamma(3, x), polygamma(4, x), polygamma(5, x));
    return 0;
}
