/***********************************************************
    atan.c -- 逆三角関数
***********************************************************/
#define N  24  /* 本文参照 */
#define PI 3.14159265358979323846264
long double latan(long double x)  /* アークタンジェント */
{
    int i, sgn;
    long double a;

    if      (x >  1) {  sgn =  1;  x = 1 / x;  }
    else if (x < -1) {  sgn = -1;  x = 1 / x;  }
    else                sgn =  0;
    a = 0;
    for (i = N; i >= 1; i--)
        a = (i * i * x * x) / (2 * i + 1 + a);
    if (sgn > 0) return  PI / 2 - x / (1 + a);
    if (sgn < 0) return -PI / 2 - x / (1 + a);
    /* else */   return           x / (1 + a);
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

int main(void)
{
    int i;
    long double x, y;

    printf("  x    %-*s  左のtan\n", LDBL_DIG + 2, "自家製atan");
    for (i = -10; i <= 10; i++) {
        x = i / 4.0L;  y = latan(x);
        printf("%5.2Lf  %*.*Lf  % g\n",
            x, LDBL_DIG + 2, LDBL_DIG - 1, y, tan((double)y));
    }
    return 0;
}
