/***********************************************************
    qsort2.c -- クイックソート
***********************************************************/
typedef int keytype;

void inssort(int n, keytype a[])
{
    int i, j;
    keytype x;

    for (i = 1; i < n; i++) {
        x = a[i];
        for (j = i - 1; j >= 0 && a[j] > x; j--)
            a[j + 1] = a[j];
        a[j + 1] = x;
    }
}

#define THRESHOLD 10
#define STACKSIZE 32  /* たかだか int のビット数程度 */

void quicksort(int n, keytype a[])
{
    int i, j, left, right, p;
    int leftstack[STACKSIZE], rightstack[STACKSIZE];
    keytype x, t;

    left = 0;  right = n - 1;  p = 0;
    for ( ; ; ) {
        if (right - left <= THRESHOLD) {
            if (p == 0) break;
            p--;
            left = leftstack[p];
            right = rightstack[p];
        }
        x = a[(left + right) / 2];
        i = left;  j = right;
        for ( ; ; ) {
            while (a[i] < x) i++;
            while (x < a[j]) j--;
            if (i >= j) break;
            t = a[i];  a[i] = a[j];  a[j] = t;
            i++;  j--;
        }
        if (i - left > right - j) {
            if (i - left > THRESHOLD) {
                leftstack[p] = left;
                rightstack[p] = i - 1;
                p++;
            }
            left = j + 1;
        } else {
            if (right - j > THRESHOLD) {
                leftstack[p] = j + 1;
                rightstack[p] = right;
                p++;
            }
            right = i - 1;
        }
    }
    inssort(n, a);
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
    quicksort(N, a);
    printf("After: ");
    for (i = 0; i < N; i++) printf(" %2d", a[i]);
    printf("\n");
    return 0;
}
