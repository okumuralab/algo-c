/***********************************************************
    matinv.c -- 逆行列
***********************************************************/
#include "matutil.c"  /* 行列操作用小道具集 */
#include <math.h>

double lu(int n, matrix a, int *ip)  /* LU分解 */
{
    int i, j, k, ii, ik;
    double t, u, det;
    vector weight;

    weight = new_vector(n);    /* weight[0..n-1] の記憶領域確保 */
    det = 0;                   /* 行列式 */
    for (k = 0; k < n; k++) {  /* 各行について */
        ip[k] = k;             /* 行交換情報の初期値 */
        u = 0;                 /* その行の絶対値最大の要素を求める */
        for (j = 0; j < n; j++) {
            t = fabs(a[k][j]);  if (t > u) u = t;
        }
        if (u == 0) goto EXIT; /* 0 なら行列はLU分解できない */
        weight[k] = 1 / u;     /* 最大絶対値の逆数 */
    }
    det = 1;                   /* 行列式の初期値 */
    for (k = 0; k < n; k++) {  /* 各行について */
        u = -1;
        for (i = k; i < n; i++) {  /* より下の各行について */
            ii = ip[i];            /* 重み×絶対値 が最大の行を見つける */
            t = fabs(a[ii][k]) * weight[ii];
            if (t > u) {  u = t;  j = i;  }
        }
        ik = ip[j];
        if (j != k) {
            ip[j] = ip[k];  ip[k] = ik;  /* 行番号を交換 */
            det = -det;  /* 行を交換すれば行列式の符号が変わる */
        }
        u = a[ik][k];  det *= u;  /* 対角成分 */
        if (u == 0) goto EXIT;    /* 0 なら行列はLU分解できない */
        for (i = k + 1; i < n; i++) {  /* Gauss消去法 */
            ii = ip[i];
            t = (a[ii][k] /= u);
            for (j = k + 1; j < n; j++)
                a[ii][j] -= t * a[ik][j];
        }
    }
EXIT:
    free_vector(weight);  /* 記憶領域を解放 */
    return det;           /* 戻り値は行列式 */
}

double matinv(int n, matrix a, matrix a_inv)
{
    int i, j, k, ii;
    double t, det;
    int *ip;   /* 行交換の情報 */

    ip = malloc(sizeof(int) * n);
    if (ip == NULL) error("記憶領域不足");
    det = lu(n, a, ip);
    if (det != 0)
        for (k = 0; k < n; k++) {
            for (i = 0; i < n; i++) {
                ii = ip[i];  t = (ii == k);
                for (j = 0; j < i; j++)
                    t -= a[ii][j] * a_inv[j][k];
                a_inv[i][k] = t;
            }
            for (i = n - 1; i >= 0; i--) {
                t = a_inv[i][k];  ii = ip[i];
                for (j = i + 1; j < n; j++)
                    t -= a[ii][j] * a_inv[j][k];
                a_inv[i][k] = t / a[ii][i];
            }
        }
    free(ip);
    return det;
}

/************* 以下はテスト用 ****************/

#include <limits.h>

double rnd(void)  /* 乱数  0 < rnd() < 1 */
{
    static unsigned long seed = 123456789UL;  /* 奇数 */

    return (seed *= 69069UL) / (ULONG_MAX + 1.0);
}

int main(void)
{
    int i, j, k, n;
    matrix a, asave, a_inv;
    double s, t;

    printf("n = ");  scanf("%d", &n);
    a = new_matrix(n, n);  asave = new_matrix(n, n);
    a_inv = new_matrix(n, n);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            a[i][j] = asave[i][j] = rnd() - rnd();
    printf("A\n");
    matprint(a, n, 7, "%10.6f");
    s = matinv(n, a, a_inv);
    printf("行列式 = %g\n", s);
    printf("A^{-1}\n");
    matprint(a_inv, n, 7, "%10.6f");
    t = 0;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            s = (i == j);
            for (k = 0; k < n; k++)
                s -= asave[i][k] * a_inv[k][j];
            t += s * s;
        }
    printf("A A^{-1} の成分の二乗平均誤差 %g\n",
        sqrt(t / (n * n)));
    t = 0;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            s = (i == j);
            for (k = 0; k < n; k++)
                s -= a_inv[i][k] * asave[k][j];
            t += s * s;
        }
    printf("A^{-1} A の成分の二乗平均誤差 %g\n",
        sqrt(t / (n * n)));
    return 0;
}
