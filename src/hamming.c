/***********************************************************
    hamming.c -- Hamming (ハミング) の問題
***********************************************************/
#define N 100
int q[N];

void hamming(void)
{
    int i, j2, j3, j5, min, x2, x3, x5;

    j2 = j3 = j5 = 0;  x2 = x3 = x5 = 1;
    for (i = 0; i < N; i++) {
        min = x2;
        if (x3 < min) min = x3;
        if (x5 < min) min = x5;
        q[i] = min;
        while (x2 <= min) x2 = 2 * q[j2++];
        while (x3 <= min) x3 = 3 * q[j3++];
        while (x5 <= min) x5 = 5 * q[j5++];
    }
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i;

    hamming();
    for (i = 0; i < N; i++) printf("%5d", q[i]);
    printf("\n");
    return 0;
}
