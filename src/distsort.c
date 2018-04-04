/***********************************************************
    distsort.c -- 分布数えソート
***********************************************************/
#define MAX 100
#define MIN   0

void distsort(int n, const int a[], int b[])
{
    int i, x;
    static int count[MAX - MIN + 1];

    for (i = 0; i <= MAX - MIN; i++) count[i] = 0;
    for (i = 0; i < n; i++) count[a[i] - MIN]++;
    for (i = 1; i <= MAX - MIN; i++) count[i] += count[i - 1];
    for (i = n - 1; i >= 0; i--) {
        x = a[i] - MIN;  b[--count[x]] = a[i];
    }
}

#include <stdio.h>
#include <stdlib.h>
#define N 20

int main(void)
{
    int i;
    static int a[N], b[N];

    printf("Before:");
    for (i = 0; i < N; i++) {
        a[i] = (MAX - MIN + 1.0) / (RAND_MAX + 1.0) * rand() + MIN;
        printf(" %d", a[i]);
    }
    printf("\n");
    distsort(N, a, b);
    printf("After: ");
    for (i = 0; i < N; i++) printf(" %d", b[i]);
    printf("\n");
    return 0;
}
