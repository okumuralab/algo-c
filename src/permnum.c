/***********************************************************
    permnum.c -- 順列
***********************************************************/
/* 自然数との相互変換 */

#define N 4
int a[N + 1];

int encode(void)
{
    int i, j, k, t, c;

    c = 0;
    for (i = N; i > 1; i--) {
        k = 1;
        for (j = 2; j <= i; j++)
            if (a[j] > a[k]) k = j;
        t = a[i];  a[i] = a[k];  a[k] = t;
        c = c * i + k - 1;
    }
    return c;
}

void decode(int c)
{
    int i, k, t;

    for (i = 2; i <= N; i++) {
        k = c % i + 1;  c /= i;
        t = a[i];  a[i] = a[k];  a[k] = t;
    }
}

int nextperm(void)
{
    int i, j, t;

    a[0] = 0;  /* 番人 */
    i = N - 1;
    while (a[i] >= a[i + 1]) i--;
    if (i == 0) return 0;  /* 完了 */
    j = N;
    while (a[i] >= a[j]) j--;
    t = a[i];  a[i] = a[j];  a[j] = t;
    i++;  j = N;
    while (i < j) {
        t = a[i];  a[i] = a[j];  a[j] = t;  i++;  j--;
    }
    return 1;  /* 未了 */
}

#include <stdio.h>
#include <stdlib.h>

void show(int count)
{
    int i;

    printf("%5d: ", count);
    for (i = 1; i <= N; i++) printf("%4d", a[i]);
    printf("\n");
}

int main(void)
{
    int i, c, count;

    count = 0;
    for (i = 1; i <= N; i++) a[i] = i;
    do {
        count++;
        show(count);
        printf("code = %d\n", c = encode());
        show(count);
        decode(c);
        show(count);
        printf("\n");
    } while (nextperm());
    return 0;
}
