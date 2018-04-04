/***********************************************************
    poweigen.c -- 累乗法
***********************************************************/
#include "matutil.c"  /* 行列用小道具集 */
#include <math.h>
#define TEST  /* これがあると途中経過を報告 */

#define EPS       1E-6  /* 固有ベクトルの許容誤差 */
#define MAX_ITER  200   /* 最大繰返し数 */
#define forall(i) for (i = 0; i < n; i++)

int power(int n, int m, matrix a, vector lambda, matrix x)
{
    int i, j, k, kk, iter;
    double s, s1, t, u, d, d1, e;
    vector xk, y;

    y = new_vector(n);  /* {\tt y[0..n-1]} の記憶領域を確保 */
    kk = m;             /* 実際に求められた固有値・固有ベの個数 */
    for (k = 0; k < m; k++) { /* {\tt k} 番目の固有値・固有ベを求める */
        xk = x[k];  t = 1 / sqrt(n);
        forall(i) xk[i] = t;   /* 大きさ1の初期値ベクトル */
        d = s = 0;  iter = 0;
        do {
            d1 = d;  s1 = s;  s = e = 0;
            forall(i) {
                t = 0;
                forall(j) t += a[i][j] * xk[j];
                y[i] = t;  s += t * t;  /* $y = Ax$ */
            }
            s = sqrt(s);  if (s1 < 0) s = -s;  /* $s = \pm \| y \|$ */
            forall(i) {
                t = y[i] / s;  u = xk[i] - t;
                e += u * u;  xk[i] = t;  /* {\tt xk[]}: 固有ベクトル */
            }
            if (e > 2) s = -s;  /* ベクトルが反転したなら固有値は負 */
            d = sqrt(e);  d1 -= d;
            #ifdef TEST
                printf("iter = %3d  lambda[%d] = %10.6f  "
                    "||x' - x|| = %10.8f\n", iter, k, s, d);
            #endif
        } while (++iter < MAX_ITER && e > EPS * d1);
        if (iter >= MAX_ITER && kk == m) kk = k;
        lambda[k] = s;  /* 固有値 */
        if (k < m - 1)
            forall(i) forall(j)
                a[i][j] -= s * xk[i] * xk[j];
    }
    free_vector(y);
    return kk;  /* 収束した固有ベクトルの数 */
}

#include <limits.h>
static unsigned long seed;
double rnd(void)  /* 乱数  0 < rnd() < 1 */
{
    return (seed *= 69069UL) / (ULONG_MAX + 1.0);
}

int main(void)
{
    int i, j, k, n;
    double s, e;
    matrix a, b, x;
    vector lambda;

    printf("n = ");  scanf("%d", &n);
    printf("乱数の種 (正の整数) = ");
    scanf("%ul", &seed);  seed |= 1;
    a = new_matrix(n, n);
    b = new_matrix(n, n);
    x = new_matrix(n, n);
    lambda = new_vector(n);
    forall(i) for (j = 0; j <= i; j++)
        a[i][j] = a[j][i] =
        b[i][j] = b[j][i] = rnd() - rnd();
    matprint(a, n, 7, "%10.6f");
    k = power(n, n, a, lambda, x);
    printf("収束した固有ベクトルの数: %d\n", k);
    printf("固有値:\n");
    vecprint(lambda, n, 5, "% -14g");
    e = 0;
    forall(i) forall(j) {
        s = b[i][j];
        forall(k) s -= lambda[k] * x[k][i] * x[k][j];
        e += s * s;
    }
    printf("二乗平均誤差: %g\n", sqrt(e / (n * n)));
    return 0;
}
