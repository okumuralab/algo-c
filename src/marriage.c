/***********************************************************
    marriage.c -- 安定な結婚の問題
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#define N  3  /* 各性の人数 */

int boy[N+1], girl[N+1][N+1], position[N+1], rank[N+1][N+1];

int main(void)
{
    int b, g, r, s, t;

    for (g = 1; g <= N; g++) {  /* 各女性の好み */
        for (r = 1; r <= N; r++) {
            scanf("%d", &b);  rank[g][b] = r;
        }
        boy[g] = 0;  rank[g][0] = N + 1;  /* 番人 */
    }
    for (b = 1; b <= N; b++) {  /* 各男性の好み */
        for (r = 1; r <= N; r++) scanf("%d", &girl[b][r]);
        position[b] = 0;
    }
    for (b = 1; b <= N; b++) {
        s = b;
        while (s != 0) {
            g = girl[s][++position[s]];
            if (rank[g][s] < rank[g][boy[g]]) {
                t = boy[g];  boy[g] = s;  s = t;
            }
        }
    }
    for (g = 1; g <= N; g++)
        printf("女 %d - 男 %d\n", g, boy[g]);
    return 0;
}
