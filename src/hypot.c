/**************************************************************
    hypot.c -- 直角三角形の斜辺の長さ
**************************************************************/
#include <math.h>

double hypot0(double x, double y)  /* 通常の方法 */
{
    return sqrt(x * x + y * y);
}

double hypot1(double x, double y)  /* やや念入りな方法 */
{
    double t;

    if (x == 0) return fabs(y);
    if (y == 0) return fabs(x);
    if (fabs(y) > fabs(x)) {
        t = x / y;
        return fabs(y) * sqrt(1 + t * t);
    } else {
        t = y / x;
        return fabs(x) * sqrt(1 + t * t);
    }
}

double hypot2(double x, double y)  /* Moler-Morrison法 */
{
    int i;
    double t;

    x = fabs(x);  y = fabs(y);
    if (x < y) {  t = x;  x = y;  y = t;  }
    if (y == 0) return x;
    for (i = 0; i < 3; i++) {  /* float: 2, double: 3 */
        t = y / x;  t *= t;  t /= 4 + t;
        x += 2 * x * t;  y *= t;
    }
    return x;
}

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

int main(void)
{
    double x, y;

    printf("x? ");  scanf("%lf", &x);
    printf("y? ");  scanf("%lf", &y);
    printf("hypot0 = %.*g\n", DBL_DIG, hypot0(x, y));
    printf("hypot1 = %.*g\n", DBL_DIG, hypot1(x, y));
    printf("hypot2 = %.*g\n", DBL_DIG, hypot2(x, y));
    return 0;
}
