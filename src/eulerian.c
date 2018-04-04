/***********************************************************
    eulerian.c -- Euler (オイラー) の数
***********************************************************/

int Eulerian(int n, int k)  /* ${\tt n} \ge 0$ */
{
    if (k == 0) return 1;
    if (k < 0 || k >= n) return 0;
    return (k + 1) * Eulerian(n - 1, k)
         + (n - k) * Eulerian(n - 1, k - 1);
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n, k;

    printf("  k");
    for (k = 0; k <= 8; k++) printf("%6d", k);
    printf("\nn  ");
    for (k = 0; k <= 8; k++) printf("------");
    printf("\n");
    for (n = 0; n <= 8; n++) {
        printf("%d |", n);
        for (k = 0; k <= n; k++) printf("%6d", Eulerian(n, k));
        printf("\n");
    }
    return 0;
}
