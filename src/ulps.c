/***********************************************************
    ulps.c -- 浮動小数点数
***********************************************************/
#include <float.h>
#include <math.h>

double ulps(double x, double y)
{
    float s, t, u;

    if (x == y) return 0;
    if ((x <= 0 && y >= 0) || (x >= 0 && y <= 0)) return HUGE_VAL;
    x = fabs(x);  y = fabs(y);
    u = 1;
    while (u <= x) u *= FLT_RADIX;
    t = u / FLT_RADIX;
    while (t > x) {  u = t;  t /= FLT_RADIX;  }
    s = t * FLT_EPSILON;
    if      (y < t) return ((x - t) + (t - y) * FLT_RADIX) / s;
    else if (y > u) return ((u - x) + (y - u) / FLT_RADIX) / s;
    else            return fabs(x - y) / s;
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    float x, y;

    for (x = 1; x < 10; x *= 1.1) {
        y = x + 0.6 * FLT_EPSILON * x;
        printf("x = %8.6f  ulps(x, x+0.6e|x|) = %g\n",
            x, ulps(x, y));
    }
    return 0;
}
