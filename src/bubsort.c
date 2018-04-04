/***********************************************************
    bubsort.c -- バブルソート
***********************************************************/
typedef int keytype;
void bubblesort(int n, keytype a[])
{
    int i, j, k;
    keytype x;

    k = n - 1;
    while (k >= 0) {
        j = -1;
        for (i = 1; i <= k; i++)
            if (a[i - 1] > a[i]) {
                j = i - 1;
                x = a[j];  a[j] = a[i];  a[i] = x;
            }
        k = j;
    }
}

#include <stdio.h>
#include <stdlib.h>

#define N 20

int main(void)
{
    int i;
    static keytype a[N];

    printf("Before:");
    for (i = 0; i < N; i++) {
        a[i] = rand() / (RAND_MAX / 100 + 1);
        printf(" %2d", a[i]);
    }
    printf("\n");
    bubblesort(N, a);
    printf("After: ");
    for (i = 0; i < N; i++) printf(" %2d", a[i]);
    printf("\n");
    return 0;
}
