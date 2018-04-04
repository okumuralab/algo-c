/***********************************************************
    dragon2.c -- ドラゴンカーブ
***********************************************************/
#include "svgplot.c"          /* または epsplot.c */
#define ORDER  10             /* 位数 */
enum {RIGHT, LEFT};

int main(void)
{
    int k, i, p, q, dx, dy, dx1, dy1;
    static char fold[1 << ORDER];

    plot_start(510, 350);
    move(120, 120);
    dx = 0;  dy = 2;  draw_rel(3 * dx, 3 * dy);  p = 0;
    for (k = 1; k <= ORDER; k++) {
        fold[p] = LEFT;  q = 2 * p;
        for (i = p; i <= q; i++) {
            switch (fold[q - i]) {
            case RIGHT:
                fold[i] = LEFT;  dx1 = -dy;  dy1 = dx;
                break;
            case LEFT:
                fold[i] = RIGHT;  dx1 = dy;  dy1 = -dx;
                break;
            }
            draw_rel(dx + dx1, dy + dy1);
            draw_rel(3 * dx1, 3 * dy1);
            dx = dx1;  dy = dy1;
        }
        p = q + 1;
    }
    plot_end(0);
    return 0;
}
