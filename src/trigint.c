/**************************************************************
    trigint.c -- 三角関数による補間
**************************************************************/
#include <math.h>
#define PI  3.141592653589793238
#define  N  10  /* 点の数 */
double y[N] = {3,5,6,8,9,12,15,19,10,5}, /* 各点での y 座標 */
       a[N];

void maketable(void)
{
    int i, j;
    double s, t;

    s = 0;
    for (j = 0; j < N; j++) s += y[j];
    a[0] = s / N;
    for (i = 2; i < N; i += 2) {
        t = i * PI / N;
        s = 0;
        for (j = 0; j < N; j++) s += y[j] * cos(t * j);
        a[i - 1] = 2 * s / N;
        s = 0;
        for (j = 0; j < N; j++) s += y[j] * sin(t * j);
        a[i] = 2 * s / N;
    }
    if (i == N) {
        s = 0;  t = i * PI / N;
        for (j = 0; j < N; j++) s += y[j] * cos(t * j);
        a[i - 1] = s / N;
    }
}

double trigint(double t)
{
    int i;
    double s;

    s = a[0];
    for (i = 2; i < N; i += 2)
        s += a[i-1] * cos((i / 2) * t) + a[i] * sin((i / 2) * t);
    if (i == N)
        s += a[i-1] * cos((i / 2) * t);
    return s;
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i;

    maketable();
    for (i = 0; i <= 2 * N; i++)
        printf("%2dpi/%d %6.2f\n", i, N, trigint(i * PI / N));
    return 0;
}
