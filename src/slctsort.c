/***********************************************************
    slctsort.c -- 選択ソート
***********************************************************/

typedef int keytype;  /* 整列キーの型 */

void selectsort(int n, keytype a[])  /* a[0..n-1] を昇順に */
{
    int i, j, k;
    keytype min;

    for (i = 0; i < n - 1; i++) {
        min = a[i];  k = i;
        for (j = i + 1; j < n; j++)
            if (a[j] < min) {  min = a[j];  k = j;  }
        a[k] = a[i];  a[i] = min;
    }
}

#include <stdio.h>
#include <stdlib.h>

#define N 20
int a[N];

int main(void)
{
    int i;

    printf("Before:");
    for (i = 0; i < N; i++) {
        a[i] = rand() / (RAND_MAX / 100 + 1);
        printf(" %2d", a[i]);
    }
    printf("\n");

    selectsort(N, a);

    printf("After: ");
    for (i = 0; i < N; i++) printf(" %2d", a[i]);
    printf("\n");

    return 0;
}
