/***********************************************************
    fib.c -- Fibonacci (フィボナッチ) 数列
***********************************************************/
#include <math.h>

int fib1(int n)
{
    return (int)(pow((1 + sqrt(5)) / 2, n) / sqrt(5) + 0.5);
}

int fib2(int n)
{
    int a, a1, b, b1, c, c1, x, x1, y, y1;

    a = 1;  b = 1;  c = 0;  x = 1;  y = 0;  n--;
    while (n > 0) {
        if (n & 1) {
            x1 = x;  y1 = y;
            x = a * x1 + b * y1;  y = b * x1 + c * y1;
        }
        n /= 2;
        a1 = a;  b1 = b;  c1 = c;
        a = a1 * a1 + b1 * b1;
        b = b1 * (a1 + c1);
        c = b1 * b1 + c1 * c1;
    }
    return x;
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i, a, b, t;

    a = 1;  b = 0;
    while (a < 100) {
        printf(" %d", a);
        t = a + b;  b = a;  a = t;
    }
    printf("\n");

    a = 1;  b = 0;
    while (a < 100) {
        printf(" %d", a);
        a += b;  b = a - b;
    }
    printf("\n");

    for (i = 1; i <= 11; i++) printf(" %d", fib1(i));
    printf("\n");

    for (i = 1; i <= 11; i++) printf(" %d", fib2(i));
    printf("\n");

    return 0;
}
