/***********************************************************
    fracint.c -- フラクタル補間
***********************************************************/
#include "window.c"

double left = 0, bottom = 0, right = 100, top = 100,       /* 座標の範囲 */
       x[] = { 0, 30, 60, 100 }, y[] = { 0, 50, 40, 10 },  /* 各点の座標 */
       d[] = { 0.1, 0.1, 0.1 };                            /* 縮小率 */
#define N (sizeof x / sizeof x[0] - 1)

int main(void)
{
    int i, j;
    double p, q, a[N], c[N], e[N], f[N];

    /* アフィン変換を求める */
    q = x[N] - x[0];
    for (i = 0; i < N; i++) {
        a[i] = (x[i+1] - x[i]) / q;
        e[i] = (x[N] * x[i] - x[0] * x[i+1]) / q;
        c[i] = (y[i+1] - y[i] - d[i] * (y[N] - y[0])) / q;
        f[i] = (x[N] * y[i] - x[0] * y[i+1] -
                d[i] * (x[N] * y[0] - x[0] * y[N])) / q;
    }
    /* アトラクタをプロットする */
    gr_clear(WHITE);
    gr_window(left, bottom, right, top, 0);
    p = x[0];  q = y[0];
    for (i = 0; i < 5000; i++) {
        j = rand() / (RAND_MAX / N + 1);
        q = c[j] * p + d[j] * q + f[j];
        p = a[j] * p            + e[j];
        gr_wdot(p, q, BLACK);
    }
    gr_BMP("fracint.bmp");
    return 0;
}
