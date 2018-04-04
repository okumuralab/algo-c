/***********************************************************
    pi2.c -- 円周率
***********************************************************/
/* 相加相乗平均による方法 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(void)
{
    int i;
    double a, b, s, t, last;

    a = 1;  b = 1 / sqrt(2.0);  s = 1;  t = 4;
    for (i = 0; i < 3; i++) {
        last = a;  a = (a + b) / 2;  b = sqrt(last * b);
        s -= t * (a - last) * (a - last);  t *= 2;
        printf("%16.14f\n", (a + b) * (a + b) / s);
    }
    return 0;
}
