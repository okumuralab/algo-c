/***********************************************************
    e.c -- 自然対数の底
***********************************************************/

long double ee(void)
{
    int n;
    long double e, a, prev;

    e = 0;  a = 1;  n = 1;
    do {
        prev = e;  e += a;  a /= n;  n++;
    } while (e != prev);
    return e;
}

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

int main(void)
{
    printf("e = %.*Lg\n", LDBL_DIG, ee());
    return 0;
}
