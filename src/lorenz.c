/***********************************************************
    lorenz.c -- Lorenz (ローレンツ) アトラクタ
***********************************************************/
#include "svgplot.c"  /* または epsplot.c */

#define A  10.0
#define B  28.0
#define C  (8.0 / 3.0)
#define D  0.01

int main(void)
{
    int k;
    double x, y, z, dx, dy, dz;

    plot_start(200, 230);
    x = y = z = 1;
    for (k = 0; k < 3000; k++) {
        dx = A * (y - x);
        dy = x * (B - z) - y;
        dz = x * y - C * z;
        x += D * dx;  y += D * dy;  z += D * dz;
        if (k > 100) draw(5 * x + 100, 5 * z - 20);
        else         move(5 * x + 100, 5 * z - 20);
    }
    plot_end(0);
    return 0;
}
