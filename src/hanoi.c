/***********************************************************
    hanoi.c -- ハノイの塔
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

void movedisk(int n, int a, int b)
{
    if (n > 1) movedisk(n - 1, a, 6 - a - b);
    printf("円盤 %d を %d から %d に移す\n", n, a, b);
    if (n > 1) movedisk(n - 1, 6 - a - b, b);
}

int main(void)
{
    int n;

    printf("円盤の枚数? ");  scanf("%d", &n);
    printf("円盤 %d 枚を柱 1 から柱 2 に移す方法は"
        "次の %lu 手です.\n", n, (1UL << n) - 1);
    movedisk(n, 1, 2);
    return 0;
}
