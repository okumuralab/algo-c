/***********************************************************
    mandel.c -- Mandelbrot (マンデルブロート) 集合
***********************************************************/
#include "grBMP.c"
#define M  1000  /* 最大繰返し数 */

int main(void)
{
    int i, j, imax, jmax, count;
    double x, y, a, b, a2, b2, dx, dy,
        xmin = -1, xmax = 2.2, ymin = -1, ymax = 1;
        // xmin = 0.6, xmax = 1.24, ymin = 0, ymax = 0.4;
    unsigned long color[M + 1];
    dx = xmax - xmin;  dy = ymax - ymin;
    if (dx * YMAX > dy * XMAX) {
        imax = XMAX;  jmax = (int)(XMAX * dy / dx + 0.5);
    } else {
        imax = (int)(YMAX * dx / dy + 0.5);  jmax = YMAX;
    }
    dx /= imax;  dy /= jmax;
    color[0] = BLACK;
    for (i = 1; i <= M; i++) color[i] = WHITE;
    for (i = 0; i <= imax; i++) {
        x = xmin + i * dx;
        for (j = 0; j <= jmax; j++) {
            y = ymin + j * dy;  a = x;  b = y;
            a2 = a * a;  b2 = b * b;  count = M;
            while (a2 + b2 <= 4 && count) {
                b = 2 * a * b - y;  a = a2 - b2 - x;
                a2 = a * a;  b2 = b * b;  count--;
            }
            gr_dot(i, j, color[count]);
        }
    }
    gr_BMP("mandel.bmp");
    return 0;
}
