/***********************************************************
    ellipse.c -- グラフィックス
***********************************************************/
#include "grBMP.c"

void gr_ellipse(int xc, int yc, int rx, int ry, long color)
{
    int x, x1, y, y1, r;

    if (rx > ry) {
        x = r = rx;  y = 0;
        while (x >= y) {
            x1 = (int)((long)x * ry / rx);
            y1 = (int)((long)y * ry / rx);
            gr_dot(xc + x, yc + y1, color);
            gr_dot(xc + x, yc - y1, color);
            gr_dot(xc - x, yc + y1, color);
            gr_dot(xc - x, yc - y1, color);
            gr_dot(xc + y, yc + x1, color);
            gr_dot(xc + y, yc - x1, color);
            gr_dot(xc - y, yc + x1, color);
            gr_dot(xc - y, yc - x1, color);
            if ((r -= (y++ << 1) + 1) <= 0)
                r += --x << 1;
        }
    } else {
        x = r = ry;  y = 0;
        while (x >= y) {
            x1 = (int)((long)x * rx / ry);
            y1 = (int)((long)y * rx / ry);
            gr_dot(xc + x1, yc + y, color);
            gr_dot(xc + x1, yc - y, color);
            gr_dot(xc - x1, yc + y, color);
            gr_dot(xc - x1, yc - y, color);
            gr_dot(xc + y1, yc + x, color);
            gr_dot(xc + y1, yc - x, color);
            gr_dot(xc - y1, yc + x, color);
            gr_dot(xc - y1, yc - x, color);
            if ((r -= (y++ << 1) + 1) <= 0)
                r += --x << 1;
        }
    }
}

#if 0  /* テスト用 */
#include <stdlib.h>
int main(void)
{
    int i;

    for (i = 0; i < 100; i++)
        gr_ellipse(rand() % XMAX, rand() % YMAX,
                   rand() % 100, rand() % 100,
                   rand() % WHITE + 1);
    gr_BMP("test.bmp");
    return 0;
}
#endif
