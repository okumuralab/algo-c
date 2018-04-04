/***********************************************************
    randperm.c -- ランダムな順列
***********************************************************/

/***** 一様乱数 (線形合同法) ******************************/

#include <limits.h>
static unsigned long seed = 1;  /* 任意 */

void init_rnd(unsigned long x)
{
    seed = x;
}

unsigned long irnd(void)
{
    seed = seed * 1566083941UL + 1;
    return seed;
}

double rnd(void)  /* 0 <= rnd() < 1 */
{
    return (1.0 / (ULONG_MAX + 1.0)) * irnd();
}

/**********************************************************/

void shuffle(int n, int v[])
{
    int i, j, t;

    for (i = n - 1; i > 0; i--) {
        j = (int)((i + 1) * rnd());
        t = v[i];  v[i] = v[j];  v[j] = t;
    }
}

void randperm(int n, int v[])
{
    int i;

    for (i = 0; i < n; i++) v[i] = i + 1;
    shuffle(n, v);
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i;
    static int a[100];

    randperm(100, a);
    for (i = 0; i < 100; i++) printf("%4d", a[i]);
    printf("\n");
    return 0;
}
