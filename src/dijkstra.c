/***********************************************************
    dijkstra.c -- 最短路問題
    使用例: dijkstra <dijkstra.dat
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NMAX 100                 /* 点の数の上限 */
int weight[NMAX + 1][NMAX + 1];  /* 辺の重み */
int n;                           /* 点の数 */

void readweight(void)            /* データ入力 */
{
    int i, j, x;

    if (scanf("%d%*[^\n]", &n) != 1 || n > NMAX) {
        n = 0;  return;
    }
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++) weight[i][j] = INT_MAX;
    while (scanf("%d%d%d%*[^\n]", &i, &j, &x) == 3)
        weight[i][j] = weight[j][i] = x;
    printf("データ weight(i,j)\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (weight[i][j] < INT_MAX)
                printf("%3d", weight[i][j]);
            else
                printf(" ∞");
        }
        printf("\n");
    }
}

#define START  1  /* 出発点 */
#define FALSE  0
#define TRUE   1

int main(void)
{
    int i, j, next, min;
    static char visited[NMAX + 1];
    static int distance[NMAX + 1], prev[NMAX + 1];

    readweight();  /* 点の数{\tt n}, 距離{\tt weight[1..n][1..n]}を読む */
    for (i = 1; i <= n; i++) {
        visited[i] = FALSE;  distance[i] = INT_MAX;
    }
    distance[START] = 0;  next = START;
    do {
        i = next;  visited[i] = TRUE;  min = INT_MAX;
        for (j = 1; j <= n; j++) {
            if (visited[j]) continue;
            if (weight[i][j] < INT_MAX &&
                    distance[i] + weight[i][j] < distance[j]) {
                distance[j] = distance[i] + weight[i][j];
                prev[j] = i;
            }
            if (distance[j] < min) {
                min = distance[j];  next = j;
            }
        }
    } while (min < INT_MAX);
    printf("点  直前の点  最短距離\n");
    for (i = 1; i <= n; i++)
        if (i != START && visited[i])
            printf("%2d%10d%10d\n", i, prev[i], distance[i]);
    return 0;
}
