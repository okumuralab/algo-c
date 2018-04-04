/***********************************************************
    meansd1.c -- 平均値・標準偏差
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NMAX 1000

int main(void)
{
    int i, n;
    float x, s1, s2;
    static float a[NMAX];

    s1 = s2 = n = 0;
    while (scanf("%f", &x) == 1) {
        if (n >= NMAX) return 1;
        a[n++] = x;  s1 += x;
    }
    s1 /= n; /* 平均 */
    for (i = 0; i < n; i++) {
        x = a[i] - s1;  s2 += x * x;
    }
    s2 = sqrt(s2 / (n - 1));  /* 標準偏差 */
    printf("個数: %d  平均: %g  標準偏差: %g\n", n, s1, s2);
    return 0;
}
