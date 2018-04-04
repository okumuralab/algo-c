/***********************************************************
    julia.c -- Julia (ジュリア) 集合
***********************************************************/
#include "grBMP.c"
#include <math.h>

double dist2(double x, double y)
{
    return x * x + y * y;
}

int main(void)
{
    int k, j, i, jmid;
    double x, y, x2, y2, t, d, ya, x0, c;

    gr_clear(WHITE);
    c = 4.0 / XMAX;  jmid = YMAX / 2;
    ya = sqrt(3) / 2;
    for (i = 0; i < XMAX; i++) {
        x0 = c * i - 2.0;
        for (j = 0; j < jmid; j++) {
            y = c * j;  x = x0;
            for (k = 0; k <= 15; k++) {
                x2 = x * x;  y2 = y * y;
                d = x2 + y2;  if (d < 1E-10) break;
                d *= d;
                t = (1.0/3.0) * (2 * x + (x2 - y2) / d);
                y = (2.0/3.0) * y * (1 - x / d);  x = t;
                if (dist2(x - 1, y) < 0.0025) {
                    gr_dot(i, jmid + j, RED);
                    gr_dot(i, jmid - j, RED);
                    break;
                }
                if (dist2(x + 0.5, y + ya) < 0.0025) {
                    gr_dot(i, jmid + j, GREEN);
                    gr_dot(i, jmid - j, BLUE);
                    break;
                }
                if (dist2(x + 0.5, y - ya) < 0.0025) {
                    gr_dot(i, jmid + j, BLUE);
                    gr_dot(i, jmid - j, GREEN);
                    break;
                }
            }
        }
    }
    gr_BMP("julia.bmp");
    return 0;
}
