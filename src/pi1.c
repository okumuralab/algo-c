/***********************************************************
    pi1.c -- 円周率
***********************************************************/

long double pi(void)  /* Machinの公式 */
{
    int k;
    long double p, t, last;

    p = 0;  k = 1;  t = 16.0L / 5.0L;
    do {
        last = p;  p += t / k;  t /= -5.0L*5.0L;  k += 2;
    } while (p != last);
    k = 1;  t = 4.0L / 239.0L;
    do {
        last = p;  p -= t / k;  t /= -239.0L*239.0L;  k += 2;
    } while (p != last);
    return p;
}

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

int main(void)
{
    printf("pi = %.*Lg\n", LDBL_DIG, pi());
    return 0;
}
