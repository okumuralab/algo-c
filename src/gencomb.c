/***********************************************************
    gencomb.c -- 組合せの生成
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#define N 8
#define K 4
typedef unsigned int set;
#define first(n) ((set) ((1U << (n)) - 1U))

set nextset(set x)
{
    set smallest, ripple, new_smallest, ones;

    smallest = x & -x;
    ripple = x + smallest;
    new_smallest = ripple & -ripple;
    ones = ((new_smallest / smallest) >> 1) - 1;
    return ripple | ones;
}

void printset(set s)
{
    int i;

    for (i = 1; i <= N; i++) {
        if (s & 1) printf(" %d", i);
        s >>= 1;
    }
    printf("\n");
}

int main(void)
{
    int i;
    set x;

    i = 1;  x = first(K);
    while (! (x & ~first(N))) {
        printf("%4d:", i);  printset(x);
        x = nextset(x);  i++;
    }
    return 0;
}
