/***********************************************************
    knight.c -- 騎士巡歴の問題
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

#define N  5           /* ${\tt N} \times {\tt N}$ の番面 */

int board[N + 4][N + 4],                /* 番面 */
    dx[8] = { 2, 1,-1,-2,-2,-1, 1, 2 }, /* 横変位 */
    dy[8] = { 1, 2, 2, 1,-1,-2,-2,-1 }; /* 縦変位 */

void printboard(void)                   /* 番面を出力 */
{
    int i, j;
    static solution = 0;

    printf("\n解 %d\n", ++solution);
    for (i = 2; i <= N + 1; i++) {
        for (j = 2; j <= N + 1; j++) printf("%4d", board[i][j]);
        printf("\n");
    }
}

void try(int x, int y)  /* 再帰的に試みる */
{
    int i;
    static int count = 0;

    if (board[x][y] != 0) return;  /* すでに訪れた */
    board[x][y] = ++count;
    if (count == N * N) printboard();  /* 完成 */
    else for (i = 0; i < 8; i++) try(x + dx[i], y + dy[i]);
    board[x][y] = 0;  count--;
}

int main(void)
{
    int i, j;

    for (i = 0; i <= N + 3; i++)
        for (j = 0; j <= N + 3; j++) board[i][j] = 1;
    for (i = 2; i <= N + 1; i++)
        for (j = 2; j <= N + 1; j++) board[i][j] = 0;
    try(2, 2);
    return 0;
}
