/***********************************************************
    treecurv.c -- 樹木曲線
***********************************************************/
#include "svgplot.c"  /* または epsplot.c */
#include <math.h>  /* sin(), cos() */
#define FACTOR  0.7
#define TURN    0.5

void tree(int n, double length, double angle)
{
    double dx, dy;

    dx = length * sin(angle);  dy = length * cos(angle);
    draw_rel(dx, dy);
    if (n > 0) {
        tree(n - 1, length * FACTOR, angle + TURN);
        tree(n - 1, length * FACTOR, angle - TURN);
    }
    move_rel(-dx, -dy);
}

int main(void)
{
    int order = 10;  /* 位数 */

    plot_start(400, 350);
    move(200, 0);  tree(order, 100, 0);
    plot_end(0);
    return 0;
}
