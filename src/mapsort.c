/***********************************************************
    mapsort.c -- 逆写像ソート
***********************************************************/
#define MAX 100
#define MIN   0

void mapsort(int n, int a[], int b[], int next[])
{
    int i, j, x;
    static int index[MAX - MIN + 1];

    for (x = 0; x <= MAX - MIN; x++) index[x] = -1;
    for (i = n - 1; i >= 0; i--) {
        x = a[i] - MIN;  next[i] = index[x];  index[x] = i;
    }
    j = 0;
    for (x = 0; x <= MAX - MIN; x++) {
        i = index[x];
        while (i >= 0) {
            b[j++] = a[i];  i = next[i];
        }
    }
}

#include <stdio.h>
#include <stdlib.h>
#define N 20

int main(void)
{
    int i;
    static int a[N], b[N], work[N];

    printf("Before:");
    for (i = 0; i < N; i++) {
        a[i] = (MAX - MIN + 1.0) / (RAND_MAX + 1.0) * rand() + MIN;
        printf(" %d", a[i]);
    }
    printf("\n");
    mapsort(N, a, b, work);
    printf("After: ");
    for (i = 0; i < N; i++) printf(" %d", b[i]);
    printf("\n");
    return 0;
}
