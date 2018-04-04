/***********************************************************
    epsplot.c -- EPSグラフィックス
***********************************************************/
#include <stdio.h>

void plot_start(int x, int y)
{
    printf("%%!PS-Adobe-3.0 EPSF-3.0\n");
    printf("%%%%BoundingBox: 0 0 %d %d\n", x, y);
    printf("newpath\n");
}

void plot_end(int close)
{
    if (close) printf("closepath\n");
    printf("stroke\n");
}

void move(double x, double y)  /* ペンアップで移動 */
{
    printf("%g %g moveto\n", x, y);
}

void move_rel(double dx, double dy)  /* 同上 (相対座標) */
{
    printf("%g %g rmoveto\n", dx, dy);
}

void draw(double x, double y)  /* ペンダウンで移動 */
{
    printf("%g %g lineto\n", x, y);
}

void draw_rel(double dx, double dy)  /* 同上 (相対座標) */
{
    printf("%g %g rlineto\n", dx, dy);
}
