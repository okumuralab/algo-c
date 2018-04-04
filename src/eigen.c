/***********************************************************
    eigen.c -- QR法
***********************************************************/
#include "matutil.c"      /* 行列用小道具集 */
#include <math.h>

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
        while (j > 0 && fabs(e[j]) > EPS * (fabs(d[j - 1]) + fabs(d[j])))
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
                /* 次の5行は固有ベクトルを求めないなら不要 */
                for (i = 0; i < n; i++) {
                    x = a[k][i];  y = a[k + 1][i];
                    a[k    ][i] = c * x - s * y;
                    a[k + 1][i] = s * x + c * y;
                }
                if (k < h - 1) {
                    x = e[k + 1];  y = -s * e[k + 2];
                    e[k + 2] *= c;
                }
            }
        } while (fabs(e[h]) >
                EPS * (fabs(d[h - 1]) + fabs(d[h])));
    }
/*
  以下は固有値の降順に整列しているだけ. 必要なければ省く.
  固有ベクトルを求めないなら固有ベクトルの整列はもちろん不要.
  なお, {\tt matutil.c} 中で行列の各行をベクトルへのポインタ
  として定義しているので, 行交換はポインタのすげ替えだけで済む.
*/
    for (k = 0; k < n - 1; k++) {
        h = k;  t = d[h];
        for (i = k + 1; i < n; i++)
            if (d[i] > t) {  h = i;  t = d[h];  }
        d[h] = d[k];  d[k] = t;
        v = a[h];  a[h] = a[k];  a[k] = v;
    }
    return 0;
}

/************* 以下はテスト用 *****************/

#include <limits.h>
static unsigned long seed;

double rnd(void)  /* 乱数  0 < rnd() < 1 */
{
    return (seed *= 69069UL) / (ULONG_MAX + 1.0);
}

int main(void)
{
    int i, j, k, n;
    matrix a, u;
    vector d, work;
    double s, t;

    printf("n = ");  scanf("%d", &n);
    printf("乱数の種 (正の整数) = ");
    scanf("%ul", &seed);  seed |= 1;
    a = new_matrix(n, n);  u = new_matrix(n, n);
    d = new_vector(n);  work = new_vector(n);
    for (i = 0; i < n; i++)
        for (j = i; j < n; j++)
            u[i][j] = a[i][j] = a[j][i] = rnd() - rnd();
    printf("A:\n");
    matprint(a, n, 7, "%10.6f");
    if (eigen(n, u, d, work) == 1)
        printf("収束しません.\n");
    printf("固有値:\n");
    vecprint(d, n, 5, "% -14g");
    s = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            t = 0;
            for (k = 0; k < n; k++)
                t += u[k][i] * d[k] * u[k][j];
            s += (a[i][j] - t) * (a[i][j] - t);
        }
    }
    printf("二乗平均誤差: %g\n", sqrt(s) / n);
    return 0;
}
