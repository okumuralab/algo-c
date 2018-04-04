/***********************************************************
    lu.c -- LU分解
***********************************************************/
#include "matutil.c"  /* 行列操作の小道具集 */
#include <math.h>

double lu(int n, matrix a, int *ip)
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

void solve(int n, matrix a, vector b, int *ip, vector x)
{
    int i, j, ii;
    double t;

    for (i = 0; i < n; i++) {       /* Gauss消去法の残り */
        ii = ip[i];  t = b[ii];
        for (j = 0; j < i; j++) t -= a[ii][j] * x[j];
        x[i] = t;
    }
    for (i = n - 1; i >= 0; i--) {  /* 後退代入 */
        t = x[i];  ii = ip[i];
        for (j = i + 1; j < n; j++) t -= a[ii][j] * x[j];
        x[i] = t / a[ii][i];
    }
}

double gauss(int n, matrix a, vector b, vector x)
{
    double det;  /* 行列式 */
    int *ip;     /* 行交換の情報 */

    ip = malloc(sizeof(int) * n);         /* 記憶領域確保 */
    if (ip == NULL) error("記憶領域不足");
    det = lu(n, a, ip);                   /* LU分解 */
    if (det != 0) solve(n, a, b, ip, x);  /* LU分解の結果を使って連立方程式を解く */
    free(ip);                             /* 記憶領域の解放 */
    return det;                           /* 戻り値は行列式 */
}

/********** 以下はテスト用 **********/

#include <limits.h>

double rnd(void)  /* 乱数  0 < rnd() < 1 */
{
    static unsigned long seed = 123456789UL;  /* 奇数 */

    return (seed *= 69069UL) / (ULONG_MAX + 1.0);
}

int main(void)
{
    int i, j, n;
    matrix a, asave;
    vector b, bsave, x;
    double s, det;

    printf("n = ");  scanf("%d", &n);  /* 行列の次数を入力 */
    a = new_matrix(n, n);  asave = new_matrix(n, n);
    b = new_vector(n);  bsave = new_vector(n);
    x = new_vector(n);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            a[i][j] = asave[i][j] = rnd() - rnd();
    printf("係数行列\n");  matprint(a, n, 10, "%7.3f");
    for (i = 0; i < n; i++)
        b[i] = bsave[i] = rnd() - rnd();
    printf("右辺\n");  vecprint(b, n, 10, "%7.3f");
    det = gauss(n, a, b, x);  /* Gauss法で $Ax=b$ を解く */
    printf("行列式 = %g\n", det);
    printf("解と, 解を代入したときの両辺の差\n");
    for (i = 0; i < n; i++) {
        s = bsave[i];
        for (j = 0; j < n; j++) s -= asave[i][j] * x[j];
        printf("%4d: %12.7f %12.7f\n", i, x[i], s);
    }
    return 0;
}
