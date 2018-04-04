/***********************************************************
    plotter.c -- BMPファイル出力のプロッタシミュレーション
***********************************************************/

#include "window.c"
static double xpen = 0, ypen = 0;  /* ペンの現在位置 */

void move(double x, double y)  /* ペンアップで移動 */
{
    xpen = x;  ypen = y;
}

void move_rel(double dx, double dy)  /* 同上 (相対座標) */
{
    xpen += dx;  ypen += dy;
}

void draw(double x, double y)  /* ペンダウンで移動 */
{
    gr_wline(xpen, ypen, x, y, BLACK);
    xpen = x;  ypen = y;
}

void draw_rel(double dx, double dy)  /* 同上 (相対座標) */
{
    gr_wline(xpen, ypen, xpen + dx, ypen + dy, BLACK);
    xpen += dx;  ypen += dy;
}
