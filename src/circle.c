/***********************************************************
    circle.c -- グラフィックス
***********************************************************/
#include "grBMP.c"

void gr_circle(int xc, int yc, int r, long color)
{
    int x, y;

    x = r;  y = 0;
    while (x >= y) {
        gr_dot(xc + x, yc + y, color);
        gr_dot(xc + x, yc - y, color);
        gr_dot(xc - x, yc + y, color);
        gr_dot(xc - x, yc - y, color);
        gr_dot(xc + y, yc + x, color);
        gr_dot(xc + y, yc - x, color);
        gr_dot(xc - y, yc + x, color);
        gr_dot(xc - y, yc - x, color);
        if ((r -= (y++ << 1) + 1) <= 0)
            r += --x << 1;
    }
}

#if 0   /* テスト用 */
#include <stdlib.h>
int main(void)
{
    int i;

    for (i = 0; i < 100; i++)
        gr_circle(rand() % XMAX, rand() % YMAX,
                  rand() % 100,  rand() % WHITE + 1);
    gr_BMP("test.bmp");
    return 0;
}
#endif
