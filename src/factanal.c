/***********************************************************
    factanal.c -- 因子分析
***********************************************************/
#include "statutil.c"     /* 多変量データ入力ルーチン */

#define EPS         1E-6  /* 非対角成分の許容誤差 */
#define MAX_ITER    100   /* 最大の繰返し数 */

double house(int n, vector x)  /* Householder変換 */
{
    int i;
    double s, t;

    s = sqrt(innerproduct(n, x, x));  /* 内積の平方根, すなわち大きさ */
    if (s != 0) {
        if (x[0] < 0) s = -s;
        x[0] += s;  t = 1 / sqrt(x[0] * s);
        for (i = 0; i < n; i++) x[i] *= t;
    }
    return -s;
}

void tridiagonalize(int n, matrix a, vector d, vector e) /* 3重対角化 */
{
    int i, j, k;
    double s, t, p, q;
    vector v, w;

    for (k = 0; k < n - 2; k++) {
        v = a[k];  d[k] = v[k];
        e[k] = house(n - k - 1, &v[k + 1]);
        if (e[k] == 0) continue;
        for (i = k + 1; i < n; i++) {
            s = 0;
            for (j = k + 1; j < i; j++) s += a[j][i] * v[j];
            for (j = i;     j < n; j++) s += a[i][j] * v[j];
            d[i] = s;
        }
        t = innerproduct(n-k-1, &v[k+1], &d[k+1]) / 2;
        for (i = n - 1; i > k; i--) {
            p = v[i];  q = d[i] - t * p;  d[i] = q;
            for (j = i; j < n; j++)
                a[i][j] -= p * d[j] + q * v[j];
        }
    }
    if (n >= 2) {  d[n - 2] = a[n - 2][n - 2];
                   e[n - 2] = a[n - 2][n - 1];  }
    if (n >= 1)    d[n - 1] = a[n - 1][n - 1];
    for (k = n - 1; k >= 0; k--) {
        v = a[k];
        if (k < n - 2) {
            for (i = k + 1; i < n; i++) {
                w = a[i];
                t = innerproduct(n-k-1, &v[k+1], &w[k+1]);
                for (j = k + 1; j < n; j++)
                    w[j] -= t * v[j];
            }
        }
        for (i = 0; i < n; i++) v[i] = 0;
        v[k] = 1;
    }
}

int eigen(int n, matrix a, vector d, vector e)
{
    int i, j, k, h, iter;
    double c, s, t, w, x, y;
    vector v;

    tridiagonalize(n, a, d, &e[1]);  /* 3重対角化 */
    e[0] = 0;  /* 番人 */
    for (h = n - 1; h > 0; h--) {  /* 行列のサイズを小さくしていく */
        j = h;
        while (fabs(e[j]) > EPS * (fabs(d[j - 1]) + fabs(d[j])))
            j--;  /* $\mbox{\tt e[$j$]} \ne 0$ のブロックの始点を見つける */
        if (j == h) continue;
        iter = 0;
        do {
            if (++iter > MAX_ITER) return 1;
            w = (d[h - 1] - d[h]) / 2;
            t = e[h] * e[h];
            s = sqrt(w * w + t);  if (w < 0) s = -s;
            x = d[j] - d[h] + t / (w + s);  y = e[j + 1];
            for (k = j; k < h; k++) {
                if (fabs(x) >= fabs(y)) {
                    t = -y / x;  c = 1 / sqrt(t * t + 1);
                    s = t * c;
                } else {
                    t = -x / y;  s = 1 / sqrt(t * t + 1);
                    c = t * s;
                }
                w = d[k] - d[k + 1];
                t = (w * s + 2 * c * e[k + 1]) * s;
                d[k] -= t;  d[k + 1] += t;
                if (k > j) e[k] = c * e[k] - s * y;
                e[k + 1] += s * (c * w - 2 * s * e[k + 1]);
                for (i = 0; i < n; i++) {           /* 固有ベ */
                    x = a[k][i];  y = a[k + 1][i];  /* クトル */
                    a[k    ][i] = c * x - s * y;    /* を求め */
                    a[k + 1][i] = s * x + c * y;    /* ないな */
                }                                   /* ら不要 */
                if (k < h - 1) {
                    x = e[k + 1];  y = -s * e[k + 2];
                    e[k + 2] *= c;
                }
            }
        } while (fabs(e[h]) >
                EPS * (fabs(d[h - 1]) + fabs(d[h])));
    }
    for (k = 0; k < n - 1; k++) {
        h = k;  t = d[h];
        for (i = k + 1; i < n; i++)
            if (d[i] > t) {  h = i;  t = d[h];  }
        d[h] = d[k];  d[k] = t;
        v = a[h];  a[h] = a[k];  a[k] = v;
    }
    return 0;
}
/*
  {\tt r[0..m-1][0..m-1]} に入った相関係数の行列に対して因子分析を行い,
  {\tt nfac} ($< {\tt m}) 個の共通因子を抽出する.
  {\tt r} の対角成分は共通性の推定値で上書きされる.
  {\tt q[$k$][$j$]} には第 $j + 1$ 変数の第 $k + 1$ 因子負荷量 ($0 \le
  k < {\tt nfac}$, $0 \le j < {\tt m}$ が入る.
*/
void factor(int m, int nfac, matrix r, matrix q,
            vector lambda, vector work)
{
    int i, j, k, iter, maxiter;
    double s, t, percent;

    iter = maxiter = 0;
    for ( ; ; ) {
        if (++iter > maxiter) {
            printf("繰返し数 (0:繰返し終了) ? ");
            scanf("%d", &i);  if (i <= 0) break;
            maxiter += i;
        }
        for (j = 0; j < m; j++) for (k = 0; k < m; k++)
            q[j][k] = r[j][k];
        if (eigen(m, q, lambda, work)) error("収束しません");
        s = innerproduct(m - nfac, &lambda[nfac], &lambda[nfac]);
        printf("%3d: 非対角成分のRMS誤差 %.3g\n",
            iter, sqrt(s / (m * (m - 1)))); /* RMS: root mean square (2乗の平均の平方根) */
        for (j = 0; j < m; j++) {
            s = 0;
            for (k = 0; k < nfac; k++)
                s += lambda[k] * q[k][j] * q[k][j];
            r[j][j] = s;  /* 共通性 */
        }
    }
    t = 0;  /* trace */
    for (k = 0; k < m; k++) t += lambda[k];
    printf("因子    固有値     ％  累積％\n");
    s = 0;
    for (k = 0; k < m; k++) {
        printf((k < nfac) ? " %3d " : "(%3d)", k + 1);
        percent = 100 * lambda[k] / t;  s += percent;
        printf(" %8.4f  %5.1f  %5.1f\n", lambda[k], percent, s);
    }
    printf("合計  %8.4f  %5.1f\n", t, s);
    for (k = 0; k < nfac; k++)
        work[k] = sqrt(fabs(lambda[k]));    /* {\tt lambda[k]} は負かも */
    printf("変数  共通性   因子負荷量\n");
    for (j = 0; j < m; j++) {
        printf("%4d  %6.3f ", j + 1, r[j][j]);
        for (k = 0; k < nfac; k++) {
            q[k][j] *= work[k];
            if (k < 9) printf("%7.3f", q[k][j]);
        }
        printf("\n");
    }
#ifdef CHECK  /* 誤差のチェック用 */
    t = 0;
    for (j = 0; j < m; j++) for (k = 0; k < j; k++) {
        s = 0;
        for (i = 0; i < nfac; i++) s += q[i][j] * q[i][k];
        t += (r[j][k] - s) * (r[j][k] - s);
    }
    printf("因子負荷量から再現した相関係数のRMS誤差: %g\n",
        sqrt(t / (m * (m - 1) / 2)));
#endif /* CHECK */
}
/*
  因子分析のメインルーチン. 単に相関係数を求めるだけであるが,
  データを主記憶に一度に読み込むのでなく,
  漸化式を使って平均, 分散, 相関係数を更新する方法を用いている.
*/
int main(int argc, char *argv[])
{
    int i, j, k, n, m, nfac;
    double t;
    vector mean, lambda, work;  /* 平均, 固有値, 作業用 */
    matrix r, q;                /* 相関係数, 固有ベクトル */
    FILE *datafile;

    if (argc != 2) error("使用法: factanal filename");
    datafile = open_data(argv[1], &n, &m);
    if (datafile == NULL) error("データ不良");
    r = new_matrix(m, m);  q = new_matrix(m, m);
    mean = new_vector(m);  lambda = new_vector(m);
    work = new_vector(m);
    for (j = 0; j < m; j++) {
        mean[j] = 0;
        for (k = 0; k <= j; k++) r[j][k] = 0;
    }
    for (i = 0; i < n; i++) for (j = 0; j < m; j++) {
        t = getnum(datafile);                          /* 数値入力 */
        if (missing(t)) error("データ不良");           /* 欠測値かエラー */
        work[j] = t - mean[j];  mean[j] += work[j] / (i + 1);
        for (k = 0; k <= j; k++)
            r[j][k] += i * work[j] * work[k] / (i + 1);
    }
    for (j = 0; j < m; j++) {
        work[j] = sqrt(r[j][j]);  r[j][j] = 1;
        for (k = 0; k < j; k++) {
            r[j][k] /= work[j] * work[k];  r[k][j] = r[j][k];
        }
    }
    t = 1 / sqrt(n - 1.0);
    printf("変数  平均値        標準偏差\n");
    for (j = 0; j < m; j++)
        printf("%4d  % -12.5g  % -12.5g\n",
            j + 1, mean[j], t * work[j]);
    printf("相関係数\n");                     /* 左下半分だけ表示 */
    for (j = 0; j < m; j++) {
        for (k = 0; k <= j; k++) printf("%8.4f", r[j][k]);
        printf("\n");
    }
    for ( ; ; ) {
        printf("\n共通因子の数 (0:実行終了) ? ");
        scanf("%d", &nfac);
        if (nfac > m) nfac = m;
        if (nfac < 1) break;
        factor(m, nfac, r, q, lambda, work);
    }
    return 0;
}
