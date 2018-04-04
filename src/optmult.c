/***********************************************************
    optmult.c -- 行列の積
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define N  4                        /* 行列の数 */
int nrow[N + 1] = {4, 2, 6, 3, 5},  /* 例えば */
    mincost[N][N], split[N][N];

void printresult(int left, int right)
{
    if (left == right) printf("A%d", left);
    else {
        printf("(");
        printresult(left, split[left][right]);
        printresult(split[left][right] + 1, right);
        printf(")");
    }
}

int main(void)
{
    int i, left, right, length, cost, min, choice;

    for (i = 0; i < N; i++) mincost[i][i] = 0;
    for (length = 1; length < N; length++) {
        for (left = 0; left < N - length; left++) {
            right = left + length;  min = INT_MAX;
            for (i = left; i < right; i++) {
                cost = mincost[left][i]
                     + mincost[i+1][right]
                     + nrow[left]*nrow[i+1]*nrow[right+1];
                if (cost < min) {
                    min = cost;  choice = i;
                }
            }
            mincost[left][right] = min;
            split[left][right] = choice;
        }
    }
    printf("Minimum cost = %d\n", mincost[0][N - 1]);
    printresult(0, N - 1);
    return 0;
}
