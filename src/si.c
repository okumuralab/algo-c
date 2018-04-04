/***********************************************************
    si.c -- 正弦積分
************************************************************
    ${\rm Si}(x) = \int_{0}^{x} \frac{\sin t}{t} \, dt$
     x      Si(x)
     1   0.94608307036718301494
     2   1.60541297680269484858
     3   1.84865252799946825640
     4   1.75820313894905305811
     5   1.54993124494467413727
    10   1.65834759421887404933
    20   1.54824170104343984016
    30   1.56675654003035111098
    40   1.58698511935478450678
    50   1.55161707248593589473
    \infty   \pi/2
***********************************************************/
#include <stdio.h>
#include <math.h>
#define PI 3.14159265358979323846264338328

static double Si_series(double x)  /* 級数展開 */
{
    int k;
    double s, t, u;

    s = t = x;  x = - x * x;
    for (k = 3; k < 1000; k += 2) {
        t *= x / ((k - 1) * k);
        u = s;  s += t / k;
        if (s == u) return s;
    }
    printf("Si_series(): 収束しません.\n");
    return s;
}

double Si_asympt(double x)  /* 漸近展開 */
{
    int k, flag;
    double t, f, g, fmax, fmin, gmax, gmin;

    fmax = gmax = 2;  fmin = gmin = 0;
    f = g = 0;  t = 1 / x;
    k = flag = 0;
    while (flag != 15) {
        f += t;  t *= ++k / x;
        if (f < fmax) fmax = f;  else flag |= 1;
        g += t;  t *= ++k / x;
        if (g < gmax) gmax = g;  else flag |= 2;
        f -= t;  t *= ++k / x;
        if (f > fmin) fmin = f;  else flag |= 4;
        g -= t;  t *= ++k / x;
        if (g > gmin) gmin = g;  else flag |= 8;
    }
    return 0.5 * (PI - (fmax + fmin) * cos(x)
                     - (gmax + gmin) * sin(x));
}

double Si(double x)
{
    if (x <  0) return -Si(-x);
    if (x < 18) return Si_series(x);
    return             Si_asympt(x);
}

#include <stdlib.h>

int main(void)
{
    double x;

    printf(" x     Si(x)\n");
    for (x = 1; x <= 50; x++)
        printf("%2.0f  %.10f\n", x, Si(x));
    return 0;
}
