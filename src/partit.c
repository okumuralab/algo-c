/***********************************************************
    partit.c -- 分割数
***********************************************************/

static int p(int n, int k)
{
    int i, s;

    if (n < 0) return 0;
    if (n <= 1 || k == 1) return 1;
    s = 0;
    for (i = 1; i <= k; i++)
        s += p(n - i, i);
    return s;
}

int partition(int n)
{
    return p(n, n);
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int x;

    for (x = 1; x <= 20; x++)
        printf("%5d  %5d\n", x, partition(x));
    return 0;
}
