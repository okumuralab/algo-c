/***********************************************************
    line.c -- グラフィックス
***********************************************************/
#include "grBMP.c"
#include <stdlib.h>

void gr_line(int x1, int y1, int x2, int y2, long color)  /* 線分を描く */
{
    int dx, dy, s, step;

    dx = abs(x2 - x1);  dy = abs(y2 - y1);
    if (dx > dy) {
        if (x1 > x2) {
            step = (y1 > y2) ? 1 : -1;
            s = x1;  x1 = x2;  x2 = s;  y1 = y2;
        } else step = (y1 < y2) ? 1: -1;
        gr_dot(x1, y1, color);
        s = dx >> 1;
        while (++x1 <= x2) {
            if ((s -= dy) < 0) {
                s += dx;  y1 += step;
            };
            gr_dot(x1, y1, color);
        }
    } else {
        if (y1 > y2) {
            step = (x1 > x2) ? 1 : -1;
            s = y1;  y1 = y2;  y2 = s;  x1 = x2;
        } else step = (x1 < x2) ? 1 : -1;
        gr_dot(x1, y1, color);
        s = dy >> 1;
        while (++y1 <= y2) {
            if ((s -= dx) < 0) {
                s += dy;  x1 += step;
            }
            gr_dot(x1, y1, color);
        }
    }
}

#if 0  /* テスト用 */
int main(void)
{
    int i;

    for (i = 0; i < 100; i++)
        gr_line(rand() % XMAX, rand() % YMAX,
                rand() % XMAX, rand() % YMAX,
                rand() % WHITE + 1);
    gr_BMP("test.bmp");
    return 0;
}
#endif
