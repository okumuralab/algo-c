/***********************************************************
    krnd.c -- Knuthの乱数発生法
***********************************************************/
#define MRND  1000000000L
static int jrand;
static long ia[56];  /* ia[1..55] */

static void irn55(void)
{
    int i;
    long j;

    for (i = 1; i <= 24; i++) {
        j = ia[i] - ia[i + 31];
        if (j < 0) j += MRND;
        ia[i] = j;
    }
    for (i = 25; i <= 55; i++) {
        j = ia[i] - ia[i - 24];
        if (j < 0) j += MRND;
        ia[i] = j;
    }
}

void init_rnd(long seed)
{
    int i, ii;
    long k;

    ia[55] = seed;
    k = 1;
    for (i = 1; i <= 54; i++) {
        ii = (21 * i) % 55;
        ia[ii] = k;
        k = seed - k;
        if (k < 0) k += MRND;
        seed = ia[ii];
    }
    irn55();  irn55();  irn55();  /* warm up */
    jrand = 55;
}

long irnd(void)  /* 0 <= irnd() < MRND */
{
    if (++jrand > 55) {  irn55();  jrand = 1;  }
    return ia[jrand];
}

double rnd(void)  /* 0 <= rnd() < 1 */
{
    return (1.0 / MRND) * irnd();
}

/**********************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i;

    init_rnd(12345);  /* 任意の long で初期化. 省略不可. */
    for (i = 0; i < 160; i++) printf("%10.7f", rnd());
    return 0;
}
