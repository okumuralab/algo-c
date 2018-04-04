/***********************************************************
    ci.c -- 余弦積分
************************************************************
    ${\rm Ci}(x) = \gamma + \log x
      + \int_{0}^{x} \frac{\cos t - 1}{t} \, dt$
     x      Ci(x)
     1   0.33740392290096813466
     2   0.42298082877486499570
     3   0.11962978600800032763
     4  -0.14098169788693041164
     5  -0.19002974965664387862
    10  -0.045456433004455372635
    20   0.044419820845353316540
    30  -0.033032417282071143779
    40   0.019020007896208766962
    50  -0.0056283863241163054402
***********************************************************/
#include <stdio.h>
#include <math.h>
#define EULER 0.577215664901532860606512090082  /* Eulerの定数 $\gamma$ */

static double Ci_series(double x)  /* 級数展開 */
{
    int k;
    double s, t, u;

    s = EULER + log(x);
    x = - x * x;  t = 1;
    for (k = 2; k < 1000; k += 2) {
        t *= x / ((k - 1) * k);
        u = s;  s += t / k;
        if (s == u) return s;
    }
    printf("Si_series(): 収束しません.\n");
    return s;
}

double Ci_asympt(double x)  /* 漸近展開 */
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
    return 0.5 * ((fmax + fmin) * sin(x)
                - (gmax + gmin) * cos(x));
}

double Ci(double x)
{
    if (x <  0) return -Ci(-x);
    if (x < 18) return Ci_series(x);
    return             Ci_asympt(x);
}

#include <stdlib.h>

int main(void)
{
    double x;

    printf(" x     Ci(x)\n");
    for (x = 1; x <= 50; x++)
        printf("%2.0f  %.10f\n", x, Ci(x));
    return 0;
}
