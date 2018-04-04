/***********************************************************
    princo.c -- 主成分分析
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
            j--;  /* $e[j] \ne 0$ のブロックの始点を見つける */
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

void princo(int n, int m, matrix x, matrix q, vector lambda,
            vector work, int method)
{
    int i, j, k, ndf;
    double s, t, percent;

    ndf = n - (method != 0);                      /* 自由度 */
    printf("変数  平均値        %s\n",
        (method == 0) ? "ＲＭＳ" : "標準偏差");
    for (j = 0; j < m; j++) {
        t = 0;
        for (i = 0; i < n; i++) t += x[j][i];
        t /= n;
        if (method != 0) for (i = 0; i < n; i++) x[j][i] -= t;
        q[j][j] = innerproduct(n, x[j], x[j]) / ndf;
        s = sqrt(q[j][j]);
        printf("%4d  % -12.5g  % -12.5g\n", j + 1, t, s);
        if (method == 2) {
            q[j][j] = 1;
            for (i = 0; i < n; i++) x[j][i] /= s;
        }
    }
    for (j = 0; j < m; j++) for (k = 0; k < j; k++)
        q[j][k] = q[k][j] = innerproduct(n, x[j], x[k]) / ndf;
    if (eigen(m, q, lambda, work)) error("収束しません");
    t = 0;  /* trace */
    for (k = 0; k < m; k++) t += lambda[k];
    printf("主成分  固有値       ％   累積％\n");
    s = 0;
    for (k = 0; k < m; k++) {
        percent = 100 * lambda[k] / t;  s += percent;
        printf("%4d  % -12.5g  %5.1f  %5.1f\n",
            k + 1, lambda[k], percent, s);
    }
    printf("合計  % -12.5g  %5.1f\n\n", t, s);
    printf("変数  重み\n");
    for (j = 0; j < m; j++) {
        printf("%4d", j + 1);
        for (k = 0; k < m && k < 5; k++)
            printf("%11.6f   ", q[k][j]);
        printf("\n");
    }
    printf("個体  主成分\n");
    for (i = 0; i < n; i++) {
        printf("%4d  ", i + 1);
        for (k = 0; k < m && k < 5; k++) {
            s = 0;
            for (j = 0; j < m; j++) s += q[k][j] * x[j][i];
            printf("% -14.5g", s);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    int n, m, method;
    vector lambda, work;  /* 固有値, 作業用 */
    matrix x, q;          /* データ, 直交行列 */
    FILE *datafile;

    if (argc != 2) error("使用法: princo filename");
    printf("0:元のまま 1:平均を引く 2:さらに標準偏差で割る ?");
    scanf("%d", &method);
    if (method < 0 || method > 2) error("誤入力");
    datafile = open_data(argv[1], &n, &m);
    if (datafile == NULL) error("データ不良");
    x = new_matrix(m, n);  q = new_matrix(m, m);
    lambda = new_vector(m);  work = new_vector(m);
    if (read_data(datafile, n, m, x)) error("データ不良");
    princo(n, m, x, q, lambda, work, method);  /* 主成分分析 */
    return 0;
}
