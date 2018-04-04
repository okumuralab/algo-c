/***********************************************************
    cannibals.c -- 宣教師と人食い人
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

#define M  3  /* 宣教師の数 */
#define C  3  /* 人食い人の数 */
#define B  2  /* ボートの定員 */

int np, solution;
unsigned char mb[(B+1)*(B+2)/2], cb[(B+1)*(B+2)/2],
    mh[2*(M+1)*(C+1)], ch[2*(M+1)*(C+1)], flag[M+1][C+1];

void found(int n)  /* 解の表示 */
{
    int i;
    static char mmm[] = "MMMMMMMMMM", ccc[] = "CCCCCCCCCC";

    printf("解 %d\n", ++solution);
    for (i = 0; i <= n; i++) {
        printf("%4d  %-*.*s %-*.*s  /  %-*.*s %-*.*s\n",
            i, M, mh[i], mmm, C, ch[i], ccc,
               M, M - mh[i], mmm, C, C - ch[i], ccc);
    }
}

void try(void)  /* 再帰的に試す */
{
    static i = 0;
    int j, m, c;

    i++;
    for (j = 1; j < np; j++) {
        if (i & 1) {  /* 奇数回目は向こうに行く */
            m = mh[i - 1] - mb[j];  c = ch[i - 1] - cb[j];
        } else {      /* 偶数回目はこちらに来る */
            m = mh[i - 1] + mb[j];  c = ch[i - 1] + cb[j];
        }
        if (m < 0 || c < 0 || m > M || c > C ||
                (flag[m][c] & (1 << (i & 1)))) continue;
        mh[i] = m;  ch[i] = c;
        if (m == 0 && c == 0) found(i);
        else {
            flag[m][c] |= 1 << (i & 1);  try();
            flag[m][c] ^= 1 << (i & 1);
        }
    }
    i--;
}

int main(void)
{
    int m, c;

    np = 0;
    for (m = 0; m <= B; m++) for (c = 0; c <= B - m; c++)
        if (m == 0 || m >= c) {
            mb[np] = m;  cb[np] = c;  np++;
        }
    for (m = 0; m <= M; m++) for (c = 0; c <= C; c++)
        if ((m > 0 && m < c) || (m < M && M - m < C - c))
            flag[m][c] |= 1 | 2;
    mh[0] = M;  ch[0] = C;  flag[M][C] |= 1;
    solution = 0;  try();
    if (solution == 0) printf("解はありません.\n");
    return 0;
}
