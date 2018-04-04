/***********************************************************
    common.c -- 共通の要素
***********************************************************/
#include <stdio.h>
#include <limits.h>

void list_common_elements(
    int na, int a[], int nb, int b[], int nc, int c[])
{
    int i, j, k, t;

    a[na] = b[nb] = c[nc] = INT_MAX;  /* 番人 */
    i = j = k = 0;  t = a[0];
    while (t < INT_MAX) {
        while (b[j] < t) j++;
        while (c[k] < t) k++;
        if (t == b[j] && t == c[k]) printf(" %d", t);
        do {  i++;  } while (a[i] == t);
        t = a[i];
    }
    printf("\n");
}

#include <stdlib.h>

void make_sorted_array(int n, int a[])
{
    int i;

    a[0] = rand() / (RAND_MAX / 5);
    for (i = 1; i < n; i++)
        a[i] = a[i - 1] + rand() / (RAND_MAX / 3);
    for (i = 0; i < n; i++) printf(" %2d", a[i]);
    printf("\n");
}

#define L 20
#define M 20
#define N 20

int main(void)
{
    static int a[L + 1], b[M + 1], c[N + 1];

    printf("a: ");  make_sorted_array(L, a);
    printf("b: ");  make_sorted_array(M, b);
    printf("c: ");  make_sorted_array(N, c);
    printf("common elements: ");
    list_common_elements(L, a, M, b, N, c);
    return 0;
}
