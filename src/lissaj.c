/***********************************************************
    lissaj.c -- Lissajous (リサジュー) 図形
***********************************************************/
#include "svgplot.c"  /* または epsplot.c */
#include <math.h>  /* sin, cos */
#define PI 3.141592653589793

int main(void)
{
    int i;
    double t;

    plot_start(420, 420);  /* 座標指定 */
    move(210 + 200 * cos(0), 210 + 200 * sin(0));  /* 初期ペン位置 */
    for (i = 1; i <= 360; i++) {
        t = (PI / 180) * i;
        draw(210 + 200 * cos(3 * t), 210 + 200 * sin(5 * t));  /* ペン移動 */
    }
    plot_end(0);
    return 0;
}
