/***********************************************************
    mccarthy.c -- McCarthy (マッカーシー) 関数
***********************************************************/
#define N 100

int McCarthy(int x)
{
    if (x > N) return x - 10;
    /* else */ return McCarthy(McCarthy(x + 11));
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int x;

    for ( ; ; ) {
        printf("0 以上 %d 以下の整数 x: ", N);
        scanf("%d", &x);
        if (x < 0 || x > N) break;
        printf("McCarthy(x) = %d\n", McCarthy(x));
    }
    return 0;
}
