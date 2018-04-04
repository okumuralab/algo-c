/***********************************************************
    acker.c -- Ackermann (アッカーマン) 関数
***********************************************************/
#define TEST 1

#if TEST
    int count = 0;
#endif

int A(int x, int y)
{
    #if TEST
        count++;
    #endif
    if (x == 0) return y + 1;
    if (y == 0) return A(x - 1, 1);
    return A(x - 1, A(x, y - 1));
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("A(3, 3) = %d\n", A(3, 3));
    #if TEST
        printf("A(x, y) は %d 回呼び出されました.\n", count);
    #endif
    return 0;
}
