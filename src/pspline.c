/***********************************************************
    pspline.c -- スプライン補間
***********************************************************/
/* 周期関数用 */

#define  N  10
double x[N + 1] = {1,2,3,5,6,7,9,10,12,13,15},
       y[N + 1] = {3,5,6,8,9,12,15,19,10,5,3},
       z[N + 1];

void maketable(double x[], double y[], double z[])
{
    int i;
    double t;
    static double h[N + 1], d[N + 1], w[N + 1];

    for (i = 0; i < N; i++) {
        h[i] = x[i + 1] - x[i];
        w[i] = (y[i + 1] - y[i]) / h[i];
    }
    w[N] = w[0];
    for (i = 1; i < N; i++) d[i] = 2 * (x[i + 1] - x[i - 1]);
    d[N] = 2 * (h[N - 1] + h[0]);
    for (i = 1; i <= N; i++) z[i] = w[i] - w[i - 1];
    w[1] = h[0];  w[N - 1] = h[N - 1];  w[N] = d[N];
    for (i = 2; i < N - 1; i++) w[i] = 0;
    for (i = 1; i < N; i++) {
        t = h[i] / d[i];
        z[i + 1] = z[i + 1] - z[i] * t;
        d[i + 1] = d[i + 1] - h[i] * t;
        w[i + 1] = w[i + 1] - w[i] * t;
    }
    w[0] = w[N];  z[0] = z[N];
    for (i = N - 2; i >= 0; i--) {
        t = h[i] / d[i + 1];
        z[i] = z[i] - z[i + 1] * t;
        w[i] = w[i] - w[i + 1] * t;
    }
    t = z[0] / w[0];  z[0] = t;  z[N] = t;
    for (i = 1; i < N; i++)
        z[i] = (z[i] - w[i] * t) / d[i];
}

double spline(double t, double x[], double y[], double z[])
{
    int i, j, k;
    double d, h, period;

    period = x[N] - x[0];
    while (t > x[N]) t -= period;
    while (t < x[0]) t += period;
    i = 0;  j = N;
    while (i < j) {
        k = (i + j) / 2;
        if (x[k] < t) i = k + 1;  else j = k;
    }
    if (i > 0) i--;
    h = x[i + 1] - x[i];
    d = t - x[i];
    return (((z[i + 1] - z[i]) * d / h + z[i] * 3) * d
        + ((y[i + 1] - y[i]) / h
        - (z[i] * 2 + z[i + 1]) * h)) * d + y[i];
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i;

    maketable(x, y, z);
    for (i = -5; i <= 25; i++)
        printf("%3d %6.2f\n", i, spline(i, x, y, z));
    return 0;
}
