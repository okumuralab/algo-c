/***********************************************************
    qrdecomp.c -- QR分解
***********************************************************/
#include "matutil.c"  /* \see 行列 */
#include <math.h>

void qrdecomp(int n, int m, matrix x)
{
    int i, j, r;
    double s, t, u;
    vector v, w;

    for (r = 0; r < m; r++) {
        v = x[r];
        u = sqrt(innerproduct(n - r, &v[r], &v[r]));
        if (v[r] < 0) u = -u;
        v[r] += u;  t = 1 / (v[r] * u);
        for (j = r + 1; j < m; j++) {
            w = x[j];
            s = t * innerproduct(n - r, &v[r], &w[r]); /* 内積 $\mbox{\tt v[r]}\times\mbox{\tt w[r]} + \cdots + \mbox{\tt v[n-1]}\times\mbox{\tt w[n-1]}$ */
            for (i = r; i < n; i++) w[i] -= s * v[i];
        }
        v[r] = -u;
    }
}

void xtoq(int n, int m, matrix x, matrix r)
{
    int i, j, k;

    for (k = 0; k < m; k++) {
        for (i = 0; i < n; i++) x[k][i] /= r[k][k];
        for (j = k + 1; j < m; j++)
            for (i = 0; i < n; i++)
                x[j][i] -= r[j][k] * x[k][i];
    }
}

/****************** 以下はテスト用 *******************/

#include <limits.h>
static unsigned long seed;

double rnd(void)  /* 乱数  0 < rnd() < 1 */
{
    return (seed *= 69069UL) / (ULONG_MAX + 1.0);
}

int main(void)
{
    int i, j, k, m, n;
    double s, t;
    matrix x, q, r;

    printf("n = ");  scanf("%d", &n);
    printf("m = ");  scanf("%d", &m);
    if (m > n) m = n;
    printf("乱数の種 (正の整数) = ");
    scanf("%ul", &seed);  seed |= 1;
    x = new_matrix(m, n);
    q = new_matrix(m, n);
    r = new_matrix(m, n);
    for (j = 0; j < m; j++)
        for (i = 0; i < n; i++)
            x[j][i] = q[j][i] = r[j][i] = rnd() - rnd();
    printf("X^T:\n");
    matprint(x, n, 7, "%10.6f");

    /* QR分解 */
    qrdecomp(n, m, r);  xtoq(n, m, q, r);
    printf("Q^T:\n");
    matprint(q, n, 7, "%10.6f");
    for (j = 0; j < m; j++)
        for (i = j + 1; i < n; i++) r[j][i] = 0;
    printf("R^T:\n");
    matprint(r, m, 7, "%10.6f");

    /* $\|QR - X\|_F / mn$ */
    t = 0;
    for (j = 0; j < m; j++)
        for (i = 0; i < n; i++) {
            s = 0;
            for (k = 0; k <= j; k++) s += q[k][i] * r[j][k];
            s -= x[j][i];  t += s * s;
        }
    printf("二乗平均誤差: %g\n", sqrt(t / (m * n)));

    return 0;
}
