/***********************************************************
    meansd2.c -- 平均値・標準偏差
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    int n;
    float x, s1, s2;

    s1 = s2 = n = 0;
    while (scanf("%f", &x) == 1) {
        n++;  s1 += x;  s2 += x * x;
    }
    s1 /= n;                                  /* 平均 */
    s2 = (s2 - n * s1 * s1) / (n - 1);        /* 分散 */
    if (s2 > 0) s2 = sqrt(s2);  else s2 = 0;  /* 標準偏差 */
    printf("個数: %d  平均: %g  標準偏差: %g\n", n, s1, s2);
    return 0;
}
