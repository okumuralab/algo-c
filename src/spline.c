/***********************************************************
    spline.c -- スプライン補間
***********************************************************/
/* 非周期関数用 */

#define  N  5
double x[N] = {   0,      10,     20,     30,     40   },
       y[N] = { 610.66, 1227.4, 2338.1, 4244.9, 7381.2 },
       z[N];

void maketable(double x[], double y[], double z[])
{
    int i;
    double t;
    static double h[N], d[N];

    z[0] = 0;  z[N - 1] = 0;  /* 両端点での y''(x) / 6 */
    for (i = 0; i < N - 1; i++) {
        h[i    ] =  x[i + 1] - x[i];
        d[i + 1] = (y[i + 1] - y[i]) / h[i];
    }
    z[1] = d[2] - d[1] - h[0] * z[0];
    d[1] = 2 * (x[2] - x[0]);
    for (i = 1; i < N - 2; i++) {
        t = h[i] / d[i];
        z[i + 1] = d[i + 2] - d[i + 1] - z[i] * t;
        d[i + 1] = 2 * (x[i + 2] - x[i]) - h[i] * t;
    }
    z[N - 2] -= h[N - 2] * z[N - 1];
    for (i = N - 2; i > 0; i--)
        z[i] = (z[i] - h[i] * z[i + 1]) / d[i];
}

double spline(double t, double x[], double y[], double z[])
{
    int i, j, k;
    double d, h;

    i = 0;  j = N - 1;
    while (i < j) {
        k = (i + j) / 2;
        if (x[k] < t) i = k + 1;  else j = k;
    }
    if (i > 0) i--;
    h = x[i + 1] - x[i];  d = t - x[i];
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
    for (i = 10; i <= 30; i++)
        printf("%3d %6.1f\n", i, spline(i, x, y, z));
    return 0;
}
