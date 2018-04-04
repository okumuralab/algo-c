/***********************************************************
    heapsort.c -- ヒープソート
***********************************************************/

typedef int keytype;

void heapsort(int n, keytype a[])
{
    int i, j, k;
    keytype x;

    for (k = n / 2; k >= 1; k--) {
        i = k;  x = a[i];
        while ((j = 2 * i) <= n) {
            if (j < n && a[j] < a[j + 1]) j++;
            if (x >= a[j]) break;
            a[i] = a[j];  i = j;
        }
        a[i] = x;
    }
    while (n > 1) {
        x = a[n];  a[n] = a[1];  n--;
        i = 1;
        while ((j = 2 * i) <= n) {
            if (j < n && a[j] < a[j + 1]) j++;
            if (x >= a[j]) break;
            a[i] = a[j];  i = j;
        }
        a[i] = x;
    }
}

#include <stdio.h>
#include <stdlib.h>

#define N 20
int a[N + 1];

int main(void)
{
    int i;

    printf("Before:");
    for (i = 1; i <= N; i++) {
        a[i] = rand() / (RAND_MAX / 100 + 1);
        printf(" %2d", a[i]);
    }
    printf("\n");

    heapsort(N, a);

    printf("After: ");
    for (i = 1; i <= N; i++) printf(" %2d", a[i]);
    printf("\n");

    return 0;
}
