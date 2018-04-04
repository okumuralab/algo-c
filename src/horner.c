/***********************************************************
    horner.c -- Horner (ホーナー) 法
***********************************************************/

double horner(int n, double a[], double x)
{
    int i;
    double p;

    p = a[n];
    for (i = n - 1; i >= 0; i--) p = p * x + a[i];
    return p;
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    static double a[5] = { 1, 2, 3, 4, 5 };

    printf("f(2) = %g\n", horner(4, a, 2));
    return 0;
}
