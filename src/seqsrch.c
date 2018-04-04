/***********************************************************
    seqsrch.c -- 逐次探索
***********************************************************/
#define NOT_FOUND (-1)
typedef int keytype;

int seqsrch1(keytype x, keytype a[], int m, int n)
{
    while (m <= n && a[m] != x) m++;
    if (m <= n) return m;
    return NOT_FOUND;
}

int seqsrch2(keytype x, keytype a[], int m, int n)
{
    if (m > n) return NOT_FOUND;
    a[n + 1] = x;  /* 番人 */
    while (a[m] != x) m++;
    if (m <= n) return m;
    return NOT_FOUND;
}

int seqsrch3(keytype x, keytype a[], int m, int n)
{
    keytype t;

    if (m > n) return NOT_FOUND;
    t = a[n];  a[n] = x;  /* 番人 */
    while (a[m] != x) m++;
    a[n] = t;
    if (m < n) return m;
    if (x == t) return n;
    return NOT_FOUND;
}

/**********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 20

int main(void)
{
    int i, x;
    static int a[N + 1];

    printf("***** 逐次探索デモンストレーション *****\n");
    srand((unsigned int) time(NULL));
    for (i = 0; i < N; i++)
        a[i] = (int)((100.0 / (RAND_MAX + 1.0)) * rand());
    printf("  i : ");
    for (i = 0; i < N; i++) printf(" %2d", i);
    printf("\n");
    printf("a[i]: ");
    for (i = 0; i < N; i++) printf(" %2d", a[i]);
    printf("\n");

    printf("\n何を探しますか? ");
    scanf("%d", &x);

    printf("seqsrch1: ");
    i = seqsrch1(x, a, 0, N - 1);
    if (i != NOT_FOUND) printf("i = %d\n", i);
    else                printf("見つかりません\n");

    printf("seqsrch2: ");
    i = seqsrch2(x, a, 0, N - 1);
    if (i != NOT_FOUND) printf("i = %d\n", i);
    else                printf("見つかりません\n");

    printf("seqsrch3: ");
    i = seqsrch3(x, a, 0, N - 1);
    if (i != NOT_FOUND) printf("i = %d\n", i);
    else                printf("見つかりません\n");

    return 0;
}
