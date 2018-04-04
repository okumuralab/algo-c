/***********************************************************
    hilbert.c -- Hilbert (ヒルベルト) 曲線
***********************************************************/
#include "svgplot.c"  /* または #include "epsplot.c" */
double h;  /* 刻み幅 */

void rul(int i), dlu(int i), ldr(int i), urd(int i);  /* 後出 */

void rul(int i)  /* right-up-left */
{
    if (i == 0) return;
    urd(i - 1);  draw_rel( h, 0);
    rul(i - 1);  draw_rel( 0, h);
    rul(i - 1);  draw_rel(-h, 0);
    dlu(i - 1);
}

void dlu(int i)  /* down-left-up */
{
    if (i == 0) return;
    ldr(i - 1);  draw_rel( 0, -h);
    dlu(i - 1);  draw_rel(-h,  0);
    dlu(i - 1);  draw_rel( 0,  h);
    rul(i - 1);
}

void ldr(int i)  /* left-down-right */
{
    if (i == 0) return;
    dlu(i - 1);  draw_rel(-h,  0);
    ldr(i - 1);  draw_rel( 0, -h);
    ldr(i - 1);  draw_rel( h,  0);
    urd(i - 1);
}

void urd(int i)  /* up-right-down */
{
    if (i == 0) return;
    rul(i - 1);  draw_rel( 0,  h);
    urd(i - 1);  draw_rel( h,  0);
    urd(i - 1);  draw_rel( 0, -h);
    ldr(i - 1);
}

int main(void)
{
    int i, order = 5, n = 310;  /* 位数5，辺310 */

    plot_start(n + 2, n + 2);
    h = n;
    for (i = 2; i <= order; i++) h = h / (2 + h / n);
    move(1, 1);  rul(order);
    plot_end(0);
    return 0;
}
