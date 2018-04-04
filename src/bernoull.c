/***********************************************************
    bernoull.c -- Bernoulli (ベルヌーイ) 数
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

double gcd(double x, double y)  /* 最大公約数 */
{
    double t;

    while (y != 0) {  t = fmod(x, y);  x = y;  y = t;  }
    return x;
}

#define  N 40

int main(void)
{
    int i, n;
    double q, b1, b2, d;
    static double t[N + 1];

    q = 1;
    t[1] = 1;
    for (n = 2; n <= N; n++) {
        for (i = 1; i < n; i++) t[i - 1] = i * t[i];
        t[n - 1] = 0;
        for (i = n; i >= 2; i--) t[i] += t[i - 2];
        if (n % 2 == 0) {
            q *= 4;
            b1 = n * t[0];  b2 = q * (q - 1);
            if (b1 < 1 / DBL_EPSILON && b2 < 1 / DBL_EPSILON) {
                d = gcd(b1, b2);  b1 /= d;  b2 /= d;
                printf("|B(%2d)| = %.0f/%.0f\n", n, b1, b2);
            } else
                printf("|B(%2d)| = %g\n", n, b1 / b2);
        }
    }
    return 0;
}
