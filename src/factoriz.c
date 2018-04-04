/***********************************************************
    factoriz.c -- 素因数分解
***********************************************************/
#include <stdio.h>

void factorize(int x)
{
    int d, q;

    printf("%5d = ", x);
    while (x >= 4 && x % 2 == 0) {
        printf("2 * ");  x /= 2;
    }
    d = 3;  q = x / d;
    while (q >= d) {
        if (x % d == 0) {
            printf("%d * ", d);  x = q;
        } else d += 2;
        q = x / d;
    }
    printf("%d\n", x);
}

#include <stdlib.h>
int main(void)
{
    int i;

    for (i = 1; i <= 100; i++) factorize(i);
    return 0;
}
