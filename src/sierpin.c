/***********************************************************
    sierpin.c -- Sierpi\'{n}ski (シェルピンスキー) 曲線
***********************************************************/
#include "svgplot.c"  /* または epsplot.c */
double h;  /* 刻み幅 */

void urd(int i), lur(int i), dlu(int i), rdl(int i);  /* 後出 */

void urd(int i)  /* up-right-down */
{
    if (i == 0) return;
    urd(i - 1);  draw_rel(h, h);
    lur(i - 1);  draw_rel(2 * h, 0);
    rdl(i - 1);  draw_rel(h, -h);
    urd(i - 1);
}

void lur(int i)  /* left-up-right */
{
    if (i == 0) return;
    lur(i - 1);  draw_rel(-h, h);
    dlu(i - 1);  draw_rel(0, 2 * h);
    urd(i - 1);  draw_rel(h, h);
    lur(i - 1);
}

void dlu(int i)  /* down-left-up */
{
    if (i == 0) return;
    dlu(i - 1);  draw_rel(-h, -h);
    rdl(i - 1);  draw_rel(-2 * h, 0);
    lur(i - 1);  draw_rel(-h, h);
    dlu(i - 1);
}

void rdl(int i)  /* right-down-left */
{
    if (i == 0) return;
    rdl(i - 1);  draw_rel(h, -h);
    urd(i - 1);  draw_rel(0, -2 * h);
    dlu(i - 1);  draw_rel(-h, -h);
    rdl(i - 1);
}

int main(void)
{
    int i, order = 4; /* 位数 */

    plot_start(242, 242);
    h = 1;
    for (i = 2; i <= order; i++) h = 3 * h / (6 + h);
    h *= 40;
    move(h + 1, 1);
    urd(order);  draw_rel( h,  h);
    lur(order);  draw_rel(-h,  h);
    dlu(order);  draw_rel(-h, -h);
    rdl(order);  draw_rel( h, -h);
    plot_end(1);
    return 0;
}
