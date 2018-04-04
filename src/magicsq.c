/***********************************************************
    magicsq.c -- 魔方陣
***********************************************************/
/* 奇数次の魔方陣 */

#include <stdio.h>
#include <stdlib.h>

#define N 19  /* 奇数 */

int main(void)
{
    int i, j, k;
    static int a[N][N];

    k = 0;
    for (i = - N / 2; i <= N / 2; i++)
        for (j = 0; j < N; j++)
            a[(j - i + N) % N][(j + i + N) % N] = ++k;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) printf("%4d", a[i][j]);
        printf("\n");
    }
    return 0;
}
