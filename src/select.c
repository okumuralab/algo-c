/***********************************************************
    select.c -- 選択
***********************************************************/
typedef int keytype;

keytype select(keytype a[], int n, int k)
{
    int i, j, left, right;
    keytype x, t;

    left = 0;  right = n - 1;
    while (left < right) {
        x = a[k];  i = left;  j = right;
        for ( ; ; ) {
            while (a[i] < x) i++;
            while (x < a[j]) j--;
            if (i >= j) break;
            t = a[i];  a[i] = a[j];  a[j] = t;
            i++;  j--;
        }
        if (i <= k) left = j + 1;
        if (k <= j) right = i - 1;
    }
    return a[k];
}

#include <stdio.h>
#include <stdlib.h>

#define N 10
keytype a[N];

int main(void)
{
    int i, k;

    for (i = 0; i < N; i++) {
        a[i] = rand() / (RAND_MAX / 100 + 1);
        printf(" %d", a[i]);
    }
    printf("\n");
    do {
        printf("小さい方から数えて何番目のものを求めますか? ");
        scanf("%d", &k);
    } while (k < 1 || k > N);
    printf("  %d番目 = %d\n", k, select(a, N, k - 1));
    return 0;
}
