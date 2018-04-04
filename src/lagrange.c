/***********************************************************
    lagrange.c -- Lagrange (ラグランジュ) 補間
***********************************************************/
#define  N  5                                              /* データ点の数 */
double x[N] = {   0,      10,     20,     30,     40   },
       y[N] = { 610.66, 1227.4, 2338.1, 4244.9, 7381.2 };  /* データ */

double lagrange(double t)
{
    int i, j;
    double sum, prod;

    sum = 0;
    for (i = 0; i < N; i++) {
        prod = y[i];
        for (j = 0; j < N; j++)
            if (j != i) prod *= (t - x[j]) / (x[i] - x[j]);
        sum += prod;
    }
    return sum;
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i;

    for (i = 10; i <= 30; i++)
        printf("%3d %6.1f\n", i, lagrange(i));
    return 0;
}
