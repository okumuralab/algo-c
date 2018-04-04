/***********************************************************
    gseidel.c -- Gauss (ガウス)--Seidel (ザイデル) 法
***********************************************************/
#include "matutil.c"
#include <math.h>

#define VERBOSE   1     /* 途中経過を出力しないなら 0 にする */
#define EPS       1E-6  /* 許容誤差 */
#define MAX_ITER  500   /* 最大繰返し数 */

int gseidel(int n, matrix a, vector x, vector b)
{
    int j, i, ok, iter;
    double s;

    for (iter = 1; iter <= MAX_ITER; iter++) {
        ok = 1;
        for (i = 0; i < n; i++) {
            s = b[i];
            for (j = 0    ; j < i; j++) s -= a[i][j] * x[j];
            for (j = i + 1; j < n; j++) s -= a[i][j] * x[j];
            s /= a[i][i];  /* あらかじめ対角成分を1にしておけば不要 */
            if (ok && fabs(x[i] - s) > EPS * (1 + fabs(s)))
                ok = 0;
            x[i] = s;  /* SOR法なら例えば x[i] += 1.2 * (s - x[i]); */
        }
        #if VERBOSE
            printf("%3d:\n", iter);
            vecprint(x, n, 7, "%11.6f");
        #endif
        if (ok) return 0;  /* 成功 */
    }
    return 1;  /* 収束せず */
}

int main(void)
{
    int i, j, n;
    matrix a;
    vector x, b;

    printf("n = ");  scanf("%d", &n);
    a = new_matrix(n, n);
    x = new_vector(n);  b = new_vector(n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) a[i][j] = 1;
        a[i][i] = 2;  b[i] = n + 1;  x[i] = 0;
    }
    if (gseidel(n, a, x, b) == 1)
        printf("収束しません\n");
    printf("解 (正解はすべて 1)\n");
    vecprint(x, n, 7, "%11.6f");
    return 0;
}
