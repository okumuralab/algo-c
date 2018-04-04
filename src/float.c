/***********************************************************
    float.c -- 浮動小数点数
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

float foo(float x) {  return x;  }  /* 最適化を邪魔する */

int main(void)
{
    int b, p;
    float x, y, eps;

    x = y = 2;
    while (foo(x + 1) - x == 1) x *= 2;
    while (foo(x + y) == x) y *= 2;
    b = foo(x + y) - x;
    p = 1;  x = b;
    while (foo(x + 1) - x == 1) {  p++;  x *= b;  }
    eps = 1;
    while (foo(1 + eps / 2) > 1)  eps /= 2;
    eps = foo(1 + eps) - 1;
    printf("b = %d, p = %d, eps = %g\n", b, p, eps);
    return 0;
}
