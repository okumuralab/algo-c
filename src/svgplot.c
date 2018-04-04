/***********************************************************
    svgplot.c -- SVGグラフィックス
***********************************************************/
#include <stdio.h>
static double ymax;

void plot_start(int x, int y)  /* プロット開始 */
{
    printf("<svg xmlns=\"http://www.w3.org/2000/svg\" ");
    printf("version=\"1.1\" width=\"%d\" height=\"%d\">\n", x, y);
    printf("<path d=\"");
    ymax = y;
}

void plot_end(int close)  /* プロット終了 */
{
    if (close) printf("Z");
    printf("\" fill=\"none\" stroke=\"black\" />\n");
    printf("</svg>\n");
}

void move(double x, double y)  /* ペンアップで移動 */
{
    printf("M %g %g ", x, ymax - y);
}

void move_rel(double dx, double dy)  /* 同上 (相対座標) */
{
    printf("m %g %g ", dx, -dy);
}

void draw(double x, double y)  /* ペンダウンで移動 */
{
    printf("L %g %g ", x, ymax - y);
}

void draw_rel(double dx, double dy)  /* 同上 (相対座標) */
{
    printf("l %g %g ", dx, -dy);
}

#if 0  /* テスト */

#include <math.h>

int main(void)
{
    int i;
    double theta, x, y;

    plot_start(300, 300);  /* x, yの最大値（整数）。最小値は0, 0（左下隅） */
    for (i = 0; i < 5; i++) {
        theta = 2 * M_PI * i / 5;
        x = 150 + 140 * cos(theta);
        y = 150 + 140 * sin(theta);
        if (i == 0) {
            move(x, y);
        } else {
            draw(x, y);
        }
    }
    plot_end(1);  /* 1なら閉じる（出発点に戻る線を引く）。0なら閉じない */
    return 0;
}
#endif
