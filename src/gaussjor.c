/***********************************************************
    gaussjor.c -- Gauss (ガウス)--Jordan (ジョルダン) 法
***********************************************************/
#include "matutil.c"

void gaussjordan(int n, matrix a)
{
    int i, j, k;

    for (k = 0; k < n; k++) {
        for (j = k + 1; j <= n; j++) a[k][j] /= a[k][k];
        for (i = 0; i < n; i++)
            if (i != k)
                for (j = k + 1; j <= n; j++)
                    a[i][j] -= a[i][k] * a[k][j];
    }
}

#include <limits.h>

double rnd(void)  /* 乱数  0 < rnd() < 1 */
{
    static unsigned long seed = 123456789UL;  /* 奇数 */

    return (seed *= 69069UL) / (ULONG_MAX + 1.0);
}

int main(void)
{
    int i, j, n;
    matrix a, b;
    double s;

    printf("n = ");  scanf("%d", &n);
    a = new_matrix(n, n + 1);
    b = new_matrix(n, n + 1);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            a[i][j] = b[i][j] = rnd() - rnd();
    for (i = 0; i < n; i++)
        a[i][n] = b[i][n] = rnd() - rnd();
    printf("係数行列 (右辺も含む)\n");
    matprint(a, n + 1, 10, "%7.3f");
    gaussjordan(n, a);
    printf("解と, 解を代入したときの両辺の差\n");
    for (i = 0; i < n; i++) {
        s = b[i][n];
        for (j = 0; j < n; j++) s -= b[i][j] * a[j][n];
        printf("%4d: %12.7f %12.7f\n", i, a[i][n], s);
    }
    return 0;
}
