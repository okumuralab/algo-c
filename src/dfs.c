/***********************************************************
    dfs.c -- 縦形探索
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#define NMAX 100                                /* 点の数の上限 */
char adjacent[NMAX + 1][NMAX + 1];              /* 隣接行列 */

int n = 7;                                      /* 点の数 (例) */
int data[] = { 1, 2, 2, 3, 1, 3, 2, 4, 5, 7 };  /* データ (例) */

void readgraph(void)  /* グラフ入力 */
{
    int i, j, k;

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++) adjacent[i][j] = 0;
    for (k = 0; k < (sizeof data) / (sizeof *data); k++) {
        if (k % 2 == 0) i = data[k];
        else {
            j = data[k];
            adjacent[i][j] = adjacent[j][i] = 1;
        }
    }
    printf("隣接行列:\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) printf(" %d", adjacent[i][j]);
        printf("\n");
    }
}

char visited[NMAX + 1];  /* 訪れたなら1 */

void visit(int i)  /* 点 {\tt i} を訪れる (再帰的) */
{
    int j;

    printf(" %d", i);  visited[i] = 1;
    for (j = 1; j <= n; j++)
        if (adjacent[i][j] && ! visited[j]) visit(j);
}

int main(void)
{
    int i, count;

    readgraph();                              /* グラフのデータを読む */
    for (i = 1; i <= n; i++) visited[i] = 0;  /* まだどこも訪れていない */
    printf("連結成分:\n");
    count = 0;                                /* 連結成分を数える */
    for (i = 1; i <= n; i++)
        if (! visited[i]) {
            printf("%3d:", ++count);
            visit(i);  printf("\n");
        }
    return 0;
}
