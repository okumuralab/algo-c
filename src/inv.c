/***********************************************************
    inv.c -- 合同式
***********************************************************/

int inv(int a, int n, int *gcd)
{
    int  d, q, r;
    long s, t, x;

    d = n;  x = 0;  s = 1;
    while (a != 0) {
        q = d / a;
        r = d % a;  d = a;  a = r;
        t = x - q * s;  x = s;  s = t;
    }
    *gcd = d;  /* $\gcd(a, n)$ */
    return (int)((x + n) % (n / d));
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int a, n, d, x;

    printf("a = ");  scanf("%d", &a);
    printf("n = ");  scanf("%d", &n);
    x = inv(a, n, &d);
    printf("a = %d, n = %d, d = gcd(a,n) = %d\n", a, n, d);
    printf("ax = d (mod n) <==> x = %d (mod n / d)\n", x);
    return 0;
}
