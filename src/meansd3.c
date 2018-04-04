/***********************************************************
    meansd3.c -- 平均値・標準偏差
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
        n++;                        /* 個数 */
        x -= s1;                    /* 仮平均との差 */
        s1 += x / n;                /* 平均 */
        s2 += (n - 1) * x * x / n;  /* 平方和 */
    }
    s2 = sqrt(s2 / (n - 1));  /* 標準偏差 */
    printf("個数: %d  平均: %g  標準偏差: %g\n", n, s1, s2);
    return 0;
}
