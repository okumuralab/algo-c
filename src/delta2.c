/***********************************************************
    delta2.c -- Aitken (エイトケン) の $\Delta^2$ 法
***********************************************************/
#include <stdio.h>

void delta2(int n, double a[])
{
    int i, j;
    double p, q;

    for (j = 0; j < n; j++) {
        for (i = j; i >= 2; i -= 2) {
            q = a[i] - 2 * a[i - 1] + a[i - 2];
            if (q == 0) {
                printf("収束しました.\n");  return;
            }
            p = a[i] - a[i - 1];
            a[i - 2] = a[i] - p * p / q;
        }
        printf("%3d: % .14e\n", j, a[i]);
    }
}

#include <stdlib.h>
#define N 50

main()
{
    int i;
    double t;
    static double a[N];

    /* Euler's series $1 - 1!x + 2!x^2 - 3!x^3 + \cdots$ at $x = 0.1$ */
    a[0] = t = 1;
    for (i = 1; i < N; i++) {
        t *= i * (-0.1);  a[i] = a[i - 1] + t;
        printf("%2d % .14e\n", i, a[i]);
    }
    delta2(N, a);
    return 0;
}
