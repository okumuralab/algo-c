/**************************************************************
    life.c -- ライフ・ゲーム
**************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define N  22  /* 縦方向 */
#define M  78  /* 横方向 */
char a[N + 2][M + 2], b[N + 2][M + 2];  /* 盤 */

int main(void)
{
    int i, j, g;

    a[N/2][M/2] = a[N/2-1][M/2] = a[N/2+1][M/2]
        = a[N/2][M/2-1] = a[N/2-1][M/2+1] = 1;  /* 初期状態 */
    for (g = 1; g <= 1000; g++) {
        printf("Generation %4d\n", g);  /* 世代 */
        for (i = 1; i <= N; i++) {
            for (j = 1; j <= M; j++)
                if (a[i][j]) {
                    printf("*");
                    b[i-1][j-1]++;  b[i-1][j]++;  b[i-1][j+1]++;
                    b[i  ][j-1]++;                b[i  ][j+1]++;
                    b[i+1][j-1]++;  b[i+1][j]++;  b[i+1][j+1]++;
                } else printf(".");
            printf("\n");
        }
        for (i = 0; i <= N + 1; i++)
            for (j = 0; j <= M + 1; j++) {
                if (b[i][j] != 2) a[i][j] = (b[i][j] == 3);
                b[i][j] = 0;
            }
    }
    return 0;
}
