/***********************************************************
    spline2.c -- スプライン補間
***********************************************************/
/* 開曲線 */

#include <math.h>
#define  N  5
double x[N] = { 1, 2, 4, 6, 5 },
       y[N] = { 1, 3, 4, 3, 1 },
       p[N], a[N], b[N];

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

void maketable2(double p[], double x[], double y[],
        double a[], double b[])
{
    int i;
    double t1, t2;

    p[0] = 0;
    for (i = 1; i < N; i++) {
        t1 = x[i] - x[i - 1];
        t2 = y[i] - y[i - 1];
        p[i] = p[i - 1] + sqrt(t1 * t1 + t2 * t2);
    }
    for (i = 1; i < N; i++) p[i] /= p[N - 1];
    maketable(p, x, a);
    maketable(p, y, b);
}

void spline2(double t, double *px, double *py,
        double p[], double x[], double  y[], 
        double a[], double b[])
{
    *px = spline(t, p, x, a);
    *py = spline(t, p, y, b);
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i;
    double u, v;

    maketable2(p, x, y, a, b);
    for (i = 0; i <= 20; i++) {
        spline2(0.05 * i, &u, &v, p, x, y, a, b);
        printf("%5.2f %5.2f\n", u, v);
    }
    return 0;
}
