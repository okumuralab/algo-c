/***********************************************************
    binomial.c -- 2項分布
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void error(char *s)
{
    printf("%s\n", s);
    exit(1);
}

int main(void)
{
    int k, n;
    double p, q, s, t;

    printf("n, p? ");  scanf("%d%lf", &n, &p);
    q = 1 - p;  s = t = pow(q, n);
    if (s == 0) error("n か p が大きすぎます");
    for (k = 0; k < n; k++) {
        printf("%4d %7.4f\n", k, s);
        t *= (n - k) * p / ((k + 1) * q);
        s += t;
    }
    printf("%4d %7.4f\n", n, s);
    return 0;
}
