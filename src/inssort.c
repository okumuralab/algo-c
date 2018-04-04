/***********************************************************
    inssort.c -- 挿入ソート
***********************************************************/

typedef int keytype;  /* 整列キーの型 */

void inssort(int n, keytype a[])  /* a[0..n-1] を昇順に */
{
    int i, j;
    keytype x;

    for (i = 1; i < n; i++) {
        x = a[i];
        for (j = i - 1; j >= 0 && a[j] > x; j--)
            a[j + 1] = a[j];
        a[j + 1] = x;
    }
}

#if 0  /***** a[N] を番人として使う **************/

#include <limits.h>  /* INT_MAX の定義を含むファイル */

void inssort(int n, keytype a[])
{
    int i, j;
    keytype x;

    a[n] = INT_MAX;  /* 番人 */
    for (i = n - 2; i >= 0; i--) {
        x = a[i];
        for (j = i + 1; a[j] < x; j++)
            a[j - 1] = a[j];
        a[j - 1] = x;
    }
}

#endif  /*****************************************/

#include <stdio.h>
#include <stdlib.h>

#define N 20
int a[N + 1];  /* 番人を使わないなら a[N] でよい */

int main(void)
{
    int i;

    printf("Before:");
    for (i = 0; i < N; i++) {
        a[i] = rand() / (RAND_MAX / 100 + 1);
        printf(" %2d", a[i]);
    }
    printf("\n");
    inssort(N, a);
    printf("After: ");
    for (i = 0; i < N; i++) printf(" %2d", a[i]);
    printf("\n");
    return 0;
}
