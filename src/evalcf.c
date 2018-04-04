/**************************************************************
    evalcf.c -- 連分数
**************************************************************/
#include <stdio.h>   /* printf */
#include <float.h>   /* DBL_MAX */

double cf_ascend(int n, double c[], double b[])
{
    double f;

    f = 0;
    while (n > 0) {
        f = c[n] / (b[n] + f);  n--;
    }
    return f + b[0];
}

double cf_descend(int n, double c[], double b[])
{
    int i;
    double p1, q1, p2, q2, t;

    p1 = 1;  q1 = 0;  p2 = b[0];  q2 = 1;
    printf("  0: %g\n", p2);
    for (i = 1; i <= n; i++) {
        t = p1 * c[i] + p2 * b[i];  p1 = p2;  p2 = t;
        t = q1 * c[i] + q2 * b[i];  q1 = q2;  q2 = t;
        if (q2 != 0) {
            p1 /= q2;  q1 /= q2;  p2 /= q2;  q2 = 1;
            printf("%3d: %g\n", i, p2);
        } else
            printf("%3d: 無限大\n", i);
    }
    if (q2 != 0) return p2;  else return DBL_MAX;
}

#include <stdlib.h>

#define N 15

int main(void)  /* tan(x) */
{
    int i;
    double x, t, c[N + 1], b[N + 1];

    printf("x = ");  scanf("%lf", &x);
    c[1] = x;  b[0] = 0;
    for (i = 2; i <= N; i++) c[i] = -x * x;
    for (i = 1; i <= N; i++) b[i] = 2 * i - 1;
    printf("tan(x) = %g\n", cf_ascend(N, c, b));
    t = cf_descend(N, c, b);
    printf("tan(x) = %g\n", t);
    return 0;
}
