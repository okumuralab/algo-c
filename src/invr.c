/***********************************************************
    invr.c -- 逆行列
***********************************************************/
#include "matutil.c"

void invr(int n, matrix x)  /* 上三角行列の逆行列 */
{
    int i, j, k;
    double s;

    for (k = 0; k < n; k++) {
        x[k][k] = 1 / x[k][k];
        for (j = k - 1; j >= 0; j--) {
            s = 0;
            for (i = j + 1; i <= k; i++)
                s -= x[i][j] * x[i][k];
            x[j][k] = s * x[j][j];
        }
    }
}

/************** 以下はテスト用 *************/

#include <math.h>
#include <limits.h>

double rnd(void)  /* 乱数  0 < rnd() < 1 */
{
    static unsigned long seed = 123456789UL;  /* 奇数 */

    return (seed *= 69069UL) / (ULONG_MAX + 1.0);
}

int main(void)
{
    int i, j, k, n;
    matrix r, r_inv,rr;
    double s, t;

    printf("n = ");  scanf("%d", &n);
    r = new_matrix(n, n);  
    r_inv = new_matrix(n, n);
    rr = new_matrix(n, n);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            r[i][j] = r_inv[i][j] = 0;
    for (i = 0; i < n; i++)
        for (j = i; j < n; j++)
            r[i][j] = r_inv[j][i] = rnd() - rnd();

    printf("$R$\n");
    matprint(r, n, 5, "% -14g");

    invr(n, r_inv);
    for (i = 0; i < n; i++)
        for (j = 0; j < i; j++)
            r_inv[i][j] = 0;
    printf("$R^{-1}$\n");
    matprint(r_inv, n, 5, "% -14g");

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            s = 0;
            for (k = 0; k < n; k++)
                s += r_inv[i][k] * r[k][j];
            rr[i][j] = s;
        }

    printf("$R^{-1} * R$\n");
    matprint(rr, n, 5, "% -14g");

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            s = 0;
            for (k = 0; k < n; k++)
                s += r[i][k] * r_inv[k][j];
            rr[i][j] = s;
        }

    printf("$R * R^{-1}$\n");
    matprint(rr, n, 5, "% -14g");

    t = 0;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            s = (i == j);
            for (k = 0; k < n; k++)
                s -= r[i][k] * r_inv[k][j];
            t += s * s;
        }
    printf("$R R^{-1}$ の成分の二乗平均誤差 %g\n",
    sqrt(t / (n * n)));
    t = 0;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            s = (i == j);
            for (k = 0; k < n; k++)
                s -= r_inv[i][k] * r[k][j];
            t += s * s;
        }
    printf("$R^{-1} R$ の成分の二乗平均誤差 %g\n",
    sqrt(t / (n * n)));
    return 0;
}
