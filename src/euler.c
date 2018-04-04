/***********************************************************
    euler.c -- 一筆書き
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

#define NMAX    100                     /* 点の数の上限 */
#define EDGEMAX 100                     /* 線の数の上限 */
int adjacent[NMAX + 1][NMAX + 1];       /* 隣接行列 */
int position[EDGEMAX + 1];
int n, n_edge, edge, solution;          /* 点, 線の数; 線, 解の番号 */

void readgraph(void)                    /* データ入力 */
{
    int i, j;

    if (scanf("%d%*[^\n]", &n) != 1 || n > NMAX) {  /* 点の数 */
        n = 0;  return;
    }
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++) adjacent[i][j] = 0;
    while (scanf("%d%d%*[^\n]", &i, &j) == 2) {
        n_edge++;                       /* 線の数 */
        adjacent[i][j]++;
        adjacent[j][i]++;               /* 有向グラフならこの行は削除 */
    }
    printf("隣接行列:\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) printf(" %d", adjacent[i][j]);
        printf("\n");
    }
}

void visit(int i)
{
    int j;

    position[edge] = i;
    if (edge == n_edge) {
        printf("解 %d: ", ++solution);
        for (i = 0; i <= n_edge; i++) printf(" %d", position[i]);
        printf("\n");
    } else {
        for (j = 1; j <= n; j++) if (adjacent[i][j]) {
            adjacent[i][j]--;
            adjacent[j][i]--;  /* 有向グラフならこの行は削除 */
            edge++;  visit(j);  edge--;
            adjacent[i][j]++;
            adjacent[j][i]++;  /* 有向グラフならこの行は削除 */
        }
    }
}

int main(void)
{
    readgraph();                     /* データを読む */
    solution = edge = 0;  visit(1);  /* 点1から出発 */
    if (solution == 0) printf("解なし\n");
    return 0;
}
