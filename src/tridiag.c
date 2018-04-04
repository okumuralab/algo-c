/***********************************************************
    tridiag.c -- 3重対角化
***********************************************************/
#include "matutil.c"
#include <math.h>

double house(int n, vector x)  /* Householder変換 */
{
    int i;
    double s, t;

    s = sqrt(innerproduct(n, x, x));  /* 内積の平方根 = 大きさ */
    if (s != 0) {
        if (x[0] < 0) s = -s;
        x[0] += s;  t = 1 / sqrt(x[0] * s);
        for (i = 0; i < n; i++) x[i] *= t;
    }
    return -s;
}

void tridiagonalize(int n, matrix a, vector d, vector e)
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

/***************** 以下はテスト用 *********************/

#include <limits.h>
static unsigned long seed;

double rnd(void)  /* 乱数  0 < rnd() < 1 */
{
    return (seed *= 69069UL) / (ULONG_MAX + 1.0);
}

int main(void)
{
    int i, j, k, n;
    static matrix a, p;
    static vector d, e, temp;
    double s, t;

    printf("n = ");  scanf("%d", &n);
    printf("乱数の種 (正の整数) = ");
    scanf("%ul", &seed);  seed |= 1;
    a = new_matrix(n, n);
    p = new_matrix(n, n);
    d = new_vector(n);
    e = new_vector(n);
    temp = new_vector(n);
    for (i = 0; i < n; i++)
        for (j = 0; j <= i; j++)
            a[i][j] = a[j][i] = p[i][j] = p[j][i]
                = rnd() - rnd();
    printf("A:\n");
    matprint(a, n, 7, "%10.6f");
    tridiagonalize(n, p, d, e);
    printf("d:\n");
    vecprint(d, n, 5, "% -14g");
    printf("e:\n");
    vecprint(e, n - 1, 5, "% -14g");
    for (i = 0; i < n; i++) {
        for (k = 0; k < n; k++)
            temp[k] = a[i][k];
        for (j = 0; j < n; j++) {
            s = 0;
            for (k = 0; k < n; k++)
                s += temp[k] * p[j][k];
            a[i][j] = s;
        }
    }
    for (j = 0; j < n; j++) {
        for (k = 0; k < n; k++)
            temp[k] = a[k][j];
        for (i = 0; i < n; i++) {
            s = 0;
            for (k = 0; k < n; k++)
                s += p[i][k] * temp[k];
            a[i][j] = s;
        }
    }
    s = 0;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (i == j) {
                t = a[i][j] - d[i];  s += t * t;
            } else if (i + 1 == j) {
                t = a[i][j] - e[i];  s += t * t;
            } else if (i == j + 1) {
                t = a[i][j] - e[j];  s += t * t;
            } else {
                t = a[i][j];  s += t * t;
            }
    printf("二乗平均誤差: %g\n", sqrt(s) / n);
    return 0;
}
