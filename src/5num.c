/***********************************************************
    5num.c -- 五数要約
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

int cmp(const void *k1, const void *k2)  /* 比較 */
{
    if (*((double *)k1) < *((double *)k2)) return -1;
    if (*((double *)k1) > *((double *)k2)) return  1;
    /* else */                           return  0;
}

void fivenum(int n, double x[])  /* 五数要約 */
{
    int i, j;
    double t;

    qsort(x, n, sizeof(double), cmp);  /* クイックソート */
    for (i = 0; i < 4; i++) {
        t = (n - 1.0) * i / 4.0;  j = (int)t;
        printf("%g ", x[j] + (x[j + 1] - x[j]) * (t - j));
    }
    printf("%g\n", x[n - 1]);
}

#include "statutil.c"
#define NMAX  5000

int main(void)
{
    int n;
    double t;
    static double x[NMAX];

    n = 0;
    while (! readerror(t = getnum(stdin)))
        if (missing(t)) continue;
        else if (n >= NMAX) error("多すぎます");
        else x[n++] = t;
    fivenum(n, x);
    return 0;
}
