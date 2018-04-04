/***********************************************************
    shelsort.c -- Shellソート
***********************************************************/

typedef int keytype;  /* 整列キーの型 */

void shellsort(int n, keytype a[])  /* a[0..n-1] を昇順に */
{
    int h, i, j;
    keytype x;

    h = 13;
    while (h < n) h = 3 * h + 1;
    h /= 9;
    while (h > 0) {
        for (i = h; i < n; i++) {
            x = a[i];
            for (j = i - h; j >= 0 && a[j] > x; j -= h)
                a[j + h] = a[j];
            a[j + h] = x;
        }
        h /= 3;
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

    shellsort(N, a);

    printf("After: ");
    for (i = 0; i < N; i++) printf(" %2d", a[i]);
    printf("\n");

    return 0;
}
