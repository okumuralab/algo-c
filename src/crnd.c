/***********************************************************
    crnd.c -- 線形合同法
***********************************************************/
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

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i;

    init_rnd(12345);  /* 任意の unsigned long で初期化. 省略可. */
    for (i = 0; i < 160; i++) printf("%10.7f", rnd());
    return 0;
}
