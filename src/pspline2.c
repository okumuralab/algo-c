/***********************************************************
    pspline2.c -- スプライン補間
***********************************************************/
/* 閉曲線 */

#include <math.h>
#define  N  5
double x[N + 1] = { 1, 2, 4, 6, 5, 1 },
       y[N + 1] = { 1, 3, 4, 3, 1, 1 },
       p[N + 1], a[N + 1], b[N + 1];

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

void maketable2(double p[], double x[], double y[],
        double a[], double b[])
{
    int i;
    double t1, t2;

    p[0] = 0;
    for (i = 1; i <= N; i++) {
        t1 = x[i] - x[i - 1];
        t2 = y[i] - y[i - 1];
        p[i] = p[i - 1] + sqrt(t1 * t1 + t2 * t2);
    }
    for (i = 1; i <= N; i++) p[i] /= p[N];
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
