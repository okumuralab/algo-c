/***********************************************************
    toposort.c -- トポロジカル・ソーティング
    使用例: toposort <toposort.dat
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

#define NMAX 100                                /* 点の数の上限 */
char adjacent[NMAX + 1][NMAX + 1];              /* 隣接行列 */
char visited[NMAX + 1];                         /* 訪れたか */

int n;                                          /* 点の数 */

void readgraph(void)                            /* データ入力 */
{
    int i, j;

    if (scanf("%d%*[^\n]", &n) != 1 || n > NMAX) {
        n = 0;  return;
    }
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++) adjacent[i][j] = 0;
    while (scanf("%d%d%*[^\n]", &i, &j) == 2)
        adjacent[i][j] = 1;
    printf("隣接行列:\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) printf(" %d", adjacent[i][j]);
        printf("\n");
    }
}

enum {NEVER, JUST, ONCE};

void visit(int i)
{
    int j;

    visited[i] = JUST;
    for (j = 1; j <= n; j++) {
        if (! adjacent[j][i]) continue;
        if (visited[j] == NEVER) visit(j);
        else if (visited[j] == JUST) {
            printf("\nサイクルあり!n");  exit(1);
        }
    }
    visited[i] = ONCE;  printf(" %d", i);
}

int main(void)
{
    int i;

    readgraph();  /* データ {\tt n}, {\tt adjacent[1..n][1..n]} を読む */
    for (i = 1; i <= n; i++) visited[i] = NEVER;
    printf("トポロジカル・ソーティングの結果:\n");
    for (i = 1; i <= n; i++)
        if (visited[i] == NEVER) visit(i);
    printf("\n");
    return 0;
}
