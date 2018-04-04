/***********************************************************
    gray1.c -- Gray (グレイ) 符号
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#define N  6  /* 桁数 */

int main(void)
{
    int i;
    char binary[N + 1], Gray[N];

    for (i = 0; i < N; i++) binary[i] = Gray[i] = 0;
    binary[N] = 0;  /* 番人 */
    printf("%*s  %*s\n", N, "binary", N, "Gray");
    for ( ; ; ) {
        /* 出力. */
        for (i = N - 1; i >= 0; i--) printf("%d", binary[i]);
        printf("  ");
        for (i = N - 1; i >= 0; i--) printf("%d", Gray[i]);
        printf("\n");
        for (i = 0; binary[i] == 1; i++) binary[i] = 0;
        if (i == N) break;
        binary[i] = 1;
        Gray[i] ^= 1;  /* 1個変えるだけで次のGray符号が得られる. */
    }
    return 0;
}
