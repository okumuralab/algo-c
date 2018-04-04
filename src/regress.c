/***********************************************************
    regress.c -- 回帰分析
***********************************************************/
#include "statutil.c"

#define PIVOTING 0    /* ピボット選択を行うか */
#define VERBOSE  0    /* 途中経過を出力するか */
#define EPS   1e-6    /* 許容誤差 */

#if ! PIVOTING  /* ピボット選択を行わない場合 */

int lsq(int n, int m, matrix x, vector b,
        int *col, vector normsq)  /* 最小2乗法 */
{
    int i, j, k, r;
    double s, t, u;
    vector v, w;

    for (j = 0; j < m; j++)
        normsq[j] = innerproduct(n, x[j], x[j]);
    r = 0;
    for (k = 0; k < m; k++) {
        if (normsq[k] == 0) continue;
        v = x[k];  u = innerproduct(n - r, &v[r], &v[r]);
        #if VERBOSE
            printf("\n%4d: 2乗和÷初期2乗和 = %-14g",
                k + 1, u / normsq[k]);
        #endif
        if (u / normsq[k] < EPS * EPS) continue;
        x[r] = v;  col[r] = k;
        u = sqrt(u);  if (v[r] < 0) u = -u;
        v[r] += u;  t = 1 / (v[r] * u);
        for (j = k + 1; j <= m; j++) {
            w = x[j];
            s = t * innerproduct(n - r, &v[r], &w[r]);
            for (i = r; i < n; i++) w[i] -= s * v[i];
        }
        v[r] = -u;
        #if VERBOSE
            printf("  残差2乗和 = %g",
              innerproduct(n-r-1, &x[m][r+1], &x[m][r+1]));
        #endif
        r++;
    }
    for (j = r - 1; j >= 0; j--) {
        s = x[m][j];
        for (i = j + 1; i < r; i++) s -= x[i][j] * b[i];
        b[j] = s / x[j][j];
    }
    #if VERBOSE
        printf("\n\n");
    #endif
    return r;  /* rank */
}

#else /* ピボット選択を行う場合 */

#define swap(a, i, j, t)  t = a[i];  a[i] = a[j];  a[j] = t

int lsq(int n, int m, matrix x, vector b,
        int *col, vector initnormsq, vector normsq)
{
    int i, j, r;
    double s, t, u;
    vector v, w;

    for (j = 0; j < m; j++) {
        col[j] = j;
        normsq[j] = innerproduct(n, x[j], x[j]);
        initnormsq[j] = (normsq[j] != 0) ? normsq[j] : -1;
    }
    for (r = 0; r < m; r++) {
        if (r != 0) {
            j = r;  u = 0;
            for (i = r; i < m; i++) {
                t = normsq[i] / initnormsq[i];
                if (t > u) {  u = t;  j = i;  }
            }
            swap(col, j, r, i);
            swap(normsq, j, r, t);
            swap(initnormsq, j, r, t);
            swap(x, j, r, v);
        }
        v = x[r];  u = innerproduct(n - r, &v[r], &v[r]);
        if (u / initnormsq[r] < EPS * EPS) break;
        u = sqrt(u);  if (v[r] < 0) u = -u;
        v[r] += u;  t = 1 / (v[r] * u);
        for (j = r + 1; j <= m; j++) {
            w = x[j];
            s = t * innerproduct(n - r, &v[r], &w[r]);
            for (i = r; i < n; i++) w[i] -= s * v[i];
            if (j < m) normsq[j] -= w[r] * w[r];
        }
        v[r] = -u;
    }
    for (j = r - 1; j >= 0; j--) {
        s = x[m][j];
        for (i = j + 1; i < r; i++) s -= x[i][j] * b[i];
        b[j] = s / x[j][j];
    }
    return r;  /* rank */
}

#endif /* PIVOTING */

void invr(int r, matrix x)  /* 上三角行列の逆行列 */
{
    int i, j, k;
    double s;

    for (k = 0; k < r; k++) {
        x[k][k] = 1 / x[k][k];
        for (j = k - 1; j >= 0; j--) {
            s = 0;
            for (i = j + 1; i <= k; i++)
                s -= x[i][j] * x[i][k];
            x[j][k] = s * x[j][j];
        }
    }
}

int main(int argc, char *argv[])
{
    int i, j, n, m, p, r, con, *col;  /* {\tt col} は列番号の表 */
    double s, t, rss;
    matrix x;
    vector b, normsq;  /* 回帰係数, ノルム2乗 */
    FILE *datafile;
#if PIVOTING
    vector initnormsq;  /* 初期ノルム2乗 */
#endif /* PIVOTING */

    if (argc != 2) error("使用法: regress filename");
    datafile = open_data(argv[1], &n, &m);
    if (datafile == NULL) error("データ不良");
    printf("定数項を含めますか(y/n)? ");
    con = (i = getchar()) == 'y' || i == 'Y';  p = m + con - 1;
    col = malloc(p * sizeof(int));
    x = new_matrix(p + 1, n);                       /* 記憶領域を獲得 */
    b = new_vector(p);  normsq = new_vector(p);
#if PIVOTING
    initnormsq = new_vector(p);                     /* 最初のノルム2乗 */
#endif /* PIVOTING */
    if (read_data(datafile, n, m, &x[con])) error("データ不良");
    if (con) for (i = 0; i < n; i++) x[0][i] = 1;   /* 定数項 */
#if ! PIVOTING
    r = lsq(n, p, x, b, col, normsq);   /* 最小2乗法 (ピボット交換なし) */
#else /* PIVOTING */
    r = lsq(n, p, x, b, col, initnormsq, normsq); /* (ピボット交換あり) */
#endif /* PIVOTING */
    rss = innerproduct(n - r, &x[p][r], &x[p][r]);  /* 残差2乗和 */
    invr(r, x);                                     /* {\tt r} を逆行列に */
    printf("変数  回帰係数       標準誤差        t\n");
    for (j = 0; j < r; j++) {
        t = innerproduct(r - j, &x[j][j], &x[j][j]);  /* 内積 */
        s = sqrt(t * rss / (n - r));
        printf("%4d  % #-14g % #-14g", col[j] + 1 - con, b[j], s);
        if (s > 0) printf("  % #-11.3g", fabs(b[j] / s));
        printf("\n");
    }
    printf("残差2乗和 / 自由度 = %g / %d = %g\n",
        rss, n - r, rss / (n - r));
    return 0;
}
