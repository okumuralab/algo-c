/***********************************************************
    rndsamp3.c -- 無作為抽出
***********************************************************/

/***** 一様乱数 (線形合同法) ******************************/

#include <limits.h>
static unsigned long seed = 1;

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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100
#define M 50

int main(void)
{
    int i, j;
    static char s[N];

    init_rnd((unsigned long) time(NULL));
    for (i = N - M; i < N; i++) {
        j = (int)((i + 1) * rnd());  /* 0 <= j <= i */
        if (s[j] == 0) s[j] = 1;
        else           s[i] = 1;
    }
    for (i = 0; i < N; i++)
        if (s[i]) printf(" %4d", i + 1);
    printf("\n");
    return 0;
}
