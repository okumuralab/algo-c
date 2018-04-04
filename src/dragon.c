/***********************************************************
    dragon.c -- ドラゴンカーブ
***********************************************************/
#include "svgplot.c"  /* または epsplot.c */

void dragon(int i, double dx, double dy, int sign)
{
    if (i == 0) draw_rel(dx, dy);
    else {
        dragon(i-1, (dx-sign*dy)/2, (dy+sign*dx)/2,  1);
        dragon(i-1, (dx+sign*dy)/2, (dy-sign*dx)/2, -1);
    }
}

int main(void)
{
    int order = 10;

    plot_start(400, 250);
    move(100, 100);  dragon(order, 200, 0, 1);
    plot_end(0);
    return 0;
}
