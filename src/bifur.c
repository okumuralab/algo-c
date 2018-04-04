/***********************************************************
    bifur.c -- カオスとアトラクタ
***********************************************************/
#include "window.c"

int main(void)
{
    int i;
    double k, p, dk, kmin = 1.5, kmax = 3, pmin = 0, pmax = 1.5;

    gr_clear(WHITE);
    gr_window(kmin, pmin, kmax, pmax, 0);
    dk = (kmax - kmin) / (XMAX - 1);
    for (k = kmin; k <= kmax; k += dk) {
        p = 0.3;
        for (i = 1; i <= 50; i++) p += k * p * (1 - p);
        for (i = 51; i <= 100; i++) {
            if (p >= pmin && p <= pmax)
                gr_wdot(k, p, BLACK);
            p += k * p * (1 - p);
        }
    }
    gr_BMP("bifur.bmp");
    return 0;
}
