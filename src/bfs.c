/***********************************************************
    bfs.c -- 横形探索
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

struct queue {  /* 待ち行列 */
    int item;
    struct queue *next;
} *head, *tail;

void initialize_queue(void)  /* 待ち行列の初期化 */
{
    head = tail = malloc(sizeof(struct queue));
    if (head == NULL) exit(1);
}

void addqueue(int x)  /* 待ち行列への挿入 */
{
    tail->item = x;
    tail->next = malloc(sizeof(struct queue));
    if (tail->next == NULL) exit(1);
    tail = tail->next;
}

int removequeue(void)  /* 待ち行列からの取出し */
{
    int x;
    struct queue *p;

    p = head;  head = p->next;  x = p->item;  free(p);
    return x;
}

#define START  1

int main(void)
{
    int i, j;
    static int distance[NMAX + 1], prev[NMAX + 1];

    initialize_queue();
    readgraph();
    for (i = 1; i <= n; i++) distance[i] = -1;
    addqueue(START);  distance[START] = 0;
    do {
        i = removequeue();
        for (j = 1; j <= n; j++)
            if (adjacent[i][j] && distance[j] < 0) {
                addqueue(j);  distance[j] = distance[i] + 1;
                prev[j] = i;
            }
    } while (head != tail);
    printf("点  直前の点  最短距離\n");
    for (i = 1; i <= n; i++)
        if (distance[i] > 0)
            printf("%2d%10d%10d\n", i, prev[i], distance[i]);
    return 0;
}
