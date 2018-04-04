/***********************************************************
    imandel.c -- 整数版 Mandelbrot (マンデルブロート) 集合
***********************************************************/
#include "grBMP.c"
#define M  1000  /* 最大繰返し数 */

int main(void)
{
    int count, i, j;
    static int color[M + 1];
    long int x, y, a, b, a2, b2, ixmin, ixmax, iymin, iymax,
             dx, dy, d;  /* 32ビット, 2の補数表現 */
    double xmin = -1, xmax = 2.2, ymin = -1, ymax = 1;

    ixmin = (long int)((1L << 12) * xmin);
    ixmax = (long int)((1L << 12) * xmax);
    iymin = (long int)((1L << 12) * ymin);
    iymax = (long int)((1L << 12) * ymax);
    dx = ((ixmax - ixmin) + (XMAX - 2)) / (XMAX - 1);
    dy = ((iymax - iymin) + (YMAX - 2)) / (YMAX - 1);
    d = (dx > dy) ? dx : dy;
    if (d <= 0) return 1;
    color[0] = BLACK;
    for (i = 1; i <= M; i++) color[i] = WHITE;
    i = 0;
    for (x = ixmin; x <= ixmax; x += d) {
        j = 0;
        for (y = iymax; y >= iymin; y -= d) {
            a = x;  a2 = a * a;
            b = y;  b2 = b * b;
            count = M;
            while (a2 + b2 <= (4L << 24) && count) {
                b = ((a * b) >> 11) - y;
                a = ((a2 - b2) >> 12) - x;
                a2 = a * a;  b2 = b * b;  count--;
            }
            gr_dot(i, j, color[count]);
            j++;
        }
        i++;
    }
    gr_BMP("mandel.bmp");
    return 0;
}
