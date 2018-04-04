/***********************************************************
    corrcoef.c -- 相関係数
***********************************************************/
#include <stdio.h>
#include <math.h>

void corrcoef1(int n, float x[], float y[])
{
    int i;
    float sx, sy, sxx, syy, sxy, dx, dy;

    sx = sy = sxx = syy = sxy = 0;
    for (i = 0; i < n; i++) {
        sx += x[i];  sy += y[i];
    }
    sx /= n;  sy /= n;
    for (i = 0; i < n; i++) {
        dx = x[i] - sx;  dy = y[i] - sy;
        sxx += dx * dx;  syy += dy * dy;  sxy += dx * dy;
    }
    sxx = sqrt(sxx / (n - 1));
    syy = sqrt(syy / (n - 1));
    sxy /= (n - 1) * sxx * syy;
    printf("標準偏差 %g %g  相関係数 %g\n", sxx, syy, sxy);
}

void corrcoef2(int n, float x[], float y[])
{
    int i;
    float sx, sy, sxx, syy, sxy;

    sx = sy = sxx = syy = sxy = 0;
    for (i = 0; i < n; i++) {
        sx += x[i];  sy += y[i];
        sxx += x[i] * x[i];
        syy += y[i] * y[i];
        sxy += x[i] * y[i];
    }
    sx /= n;  sxx = (sxx - n * sx * sx) / (n - 1);
    sy /= n;  syy = (syy - n * sy * sy) / (n - 1);
    if (sxx > 0) sxx = sqrt(sxx);  else sxx = 0;
    if (syy > 0) syy = sqrt(syy);  else syy = 0;
    sxy = (sxy - n * sx * sy) / ((n - 1) * sxx * syy);
    printf("標準偏差 %g %g  相関係数 %g\n", sxx, syy, sxy);
}

void corrcoef3(int n, float x[], float y[])
{
    int i;
    float sx, sy, sxx, syy, sxy, dx, dy;

    sx = sy = sxx = syy = sxy = 0;
    for (i = 0; i < n; i++) {
        dx = x[i] - sx;  sx += dx / (i + 1);
        dy = y[i] - sy;  sy += dy / (i + 1);
        sxx += i * dx * dx / (i + 1);
        syy += i * dy * dy / (i + 1);
        sxy += i * dx * dy / (i + 1);
    }
    sxx = sqrt(sxx / (n - 1));
    syy = sqrt(syy / (n - 1));
    sxy /= (n - 1) * sxx * syy;
    printf("標準偏差 %g %g  相関係数 %g\n", sxx, syy, sxy);
}

#include <stdlib.h>
#include "statutil.c"
#define NMAX  1000

int main(void)
{
    int n;
    float t, u;
    static float x[NMAX], y[NMAX];

    n = 0;
    for ( ; ; ) {
        t = getnum(stdin);  u = getnum(stdin);
        if (readerror(t) || readerror(u)) break;
        if (missing(t) || missing(u)) continue;
        if (n >= NMAX) error("多すぎます");
        x[n] = t;  y[n] = u;  n++;
    }
    printf("データの件数 %d\n", n);
    corrcoef1(n, x, y);
    corrcoef2(n, x, y);
    corrcoef3(n, x, y);
    return 0;
}
