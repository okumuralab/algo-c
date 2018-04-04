/***********************************************************
    radsort.c -- ラディックス・ソート
***********************************************************/
#include <limits.h>  /* UCHAR_MAX (>= 255) */
void radixsort(int n, int length,
               unsigned char *a[], unsigned char *work[])
{
    int i, j;
    static int count[UCHAR_MAX + 1];

    for (j = length - 1; j >= 0; j--) {
        for (i = 0; i <= UCHAR_MAX; i++) count[i] = 0;
        for (i = 0; i < n; i++) count[a[i][j]]++;
        for (i = 1; i <= UCHAR_MAX; i++) count[i] += count[i - 1];
        for (i = n - 1; i >= 0; i--) work[--count[a[i][j]]] = a[i];
        for (i = 0; i < n; i++) a[i] = work[i];
    }
}

#define N 1000
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int i, n;
    static unsigned char *a[N], *work[N], s[N][17];

    for (n = 0; n < N; n++) {
        if (scanf("%16s%*[^ \t\n]", s[n]) != 1) break;
        a[n] = s[n];
    }
    radixsort(n, 16, a, work);
    for (i = 0; i < n; i++) printf("%s\n", a[i]);
    return 0;
}
